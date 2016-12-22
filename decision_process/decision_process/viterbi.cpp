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

void viterbi::do_viterbi(std::vector<std::vector<map_str>>& map, std::vector<std::pair<char, std::pair<int, int>>>& path, std::vector<int>& actions) {
	if (!initial(map)) return;
	int status_size = path.size();
	int action_size = actions.size();
	if (!status_size || status_size != action_size) return;
	std::vector<char> status(path.size(), '\0');
	std::vector<std::pair<int, int>> location(path.size());
	for (int i = 0; i < path.size(); ++i) {
		status[i] = path[i].first;
		location[i].first = path[i].second.first;
		location[i].second = path[i].second.second;
	}
	for (int i = 0; i < action_size; ++i) {
		std::vector<std::vector<beli_stur>> tmp_beli(row, std::vector<beli_stur>(col));
		transition(map, tmp_beli, actions[i], status[i], i);
		set_beli_status(tmp_beli);
		/*if (i == 9) {
			std::vector <beli_stur> mlp = get_mls(10);
			for (int i = 0; i < mlp.size(); ++i) {
				out_mls(mlp[i].parent, i);
			}
		}
		else if (i == 49) {
			std::vector <beli_stur> mlp = get_mls(10);
			for (int i = 0; i < mlp.size(); ++i) {
				out_mls(mlp[i].parent, i);
			}
		}
		else if (i == 99) {
			std::vector <beli_stur> mlp = get_mls(10);
			for (int i = 0; i < mlp.size(); ++i) {
				out_mls(mlp[i].parent, i);
			}
		}*/
	}
	std::vector <beli_stur> mlp = get_mls(0);
	std::vector<beli_stur> result;
	for (int i = 0; i < mlp.size(); ++i) {
		result = out_mls(mlp[i].parent, i);
	}
	/*for (int i = result.size() - 1; i >= 0; --i) {
		std::cout << result[i].parent.first << ","<< result[i].parent.second << " " << result[i].probability << std::endl;
	}*/
	std::reverse(result.begin(), result.end());
	calc_error(result, location);
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

std::vector<beli_stur> viterbi::out_mls(const std::pair<int,int>& mlp, int idx) {
	int len_action = this->beli_status[0][0].size();
	std::string out_file = "./ans/f/path_" + std::to_string(len_action) + "_" + std::to_string(idx) + ".txt";
	beli_stur max_res = beli_status[mlp.first][mlp.second][len_action - 1];
	std::vector<beli_stur> mls;
	std::pair<int, int> parent = max_res.parent;
	max_res.parent = { mlp.first, mlp.second };
	mls.push_back(max_res);
	for (int i = len_action - 2; i >= 0; --i) {
		int x = parent.first, y = parent.second;
		max_res.probability = this->beli_status[x][y][i].probability;
		max_res.parent = parent;
		parent = this->beli_status[x][y][i].parent;
		mls.push_back(max_res);
	}
	/*std::ofstream out_f;
	out_f.open(out_file);
	for (int i = mls.size() - 1; i >= 0; --i) {
		out_f << mls[i].parent.first << ","<< mls[i].parent.second << " " << mls[i].probability << std::endl;
	}
	out_f.close();*/
	return mls;
}
std::vector <beli_stur> viterbi::get_mls(int count) {
	int len_action = this->beli_status[0][0].size();
	beli_stur max_res = beli_status[0][0][len_action - 1];
	std::priority_queue<beli_stur, std::vector<beli_stur>, cmp> max_prob;
	std::vector<beli_stur> mls;
	std::pair<int, int> parent = { -1,-1 };
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			beli_stur tmp = this->beli_status[i][j][len_action - 1];
			tmp.parent = { i,j };
			max_prob.push(tmp);
		}
	}
	std::vector<beli_stur> result;
	while (count-- >= 0) {
		result.push_back(max_prob.top());
		max_prob.pop();
	}
	return result;
}

std::vector<int> viterbi::get_error() {
	return this->error;
}
void viterbi::calc_error(std::vector<beli_stur>& result, const std::vector<std::pair<int, int>>& locations) {
	this->error.resize(locations.size(), 0);
	result.erase(result.begin());
	for (int i = 0; i < result.size(); ++i) {
		std::pair<int, int> est_p = result[i].parent;
		error[i] = abs(est_p.first - locations[i].first) + abs(est_p.second - locations[i].second);
	}
}