#pragma once
#ifndef _DECISION_PROCESS_H_
#define _DECISION_PROCESS_H_
#include <vector>
#include <iostream>

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

const static std::pair<int, int> direction [4] = { {1,0},{-1,0},{0,1},{0,-1} };
typedef struct _map_str_ {
	char type;
}map_str;

#endif // !_DECISION_PROCESS_H_

