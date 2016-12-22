#ifndef _OUT_ACT_PTH_
#define _OUT_ACT_PTH_
#include "decision_process.h"
#pragma once
class out_act_pth
{
private:
	std::ofstream out_pth_file;
public:
	out_act_pth(std::string file_name, std::vector<std::pair<char, std::pair<int, int>>>& path, std::vector<int>& actions, std::pair<int,int> start);
	~out_act_pth();
};

#endif // !_OUT_ACT_PTH_
