// decision_process.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pomdp.h"
#include "viterbi.h"

int main()
{
	std::vector<int> actions = { RIGHT, RIGHT, DOWN, DOWN };
	std::vector<char> status = { NORMAL, NORMAL, HIGH_WAY, HIGH_WAY };
	std::vector < std::vector<map_str >> map = { {{HIGH_WAY}, {HIGH_WAY}, {HARD}}
										,{{NORMAL}, {NORMAL}, {NORMAL}},
										{{NORMAL},{BLOCK},{HIGH_WAY}} };
	/*pomdp *p = new pomdp();
	p->do_pomdp(map, status, actions);*/
	viterbi *v = new viterbi();
	v->do_viterbi(map, status, actions);
	system("pause");
	delete v;
    return 0;
}

