#ifndef AI_MAP_H
#define AI_MAP_H
#include "decision_process.h"
#include <algorithm>
class ai_map
{
public:
    ai_map(int row, int col, std::vector<std::vector<map_str>> &origin_map, std::vector<std::pair<int,int>>& start_goal, std::vector<std::pair<int,int>>& hard_center, int goal_count);
    ~ai_map();
private:
    int col;
    int row;
	int goal_count;
    std::vector<std::vector<map_str>> origin_map;
	std::vector<std::pair<int, int>> hard_center;
	std::vector<std::pair<int, int>> start_goal;
    std::vector<std::vector<map_str>> highway_map;
    std::vector<std::vector<map_str>> highway_tmp_map;
    void start_generate();
    void generate_unblock();
    void generate_hard();
    bool generate_highway();
    bool generate_one_highway(int);
	bool check_highway(int, int, int);
	bool diff_direction(int start_x, int start_y, int direction, std::pair<int,int> & dest, int );
	bool move_next(int direction, std::pair<int, int> & dest, int& count, int );
    void generate_block();
    void generate_start_goal();
	bool check_bound(std::pair<int,int>&);
	int my_random();
};

#endif // AI_MAP_H