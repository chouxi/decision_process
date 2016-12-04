#pragma once
#ifndef _POMDP_H_
#define _POMDP_H_
#include "decision_process.h"

class pomdp {
private:
	int row;
	int col;
	std::vector<std::vector<double>> beli_status;
	bool initial(std::vector<std::vector<map_str>>&);
	void transition(std::vector<std::vector<map_str>>& map, std::vector<std::vector<double>>& tmp_beli, int action, char status);
	double sensor(char status, char map_status);
	void normalize(std::vector<std::vector<map_str>>& map);
public:
	pomdp();
	void do_pomdp(std::vector<std::vector<map_str>>&, std::vector<char>&, std::vector<int>&);
	std::vector<std::vector<double>> get_beli_status();
};
#endif // !_POMDP_H_

