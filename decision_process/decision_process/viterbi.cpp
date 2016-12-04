#include "stdafx.h"
#include "viterbi.h"


viterbi::viterbi()
{
}


viterbi::~viterbi()
{
}

bool viterbi::initial(std::vector<std::vector<map_str>>& map) {
	this->row = map.size();
	if (!row) return false;
	this->col = map[0].size();
	if (!col) return false;
	this->beli_status.resize(row, std::vector<std::vector<beli_stur>>(col, std::vector<beli_stur>(1)));
	int count = 0;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (map[i][j].type != BLOCK)
				++count;
		}
	}
	double ini_prob = 1.0 / count;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (map[i][j].type != BLOCK)
				this->beli_status[i][j][0].probability = ini_prob;
		}
	}
	return true;
}

void viterbi::do_viterbi(std::vector<std::vector<map_str>>& map, std::vector<char>& status, std::vector<int>& actions) {
	if (!initial(map)) return;
	int status_size = status.size();
	int action_size = actions.size();
	if (!status_size || status_size != action_size) return;
	for (int i = 0; i < action_size; ++i) {
		std::vector<std::vector<beli_stur>> tmp_beli(row, std::vector<beli_stur>(col));;
		transition(map, tmp_beli, actions[i], status[i], i);
		set_beli_status(tmp_beli);
	}
	std::vector<beli_stur> path = get_mls();
	for (int i = path.size() - 1; i >= 0; --i) {
		std::cout << path[i].parent.first << ","<< path[i].parent.second << "," << path[i].probability << std::endl;
	}
}

void viterbi::transition(std::vector<std::vector<map_str>>& map, std::vector<std::vector<beli_stur>>& tmp_beli, int action, char status, int idx) {
	if (action < 0 || action > 3) return;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (beli_status[i][j].size() < idx) {
				std::cout << "[ERROR] beli_status no such big beli_stur vector " << beli_status.size() << "need at least " << idx << std::endl;
				return;
			}
			if (map[i][j].type == BLOCK)
				continue;
			beli_stur pre_beli_stur = this->beli_status[i][j][idx];
			int x = i + direction[action].first, y = j + direction[action].second;
			if (x < 0 || x >= row || y < 0 || y >= col || map[x][y].type == BLOCK) {
				if (tmp_beli[i][j].probability < pre_beli_stur.probability) {
					tmp_beli[i][j].probability = pre_beli_stur.probability;
					tmp_beli[i][j].parent = { i,j };
				}
				continue;
			}
			else {
				double tmp = SUCC_MOVE * pre_beli_stur.probability;
				if (tmp_beli[x][y].probability < tmp) {
					tmp_beli[x][y].probability = tmp;
					tmp_beli[x][y].parent = { i,j };
				}
				tmp = (1 - SUCC_MOVE) * pre_beli_stur.probability;
				if (tmp_beli[i][j].probability < tmp) {
					tmp_beli[i][j].probability = tmp;
					tmp_beli[i][j].parent = { i,j };
				}
			}
		}
	}
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			tmp_beli[i][j].probability *= sensor(status, map[i][j].type);
}
double viterbi::sensor(char status, char map_status) {
	if (status == map_status)
		return SUCC_SENSE;
	else
		return FAIL_SENSE;
}
std::vector < std::vector <std::vector<beli_stur>>> viterbi::get_beli_status() {
	if (beli_status.size() || beli_status[0].size()) {
		std::cout << "[ERROR] init failed row " << beli_status.size() << std::endl;
		return this->beli_status;
	}
	int len_action = this->beli_status[0][0].size();
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			for (int k = 0; k < len_action; ++k)
				std::cout << this->beli_status[i][j][k].probability << "," << this->beli_status[i][j][k].parent.first << "-" << this->beli_status[i][j][k].parent.second << std::endl;
		}
	}
	return this->beli_status;
}

void viterbi::set_beli_status(std::vector<std::vector<beli_stur>>& tmp_beli) {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			beli_stur tmp = tmp_beli[i][j];
			this->beli_status[i][j].push_back(tmp);
		}
	}
}

std::vector<beli_stur> viterbi::get_mls() {
	int len_action = this->beli_status[0][0].size();
	beli_stur max_res = beli_status[0][0][len_action - 1];
	std::vector<beli_stur> mls;
	std::pair<int, int> parent = { -1,-1 };
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (this->beli_status[i][j][len_action - 1].probability > max_res.probability) {
				max_res.probability = this->beli_status[i][j][len_action - 1].probability;
				max_res.parent = { i,j };
				parent = this->beli_status[i][j][len_action - 1].parent;
			}
		}
	}
	if (parent == std::make_pair(-1, -1)) {
		std::cout << "end_point fail to find" << std::endl;
		return mls;
	}
	mls.push_back(max_res);
	for (int i = len_action - 2; i >= 0; --i) {
		int x = parent.first, y = parent.second;
		max_res.probability = this->beli_status[x][y][i].probability;
		max_res.parent = parent;
		parent = this->beli_status[x][y][i].parent;
		mls.push_back(max_res);
	}
	return mls;
}