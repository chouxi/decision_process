#include "stdafx.h"
#include "pomdp.h"
pomdp::pomdp() {}
bool pomdp::initial(std::vector<std::vector<map_str>>& map) {
	this->row = map.size();
	if (!row) return false;
	this->col = map[0].size();
	if (!col) return false;
	this->beli_status.resize(row, std::vector<double>(col, 0.0));
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
				this->beli_status[i][j] = ini_prob;
		}
	}
	return true;
}

void pomdp::do_pomdp(std::vector<std::vector<map_str>>& map, std::vector<char>& status, std::vector<int>& actions) {
	if (!initial(map)) return;
	int status_size = status.size();
	int action_size = actions.size();
	if (!status_size || status_size != action_size) return;
	for (int i = 0; i < action_size; ++i) {
		std::vector<std::vector<double>> tmp_beli(row, std::vector<double>(col, 0.0));;
		transition(map, tmp_beli, actions[i], status[i]);
		this->beli_status = tmp_beli;
		normalize(map);
		get_beli_status();
		std::cout << std::endl;
		//get_beli_status();
	}
}

void pomdp::transition(std::vector<std::vector<map_str>>& map, std::vector<std::vector<double>>& tmp_beli, int action, char status) {
	if (action < 0 || action > 3) return;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (map[i][j].type == BLOCK)
				continue;
			int x = i + direction[action].first, y = j + direction[action].second;
			if (x < 0 || x >= row || y < 0 || y >= col || map[x][y].type == BLOCK) {
				tmp_beli[i][j] += this->beli_status[i][j];
				continue;
			}
			else {
				tmp_beli[x][y] += SUCC_MOVE * this->beli_status[i][j];
				tmp_beli[i][j] += (1 - SUCC_MOVE) * this->beli_status[i][j];
			}
		}
	}
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			tmp_beli[i][j] *= sensor(status, map[i][j].type);
}
double pomdp::sensor(char status, char map_status) {
	if (status == map_status)
		return SUCC_SENSE;
	else
		return FAIL_SENSE;
}
std::vector<std::vector<double>> pomdp::get_beli_status() {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			std::cout << this->beli_status[i][j] << ",";
		}
			std::cout << "\n";
	}
	return this->beli_status;
}

void pomdp::normalize(std::vector<std::vector<map_str>>& map) {
	int count = 0;
	double sum = 0.0;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (map[i][j].type == BLOCK)
				continue;
			sum += this->beli_status[i][j];
		}
	}
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (map[i][j].type == BLOCK)
				continue;
			this->beli_status[i][j] /= sum;
		}
	}
}
