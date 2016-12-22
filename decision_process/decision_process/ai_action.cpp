#include "stdafx.h"
#include "ai_action.h"


ai_action::ai_action(std::vector<std::pair<char,std::pair<int,int>>>& path, std::vector<int>& actions, std::vector<std::vector<map_str>>& orig_map, std::pair<int,int>& start)
{
	row = orig_map.size();
	if (!row) return;
	col = orig_map[0].size();
	if (!col) return;
	gene_actions();
	gene_path(orig_map, start);
	path = this->path;
	actions = this->actions;
	
}


ai_action::~ai_action()
{
}
void ai_action::gene_actions() {
	for (int i = 0; i < ACT_NUM; ++i)
		actions.push_back(my_random() % 4);
}

void ai_action::gene_path(std::vector<std::vector<map_str>>& map, std::pair<int,int>& start) {
	std::pair<int, int> cur = start;
	for (int i = 0; i < actions.size(); ++i) {
		int rnd = my_random() % 10;
		if (rnd <= 8) {
			int x = cur.first + direction[actions[i]].first, y = cur.second + direction[actions[i]].second;
			if (x >= 0 && x < row && y >= 0 && y < col && map[x][y].type != BLOCK) {
				cur.first = x;
				cur.second = y;
			}
		}
		rnd = my_random() % 20;
		char real_stat = map[cur.first][cur.second].type;
		if (rnd == 18) {
			if (real_stat == NORMAL)
				real_stat = HIGH_WAY;
			else if (real_stat == HIGH_WAY)
				real_stat = NORMAL;
			else if (real_stat == HARD)
				real_stat = NORMAL;
		}
		else if (rnd == 19) {
			if (real_stat == NORMAL)
				real_stat = HARD;
			else if (real_stat == HIGH_WAY)
				real_stat = HARD;
			else if (real_stat == HARD)
				real_stat = HIGH_WAY;
		}
		path.push_back({ real_stat, cur });
	}
}
int ai_action::my_random() {
	int rnum = 0;
#if defined _MSC_VER
#if defined _WIN32_WCE
	CeGenRandom(sizeof(int), (PBYTE)&rnum);
#else
	HCRYPTPROV hProvider = 0;
	const DWORD dwLength = sizeof(int);
	BYTE pbBuffer[dwLength] = {};
	DWORD result = ::CryptAcquireContext(&hProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	assert(result);
	result = ::CryptGenRandom(hProvider, dwLength, pbBuffer);
	rnum = *(int*)pbBuffer;
	assert(result);
	::CryptReleaseContext(hProvider, 0);
#endif
#elif defined __GNUC__
	int fd = open("/dev/urandom", O_RDONLY);
	if (fd != -1) {
		(void)read(fd, (void *)&rnum, sizeof(int));
		(void)close(fd);
	}
#endif
	if (rnum < 0) rnum = 0 - rnum;
	return rnum;
}