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

void pomdp::do_pomdp(std::vector<std::vector<map_str>>& map, std::vector<std::pair<char, std::pair<int, int>>>& path, std::vector<int>& actions) {
	if (!initial(map)) return;
	std::vector<char> status(path.size(), '\0');
	std::vector<std::pair<int, int>> location(path.size());
	for (int i = 0; i < path.size(); ++i) {
		status[i] = path[i].first;
		location[i].first = path[i].second.first;
		location[i].second = path[i].second.second;
	}
	int status_size = status.size();
	int action_size = actions.size();
	if (!status_size || status_size != action_size) return;
	//error.resize(action_size, 0);
	assign.resize(action_size, 0);
	for (int i = 0; i < action_size; ++i) {
		std::vector<std::vector<double>> tmp_beli(row, std::vector<double>(col, 0.0));;
		transition(map, tmp_beli, actions[i], status[i]);
		this->beli_status = tmp_beli;
		normalize(map);
		//assign[i] = this->beli_status[location[i].first][location[i].second];
		if (i == 9) {
			std::vector<std::vector<double>> tmp = get_beli_status();
			std::ofstream tmp_f("./ans/d_10.txt");
			for (int i = 0; i < tmp.size(); ++i) {
				for (int j = 0; j < tmp[0].size(); ++j) {
					tmp_f << tmp[i][j] << ",";
				}
				tmp_f << std::endl;
			}
			tmp_f.close();
		}
		else if (i == 49) {
			std::vector<std::vector<double>> tmp = get_beli_status();
			std::ofstream tmp_f("./ans/d_50.txt");
			for (int i = 0; i < tmp.size(); ++i) {
				for (int j = 0; j < tmp[0].size(); ++j) {
					tmp_f << tmp[i][j] << ",";
				}
				tmp_f << std::endl;
			}
			tmp_f.close();
		}
		else if (i == 99) {
			std::vector<std::vector<double>> tmp = get_beli_status();
			std::ofstream tmp_f("./ans/d_100.txt");
			for (int i = 0; i < tmp.size(); ++i) {
				for (int j = 0; j < tmp[0].size(); ++j) {
					tmp_f << tmp[i][j] << ",";
				}
				tmp_f << std::endl;
			}
			tmp_f.close();
		}
		//error[i] = calc_error(location[i]);
		//get_beli_status();
	}
	//get_beli_status();
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

int pomdp::calc_error(const std::pair<int, int>& location) {
	double max_beli = DBL_MIN;
	std::pair<int, int> max_p = { -1,-1 };
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (this->beli_status[i][j] > max_beli) {
				max_beli = this->beli_status[i][j];
				max_p = { i, j };
			}
		}
	}
	return (abs(max_p.first - location.first) + abs(max_p.second - location.second));
}

std::vector<int> pomdp::get_error() {
	return this->error;
}
std::vector<double> pomdp::get_assi() {
	return this->assign;
}
