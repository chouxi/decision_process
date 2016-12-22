#include "stdafx.h"
#include "in_path.h"


in_path::in_path(std::string path_file, std::vector<std::pair<char, std::pair<int, int>>>& path, std::vector<int>& actions)
{
	path_in.open(path_file);
	if (path_in.is_open()) {
		int count = 0;
		char act_char[1024];
		char path_char[1024];
		char trash[1024];
		char location_char[1024];
		path_in.getline(trash, 1024);
		path_in.getline(location_char, 1024);
		path_in.getline(act_char, 1024);
		path_in.getline(path_char, 1024);
		int idx = 0;
		while (act_char[idx] != '\n' && act_char[idx] != '\0') {
			if (act_char[idx] == ' ') {
				++idx;
				continue;
			}
			for (int i = 0; i < 4; ++i) {
				if (act_char[idx] == dir_char[i]) {
					actions.push_back(i);
					++idx;
					break;
				}
			}
		}
		idx = 0;
		while (path_char[idx] != '\n' && path_char[idx] != '\0') {
			if (path_char[idx] == ' ') {
				++idx;
				continue;
			}
			else path.push_back({ path_char[idx], {} });
			++idx;
		}
		idx = 0;
		//read coordinates
		int vec_ptr = 0;
		int number[2] = {0,0};
		int navi = 0;
		while (location_char[idx] != '\n' && location_char[idx] != '\0') {
			if (location_char[idx] >= '0' && location_char[idx] <= '9') {
				number[navi] = number[navi] * 10 + (location_char[idx] - '0');
			}
			else if (location_char[idx] == ',') {
				++navi;
			}
			else if (location_char[idx] == ' ') {
				path[vec_ptr].second.first = number[0];
				path[vec_ptr].second.second = number[1];
				navi = 0;
				++vec_ptr;
				number[0] = 0;
				number[1] = 0;
			}
			++idx;
		}
	}
}


in_path::~in_path()
{
}
