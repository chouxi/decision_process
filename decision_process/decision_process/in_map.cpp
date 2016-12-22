#include "stdafx.h"
#include "in_map.h"


in_map::in_map(std::vector<std::vector<map_str>>& origin, std::string map_file, std::vector<std::pair<int, int>>& start_goal)
{
	map_in.open(map_file);
	if (map_in.is_open()) {
		if (!start_goal.size()) {
			start_goal.push_back({0,0});
			start_goal.push_back({0,0});
		}
		origin.clear();
		int count = 0;
		char points_string[2][1024];
		char trash[1024];
		/*while (count++ < 11) {
			map_in.getline(trash, 1024);
		}*/
		while (!map_in.eof()) {
			std::vector<map_str> tmp;
			char file_c;
			do {
				map_in.get(file_c);
				map_str tmp_str;
				int count = 0;
				while (file_c != ',' && file_c != '\n' ) {
					if (!count) {
						tmp_str.type = file_c;
						tmp_str.highway_num = '0';
						count++;
					}
					else {
						tmp_str.highway_num = file_c;
					}
					map_in.get(file_c);
				}
				tmp.push_back(tmp_str);
			} while (file_c != '\n');
			if (tmp.size() == 1) break;
			origin.push_back(tmp);
		}
	}
}


in_map::~in_map()
{
	map_in.close();
}
