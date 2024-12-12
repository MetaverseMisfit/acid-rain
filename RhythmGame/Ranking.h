#include <cstdio>

struct PlayInfo {
	char name[200];
	int	nScored;
};
extern void loadRanking(const char* filename);
extern void storeRanking(const char* filename);
extern void printRanking();
extern int addRanking(int nScore);