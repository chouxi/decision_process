// decision_process.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pomdp.h"

int main()
{
	pomdp *p = new pomdp();
	std::vector<int> actions = { RIGHT, RIGHT, DOWN, DOWN };
	std::vector<char> status = { NORMAL, NORMAL, HIGH_WAY, HIGH_WAY };
	std::vector < std::vector<map_str >> map = { {{HIGH_WAY}, {HIGH_WAY}, {HARD}}
										,{{NORMAL}, {NORMAL}, {NORMAL}},
										{{NORMAL},{BLOCK},{HIGH_WAY}} };
	p->do_pomdp(map, status, actions);
	system("pause");
	delete p;
    return 0;
}

