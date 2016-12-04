#pragma once
#ifndef _VITERBI_H_
#define _VITERBI_H_

#include "decision_process.h"
typedef struct _beli_stur_ {
	double probability= 0.0;
	std::pair<int, int> parent;
}beli_stur;

class viterbi
{
private:
	int row;
	int col;
	std::vector < std::vector <std::vector<beli_stur>>> beli_status;
	bool initial(std::vector<std::vector<map_str>>& map);
	void transition(std::vector<std::vector<map_str>>& map, std::vector<std::vector<beli_stur>>& tmp_beli, int action, char status, int);
	double sensor(char status, char map_status);
	void set_beli_status(std::vector<std::vector<beli_stur>>& tmp_beli);
	std::vector<beli_stur> viterbi::get_mls();
public:
	viterbi();
	~viterbi();
	void do_viterbi(std::vector<std::vector<map_str>>& map, std::vector<char>& status, std::vector<int>& actions);
	std::vector < std::vector <std::vector<beli_stur>>> get_beli_status();
};

#endif // !_VIETERBI_H_
