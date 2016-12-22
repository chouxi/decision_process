#ifndef _OUT_MAP_H_
#define _OUT_MAP_H_

#pragma once
#include "decision_process.h"
class out_map
{
public:
	out_map(std::vector<std::vector<map_str>> map, std::vector<std::pair<int, int>> start_goal, std::vector<std::pair<int, int>> hard_center, std::string map_file, int row, int col);
	~out_map();
private:
	std::ofstream out_m_file;
	void output_map(std::vector<std::vector<map_str>> map, std::vector<std::pair<int, int>> start_goal, std::vector<std::pair<int, int>> hard_center, int row, int col);
};


#endif // !_OUT_MAP_H_
