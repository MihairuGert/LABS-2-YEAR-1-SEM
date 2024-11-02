#pragma once
#include <random>
#include <cstring>
#include "GameEngine.h"
#include "FileReader.h"
#include "FilePrinter.h"
#include "Interface.h"

const int DEFAULT_SIZE = 50;

enum class GameStatus {EXIT = 0, CONTINUE};

class Generator {
public:
    void createGliderGun(Grid& grid);
    void createPulsar(Grid& grid);
    void createRPentamino(Grid& grid);
    void createLightWeightSS(Grid& grid);
    void createBlockLayingSE(Grid& grid);
};

class LifeGame {
private:
    std::vector<int> birthCondition;
    std::vector<int> survivalCondition;
    int row;
    int column;
    Grid grid;
    std::string universeName{};
    std::string filename{};
    int iterationsOffline{};
    int iterationNum{};
    ParseFileStatus parseFileStatus;
    bool* parsingErrors;
    void createLifeFile(const std::string& filename);
    GameStatus processCmd(Cmd cmd, GameEngine& gameEngine);
    void generateUniverse();
    static void callHelp();
    void runOffline();
    void runOnline();
public:
    LifeGame(std::vector<int> birthCondition, std::vector<int> survivalCondition,
             int row, int column, Grid grid, std::string universeName, ParseFileStatus parseFileStatus,
             bool* parseLifeFileStatus, std::string filename = "", int iterationsOffline = 0);
    void startGame();
};
