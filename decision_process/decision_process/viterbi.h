#pragma once
#ifndef _VITERBI_H_
#define _VITERBI_H_

#include "decision_process.h"
typedef struct _beli_stur_ {
	double probability= 0.0;
	std::pair<int, int> parent;
}beli_stur;

struct cmp
{
	bool operator () (const beli_stur& a, const beli_stur& b)const {
		return a.probability < b.probability;
	}
};
class viterbi
{
private:
	int row;
	int col;
	std::vector<int> error;
	std::vector < std::vector <std::vector<beli_stur>>> beli_status;
	bool initial(std::vector<std::vector<map_str>>& map);
	void transition(std::vector<std::vector<map_str>>& map, std::vector<std::vector<beli_stur>>& tmp_beli, int action, char status, int);
	double sensor(char status, char map_status);
	void set_beli_status(std::vector<std::vector<beli_stur>>& tmp_beli);
	std::vector<beli_stur> viterbi::out_mls(const std::pair<int,int>& mlp, int idx);
	std::vector<beli_stur> viterbi::get_mls(int count);
	void calc_error(std::vector<beli_stur>& , const std::vector<std::pair<int,int>>&);
public:
	viterbi();
	~viterbi();
	void do_viterbi(std::vector<std::vector<map_str>>& map, std::vector<std::pair<char, std::pair<int, int>>>& path, std::vector<int>& actions);
	std::vector < std::vector <std::vector<beli_stur>>> get_beli_status();
	std::vector<int> get_error();
};

#endif // !_VIETERBI_H_
