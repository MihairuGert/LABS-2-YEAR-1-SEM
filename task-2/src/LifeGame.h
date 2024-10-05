#pragma once
#include <chrono>
#include <thread>
#include "GameEngine.h"
#include "FileReader.h"
#include "FilePrinter.h"
#include "InputInterpreter.h"
#include "Interface.h"

const int DEFAULT_SIZE = 25;

enum class GameStatus {EXIT = 0, CONTINUE = 1};
enum class ParseFileStatus {SUCCESS = 0, NO_NAME = 1, NO_CONDITIONS = 2, NO_SIZE = 3, NEGATIVE_CELL = 4, NO_FORMAT = 5};

class LifeGame {
private:
    std::vector<int> birthCondition;
    std::vector<int> survivalCondition;
    int row;
    int column;
    Grid grid1;
    Grid grid2;
    std::string universeName{};
    int iterationNum{};
    static void callHelp();
public:
    void startGame(char** argv);
    ParseFileStatus parseLifeFile(char** argv, bool* parseLifeFileStatus);
    void createLifeFile(const std::string& filename);
    GameStatus processCmd(Cmd cmd, GameEngine gameEngine, bool* parseLifeFileStatus);
};
