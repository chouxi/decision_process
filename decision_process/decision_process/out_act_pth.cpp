#include "stdafx.h"
#include "out_act_pth.h"


out_act_pth::out_act_pth(std::string file_name, std::vector<std::pair<char, std::pair<int, int>>>& path, std::vector<int>& actions, std::pair<int, int> start)
{
	out_pth_file.open(file_name);
	if (!path.size() || !actions.size()) {
		std::cout << "[ERROR] no path in memory" << std::endl;
		return;
	}
	if (!out_pth_file.is_open()) {
		std::cout << "[ERROR] cannot open map file" << std::endl;
		return;
	}
	out_pth_file << start.first << "," << start.second << std::endl;
	for (int i = 0; i < path.size(); ++i) {
		out_pth_file << path[i].second.first << "," << path[i].second.second << " ";
	}
	out_pth_file << std::endl;
	for (int i = 0; i < actions.size(); ++i) {
		out_pth_file << dir_char[actions[i]] << " ";
	}
	out_pth_file << std::endl;
	for (int i = 0; i < path.size(); ++i)
		out_pth_file << path[i].first << " ";
	out_pth_file << std::endl;
}


out_act_pth::~out_act_pth()
{
	out_pth_file.close();
}
