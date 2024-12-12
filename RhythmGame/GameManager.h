#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class GameManager {
public:
    GameManager();

    void Start();
    void PlayGame();
    void DisplayRains() const;
    void ProcessInput(const string& input);

private:
    static const int VERTICAL = 25; // 높이
    static const int HORIZONAL = 50; // 넓이

    int level = 1;
    int hp = 10;
    int score = 0;
    int successfulInputs = 0;

    vector<string> notes; // 각 행을 문자열로 처리

    int rainStepCounter = 0;
    string words[11] = { "계명대", "겜소", "임지원", "치킨", "피자", "햄버거", "몬스터에너지", "핫식스", "레드불", "산성비", "조현철"};

    void DropRain();
    void InputThread();
};

#endif