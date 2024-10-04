#pragma once
#include "GameEngine.h"
#include <chrono>
#include <thread>

class LifeGame {
private:
    std::vector<int> birthCondition;
    std::vector<int> survivalCondition;
    int row;
    int column;
    Grid grid1;
    Grid grid2;
public:
    void startGame();
    LifeGame(int column, int row);
};
