#ifndef _AI_ACTION_H_
#define _AI_ACTION_H_
#include "decision_process.h"
#pragma once
#define ACT_NUM 100
class ai_action
{
private:
	int row;
	int col;
	std::vector<int> actions;
	std::vector<std::pair<char,std::pair<int,int>>> path;
	void gene_actions();
	int my_random();
	void gene_path(std::vector<std::vector<map_str>>& map, std::pair<int,int>& start);
public:
	ai_action(std::vector<std::pair<char,std::pair<int,int>>>& path, std::vector<int>& actions, std::vector<std::vector<map_str>>& orig_map, std::pair<int,int>& start);
	~ai_action();
};

#endif // !_AI_ACTION_H_

