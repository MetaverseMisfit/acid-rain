#define _CRT_SECURE_NO_WARNINGS
#include "Ranking.h"
#include <cstdio>
#include <cstring>

using namespace std;

#define NUM_MVP 10
static PlayInfo MVP[NUM_MVP];
static int nMVP = NUM_MVP;

static void initRanking() {
	PlayInfo noname = { "조현철", 10 };
	for (int i = 0; i < nMVP; i++)
		MVP[i] = noname;
}

void loadRanking(const char* fname) {
	FILE* fp = fopen(fname, "r");
	if (fp == NULL)
		initRanking();
	else {
		for (int i = 0; i < nMVP; i++)
			fscanf(fp, "%s %d", MVP[i].name, &MVP[i].nScored);
		fclose(fp);
	}
}
void storeRanking(const char* fname) {
    FILE* fp = fopen(fname, "w");
    if (fp == NULL) return;
    for (int i = 0; i < nMVP; i++) {
        fprintf(fp, "%-16s %4d\n", MVP[i].name, MVP[i].nScored);
    }
    fclose(fp);
}

void printRanking() {
    printf("===================================================\n\n");
    printf("######     #    #     # #    # ### #     #  #####  \n");
    printf("#     #   # #   ##    # #   #   #  ##    # #     # \n");
    printf("#     #  #   #  # #   # #  #    #  # #   # #       \n");
    printf("######  #     # #  #  # ###     #  #  #  # #  #### \n");
    printf("#   #   ####### #   # # #  #    #  #   # # #     # \n");
    printf("#    #  #     # #    ## #   #   #  #    ## #     # \n");
    printf("#     # #     # #     # #    # ### #     #  #####  \n");
    printf("\n===================================================\n\n");

    for (int i = 0; i < nMVP; i++) {
        if (i < 3) {
            printf(" ㅁ-----ㅁ\n");
            printf(" | %2d위  | 개지리는 %-16s %4d \n", i + 1, MVP[i].name, MVP[i].nScored);
            printf(" ㅁ-----ㅁ\n");
        }
        else
        printf(" [%2d위] %-16s %4d \n", i + 1, MVP[i].name, MVP[i].nScored);
    }
}

int addRanking(int nScore) {
    if (nScore > MVP[nMVP - 1].nScored) {
        int pos = nMVP - 1;
        for (; pos > 0; pos--) {
            if (nScore <= MVP[pos - 1].nScored) break;
            MVP[pos] = MVP[pos - 1];
        }
        MVP[pos].nScored = nScore;
        printf("%d위를 달성했습니다! 이름 : ", pos + 1);
        scanf("%s", MVP[pos].name);
        return pos + 1;
    }
    return 0;
}