#include "GameManager.h"
#include "Ranking.h"
#include <fmod.hpp>
#include <conio.h>
#include <chrono>
#include <thread>
#include <cmath>
#include <string>
#include <iostream>
#include <windows.h>

using namespace std;

GameManager::GameManager() {
    notes.resize(VERTICAL, string(HORIZONAL, ' '));
}

void MoveCursorTo(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameManager::Start() {
    string input;
    int mode;

    while (true) {

        printf("===============================================================================\n\n");
        printf("  ###      ####    ######  #####             ######     ###     ######  ##   ##\n");
        printf(" ## ##    ##  ##   # ## #  ##  ##            ##   ##   ## ##    # ## #  ###  ##\n");
        printf("##   ##  ##          ##    ##   ##           ##   ##  ##   ##     ##    #### ##\n");
        printf("##   ##  ##          ##    ##   ##           ##  ###  ##   ##     ##    #######\n");
        printf("#######  ##          ##    ##   ##           #####    #######     ##    ## ####\n");
        printf("##   ##   ##  ##   # ## #  ##  ##            ## ###   ##   ##   # ## #  ##  ###\n");
        printf("##   ##    ####    ######  #####             ##  ###  ##   ##   ######  ##   ##\n\n");
        printf("===============================================================================\n\n");

        cout << "                                  산 성 비\n" << endl;
        cout << "                            [ 1 ] 게임 시작" << endl;
        cout << "                            [ 2 ] 랭킹" << endl;
        cout << "                            [ 3 ] 나가기\n" << endl;
        cout << "선택하기: ";

        getline(cin, input);

        if (input.length() != 1 || !isdigit(input[0])) {
            cout << "\n대머리깎아라\n" << endl;
            _getch();
            system("cls");
            continue;
        }

        mode = input[0] - '0';

        switch (mode) {
        case 1:
            system("cls");
            PlayGame();
            return;

        case 2:
            system("cls");
            printRanking();
            cout << "\n아무키나 눌러 전 단계로 돌아갑니다.\n";
            _getch();
            system("cls");
            continue;

        case 3:
            cout << "\n안녕히 가세요.\n" << endl;
            return;

        default:
            cout << "\n잘못된 입력입니다. 아무키나 눌러 전 단계로 돌아갑니다.\n" << endl;
            _getch();
            system("cls");
            continue;
        }
    }
}

void GameManager::PlayGame() {
    auto lastUpdate = chrono::steady_clock::now();

    thread inputThread(&GameManager::InputThread, this);

    while (true) {
        auto currentTime = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(currentTime - lastUpdate).count();

        // 화면 갱신
        if (elapsed >= (1000 - (level - 1) * 60)) {
            MoveCursorTo(0, 0); // 커서 이동
            DropRain(); // 비 내리기
            DisplayRains(); // 비 화면에 표시
            lastUpdate = currentTime;
        }

        if (successfulInputs >= 3) {
            level++;
            successfulInputs = 0;
        }

        if (hp <= 0) {
            system("cls");

            cout << " ::::::::      :::     ::::    ::::  ::::::::::   ::::::::  :::     ::: :::::::::: :::::::::  " << endl;
            cout << ":+:    :+:   :+: :+:   +:+:+: :+:+:+ :+:         :+:    :+: :+:     :+: :+:        :+:    :+: " << endl;
            cout << "+:+         +:+   +:+  +:+ +:+:+ +:+ +:+         +:+    +:+ +:+     +:+ +:+        +:+    +:+ " << endl;
            cout << ":#:        +#++:++#++: +#+  +:+  +#+ +#++:++#    +#+    +:+ +#+     +:+ +#++:++#   +#++:++#:  " << endl;
            cout << "+#+   +#+# +#+     +#+ +#+       +#+ +#+         +#+    +#+  +#+   +#+  +#+        +#+    +#+ " << endl;
            cout << "#+#    #+# #+#     #+# #+#       #+# #+#         #+#    #+#   #+#+#+#   #+#        #+#    #+# " << endl;
            cout << " ########  ###     ### ###       ### ##########   ########      ###     ########## ###    ### " << endl;

            _getch();

            int rank = addRanking(score);

            storeRanking("ranking.txt");

            break;
        }

        MoveCursorTo(0, VERTICAL - 2);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "레벨: " << level << "  HP: " << hp << "  점수: " << score << "  " << endl;
        cout << "입력 : ";
        this_thread::sleep_for(chrono::milliseconds(10));
    }

    inputThread.join();

    int rank = addRanking(score);

    storeRanking("ranking.txt");


    system("cls");

    Start();
}

void GameManager::DropRain() {
    rainStepCounter++;

    for (int row = VERTICAL - 1; row > 0; --row) {
        for (int col = 0; col < HORIZONAL; ++col) {
            notes[row][col] = notes[row - 1][col];
        }
    }

    for (int col = 0; col < HORIZONAL; ++col) {
        notes[0][col] = ' ';
    }

    for (int col = 0; col < HORIZONAL; ++col) {
        if (notes[VERTICAL - 2][col] != ' ') {
            hp--;
            return;
        }
    }

    if (rainStepCounter >= 3) {

        int startCol = rand() % (HORIZONAL - 6);
        const string& newWord = words[rand() % 11];

        rainStepCounter = 0;

        for (size_t i = 0; i < newWord.size() && startCol + i < HORIZONAL; ++i) {
            notes[0][startCol + i] = newWord[i];
        }
    }
}

void GameManager::DisplayRains() const {
    for (int row = 0; row < VERTICAL; ++row) {
        for (int col = 0; col < HORIZONAL; ++col) {
            cout << notes[row][col];
        }
        cout << endl;
    }
}

void GameManager::ProcessInput(const string& input) {
    for (int row = VERTICAL - 1; row >= 0; --row) {
        size_t pos = notes[row].find(input);
        if (pos != string::npos) {
            notes[row].replace(pos, input.size(), input.size(), ' ');
            successfulInputs++;
            score += 10;
            return;
        }
    }
}

void GameManager::InputThread() {
    string input;

    while (true) {
        getline(cin, input);
        ProcessInput(input);
        system("cls");
    }
}