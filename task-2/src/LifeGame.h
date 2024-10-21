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
    static void createGliderGun(Grid& grid);
    static void createPulsar(Grid& grid);
    static void createRPentamino(Grid& grid);
    static void createLightWeightSS(Grid& grid);
    static void createBlockLayingSE(Grid& grid);
};

class LifeGame {
private:
    std::vector<int> birthCondition;
    std::vector<int> survivalCondition;
    int row;
    int column;
    Grid grid1;
    Grid grid2;
    std::string universeName{};
    std::string filename{};
    int iterationsOffline{};
    int iterationNum{};
    ParseFileStatus parseFileStatus;
    bool* parseLifeFileStatus;
    void createLifeFile(const std::string& filename);
    GameStatus processCmd(Cmd cmd, GameEngine gameEngine, bool* parseLifeFileStatus);
    void generateUniverse();
    static void callHelp();
    void runOffline(bool* parseLifeFileStatus);
    void runOnline(bool* parseLifeFileStatus);
public:
    LifeGame(std::vector<int> birthCondition, std::vector<int> survivalCondition,
             int row, int column, Grid grid1,std::string universeName, ParseFileStatus parseFileStatus,
             bool* parseLifeFileStatus, std::string filename = "", int iterationsOffline = 0);
    void startGame();
};
