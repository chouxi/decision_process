#pragma once
#ifndef _DECISION_PROCESS_H_
#define _DECISION_PROCESS_H_
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
//random algorithm dependency
#include "Windows.h"
#include "Winbase.h"
#include "BaseTsd.h"
#include "WinDef.h"
#include "WinNT.h"
#include "Wincrypt.h"
#include <assert.h>

#define HARD 'T'
#define HIGH_WAY 'H'
#define NORMAL 'N'
#define BLOCK 'B'
#define RIGHT 2
#define LEFT 3
#define UP 1
#define DOWN 0
#define SUCC_MOVE 0.9
#define SUCC_SENSE 0.9
#define FAIL_SENSE 0.05
#define MAP_COUNT 10
#define START_COUNT 10

const static std::pair<int, int> direction [4] = { {1,0},{-1,0},{0,1},{0,-1} };
const static char dir_char [4] = { 'D','U','R','L' };
typedef struct _map_str_ {
	char type;
	char highway_num;
}map_str;

class decision_process
{
public:
	int row;
	int col;
	float route_cost;
	std::string map_file;
	std::vector<std::vector<map_str>> origin_map;
	std::vector<std::pair<int, int>> hard_center;
	std::vector<std::pair<int, int>> start_goal;
	std::vector<std::pair<int, int>> path;
	decision_process(int row, int col, std::string map_file) {
		this->row = row;
		this->col = col;
		this->map_file = map_file;
	}
	~decision_process() {}
};

#endif // !_DECISION_PROCESS_H_

