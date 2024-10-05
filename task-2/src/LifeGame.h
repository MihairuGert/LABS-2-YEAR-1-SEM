#pragma once
#include <chrono>
#include <thread>
#include "GameEngine.h"
#include "FileReader.h"
#include "InputInterpreter.h"
#include "Interface.h"

const int DEFAULT_SIZE = 25;

enum class GameStatus {EXIT = 0, CONTINUE = 1};

class LifeGame {
private:
    std::vector<int> birthCondition;
    std::vector<int> survivalCondition;
    int row;
    int column;
    Grid grid1;
    Grid grid2;
    std::string universeName;
public:
    void startGame(char** argv);
    bool parseLifeFile(char** argv);
    GameStatus processCmd(Cmd cmd, GameEngine gameEngine);
};
