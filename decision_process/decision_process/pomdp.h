#pragma once
#ifndef _POMDP_H_
#define _POMDP_H_
#include "decision_process.h"

class pomdp {
private:
	int row;
	int col;
	std::vector<int> error;
	std::vector<double> assign;
	std::vector<std::vector<double>> beli_status;
	bool initial(std::vector<std::vector<map_str>>&);
	void transition(std::vector<std::vector<map_str>>& map, std::vector<std::vector<double>>& tmp_beli, int action, char status);
	double sensor(char status, char map_status);
	void normalize(std::vector<std::vector<map_str>>& map);
	int calc_error(const std::pair<int, int>& location);
public:
	pomdp();
	void do_pomdp(std::vector<std::vector<map_str>>&, std::vector<std::pair<char, std::pair<int, int>>>&, std::vector<int>&);
	std::vector<std::vector<double>> get_beli_status();
	std::vector<int> get_error();
	std::vector<double> get_assi();
};
#endif // !_POMDP_H_

