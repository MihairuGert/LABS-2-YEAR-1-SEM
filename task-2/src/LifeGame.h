#pragma once
#include "GameEngine.h"
#include <chrono>
#include <thread>

class LifeGame {
private:
    int birthRule[8] = {0};
    int survivalRule[8] = {0};
    int row;
    int column;
    Grid grid1;
    Grid grid2;
public:
    void startGame();
    LifeGame(int column, int row);
};
