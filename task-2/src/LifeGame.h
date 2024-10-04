#pragma once
#include <chrono>
#include <thread>
#include "GameEngine.h"
#include "FileReader.h"
#include "InputInterpreter.h"

const int DEFAULT_SIZE = 25;

class LifeGame {
private:
    std::vector<int> birthCondition;
    std::vector<int> survivalCondition;
    int row;
    int column;
    Grid grid1;
    Grid grid2;
public:
    void startGame(char** argv);
    bool parseLifeFile(char** argv);
};
