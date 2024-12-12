#include "GameManager.h"
#include "Ranking.h"
#include "fmod.hpp"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    GameManager game;

    const char* rk = "ranking.txt";
    loadRanking(rk);
    const char* wd = "words.txt";

    game.Start();

    return 0;
}