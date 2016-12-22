// decision_process.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pomdp.h"
#include "viterbi.h"
#include "ai_map.h"
#include "out_map.h"
#include "ai_action.h"
#include "out_act_pth.h"
#include "in_map.h"
#include "in_path.h"
void eb() {
	std::vector<std::vector<double>> eb_ans(MAP_COUNT * START_COUNT, std::vector<double>(100, 0.0));
	for (int i = 0; i < MAP_COUNT; ++i) {
		std::string map_file = "";
		if (i == 9) {
			map_file = "./map/map_10.txt";
		}
		else {
			map_file = "./map/map_0" + std::to_string(i+1) + ".txt";
		}
		//std::string map_file = "./map/map_" + std::to_string(i) + ".txt";
		//std::string map_file = "./maps/map_" + std::to_string(i) + ".txt";
		decision_process *dp = new decision_process(120, 160, map_file);
		in_map *in_m = new in_map(dp->origin_map, dp->map_file, dp->start_goal);
		/*for (int i = 0; i < dp->origin_map.size(); ++i) {
			for (int j = 0; j < dp->origin_map[0].size(); ++j) {
				std::cout << dp->origin_map[i][j].type << ",";
			}
			std::cout << std::endl;
		}*/
		for (int j = 0; j < START_COUNT; ++j) {
			//std::string result_file = "./results/result_" + std::to_string(i) + "_" + std::to_string(j) + ".txt";
			int tmp = i * 10 + j + 1;
			std::string result_file = "";
			if (tmp < 10) {
				result_file = "./map/truth_00" + std::to_string(tmp)+ ".txt";
			}
			else if (tmp < 100) {
				result_file = "./map/truth_0" + std::to_string(tmp)+ ".txt";
			}else{
				result_file = "./map/truth_100.txt";
			}
			std::vector<std::pair<char, std::pair<int, int>>> path;
			std::vector<int> actions;
			in_path * in = new in_path(result_file, path, actions);
			delete in;
			pomdp *p = new pomdp();
			p->do_pomdp(dp->origin_map, path, actions);
			eb_ans[i*MAP_COUNT + j] = p->get_assi();
			delete p;
			std::cout << i << ", " << j << std::endl;
		}
		delete in_m;
		delete dp;
	}
	std::ofstream e("./ans/eb.txt");
	for (int i = 0; i < MAP_COUNT * START_COUNT; ++i) {
		for (int j = 0; j < 100; ++j) {
			e << eb_ans[i][j] << " ";
		}
		e << std::endl;
	}
	e.close();
	system("pause");

}
void e() {
	std::vector<std::vector<int>> e_ans(MAP_COUNT * START_COUNT, std::vector<int>(100, 0));
	for (int i = 0; i < MAP_COUNT; ++i) {
		std::string map_file = "./maps/map_" + std::to_string(i) + ".txt";
		decision_process *dp = new decision_process(120, 160, map_file);
		in_map *in_m = new in_map(dp->origin_map, dp->map_file, dp->start_goal);
		/*for (int i = 0; i < dp->origin_map.size(); ++i) {
			for (int j = 0; j < dp->origin_map[0].size(); ++j) {
				std::cout << dp->origin_map[i][j].type << ",";
			}
			std::cout << std::endl;
		}*/
		for (int j = 0; j < START_COUNT; ++j) {
			std::string result_file = "./results/result_" + std::to_string(i) + "_" + std::to_string(j) + ".txt";
			std::vector<std::pair<char, std::pair<int, int>>> path;
			std::vector<int> actions;
			in_path * in = new in_path(result_file, path, actions);
			delete in;
			pomdp *p = new pomdp();
			p->do_pomdp(dp->origin_map, path, actions);
			e_ans[i*MAP_COUNT + j] = p->get_error();
			delete p;
			std::cout << i << ", " << j << std::endl;
		}
		delete in_m;
		delete dp;
	}
	std::ofstream e("./ans/e.txt");
	for (int i = 0; i < MAP_COUNT * START_COUNT; ++i) {
		for (int j = 0; j < 100; ++j) {
			e << e_ans[i][j] << " ";
		}
		e << std::endl;
	}
	e.close();
	system("pause");
}
void d() {
	std::string map_file = "./maps/map_0.txt";
	decision_process *dp = new decision_process(120, 160, map_file);
	in_map *in_m = new in_map(dp->origin_map, dp->map_file, dp->start_goal);
	std::string result_file = "./results/result_0_0.txt";
	std::vector<std::pair<char, std::pair<int, int>>> path;
	std::vector<int> actions;
	in_path * in = new in_path(result_file, path, actions);
	delete in;
	delete in_m;
	pomdp *p = new pomdp();
	p->do_pomdp(dp->origin_map, path, actions);
	delete p;
	delete dp;
}
void f() {
	std::string map_file = "./maps/map_1.txt";
	decision_process *dp = new decision_process(120, 160, map_file);
	in_map *in_m = new in_map(dp->origin_map, dp->map_file, dp->start_goal);
	std::string result_file = "./results/result_1_0.txt";
	std::vector<std::pair<char, std::pair<int, int>>> path;
	std::vector<int> actions;
	in_path * in = new in_path(result_file, path, actions);
	delete in;
	delete in_m;
	std::vector<char> status(path.size(), '\0');
	for (int i = 0; i < path.size(); ++i) {
		status[i] = path[i].first;
	}
	viterbi *v = new viterbi();
	//v->do_viterbi(dp->origin_map, status, actions);
	system("pause");
	delete v;
	delete dp;
}
void g() {
	std::vector<std::vector<int>> g_ans(MAP_COUNT * START_COUNT, std::vector<int>(100, 0));
	for (int i = 0; i < MAP_COUNT; ++i) {
		//std::string map_file = "./maps/map_" + std::to_string(i) + ".txt";
		std::string map_file = "";
		if (i == 9) {
			map_file = "./map/map_10.txt";
		}
		else {
			map_file = "./map/map_0" + std::to_string(i+1) + ".txt";
		}
		decision_process *dp = new decision_process(120, 160, map_file);
		in_map *in_m = new in_map(dp->origin_map, dp->map_file, dp->start_goal);
		for (int j = 0; j < START_COUNT; ++j) {
			//std::string result_file = "./results/result_" + std::to_string(i) + "_" + std::to_string(j) + ".txt";
			int tmp = i * 10 + j + 1;
			std::string result_file = "";
			if (tmp < 10) {
				result_file = "./map/truth_00" + std::to_string(tmp)+ ".txt";
			}
			else if (tmp < 100) {
				result_file = "./map/truth_0" + std::to_string(tmp)+ ".txt";
			}
			else {
				result_file = "./map/truth_100.txt";
			}
			std::vector<std::pair<char, std::pair<int, int>>> path;
			std::vector<int> actions;
			in_path * in = new in_path(result_file, path, actions);
			delete in;
			viterbi *v = new viterbi();
			v->do_viterbi(dp->origin_map, path, actions);
			g_ans[i*MAP_COUNT + j] = v->get_error();
			delete v;
			/*for(int k = 0; k < g_ans[i*MAP_COUNT + j].size(); ++ k){
				std::cout << g_ans[i*MAP_COUNT + j][k] << ",";
			}*/
			std::cout << std::endl<< i << ", " << j << std::endl;
		}
		delete in_m;
		delete dp;
	}
	std::ofstream g("./ans/g_new.txt");
	for (int i = 0; i < MAP_COUNT * START_COUNT; ++i) {
		for (int j = 0; j < 100; ++j) {
			g << g_ans[i][j] << " ";
		}
		g << std::endl;
	}
	g.close();
	system("pause");
}
int main()
{
	//e();
	//eb();
	//d();
	//f();
	g();
	/*std::vector<int> actions = { RIGHT, RIGHT, DOWN, DOWN };
	std::vector<char> status = { NORMAL, NORMAL, HIGH_WAY, HIGH_WAY };
	std::vector < std::vector<map_str >> map = { {{HIGH_WAY}, {HIGH_WAY}, {HARD}}
										,{{NORMAL}, {NORMAL}, {NORMAL}},
										{{NORMAL},{BLOCK},{HIGH_WAY}} };
	std::vector<std::pair<char, std::pair<int, int>>> path(status.size());
	for (int i = 0; i < status.size(); ++i) {
		path[i].first = status[i];
	}
	viterbi *v = new viterbi();
	v->do_viterbi(map, path, actions);
	delete v;
	system("pause");*/
	/*for (int i = 0; i < MAP_COUNT; ++i) {
		std::string map_file = "./maps/map_" + std::to_string(i) + ".txt";
		decision_process *dp = new decision_process(120, 160, map_file);
		ai_map *m = new ai_map(dp->row, dp->col, dp->origin_map, dp->start_goal, dp->hard_center, START_COUNT);
		out_map * out = new out_map(dp->origin_map, dp->start_goal, dp->hard_center, dp->map_file, dp->row, dp->col);
		for (int j = 0; j < START_COUNT; ++j) {
			std::string result_file = "./results/result_" + std::to_string(i) + "_" + std::to_string(j) + ".txt";
			std::vector<std::pair<char, std::pair<int, int>>> path;
			std::vector<int> actions;
			ai_action * a_act = new ai_action(path, actions, dp->origin_map, dp->start_goal[j]);
			out_act_pth * out_act = new out_act_pth(result_file, path, actions, dp->start_goal[j]);
			delete a_act;
			delete out_act;
		}
		delete m;
		delete out;
		delete dp;
	}*/
    return 0;
}

