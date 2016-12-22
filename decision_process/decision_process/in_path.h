#ifndef _IN_PATH_H_
#define _IN_PATH_H_
#include "decision_process.h"
#pragma once
class in_path
{
private:
	std::ifstream path_in;
public:
	in_path(std::string path_file, std::vector<std::pair<char, std::pair<int, int>>>& path, std::vector<int>& actions);
	~in_path();
};

#endif // !_IN_PATH_H_
