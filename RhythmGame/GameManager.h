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
    static const int VERTICAL = 25; // ����
    static const int HORIZONAL = 50; // ����

    int level = 1;
    int hp = 10;
    int score = 0;
    int successfulInputs = 0;

    vector<string> notes; // �� ���� ���ڿ��� ó��

    int rainStepCounter = 0;
    string words[11] = { "����", "�׼�", "������", "ġŲ", "����", "�ܹ���", "���Ϳ�����", "�ֽĽ�", "�����", "�꼺��", "����ö"};

    void DropRain();
    void InputThread();
};

#endif