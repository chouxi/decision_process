#ifndef _IN_MAP_H_
#define _IN_MAP_H_
#include "decision_process.h"

#pragma once
class in_map
{
public:
	in_map(std::vector<std::vector<map_str>>& origin, std::string map_file, std::vector<std::pair<int, int>>& start_goal);
	~in_map();
private:
	std::ifstream map_in;
};

#endif // !_IN_MAP_H_
