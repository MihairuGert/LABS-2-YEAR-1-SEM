#pragma once
#include <random>
#include <cstring>
#include "GameEngine.h"
#include "FileReader.h"
#include "FilePrinter.h"
#include "InputInterpreter.h"
#include "Interface.h"

const int DEFAULT_SIZE = 50;

enum class GameStatus {EXIT = 0, CONTINUE};
enum class ParseFileStatus {SUCCESS = 0, NO_FORMAT};

class Generator {
public:
    static void createGliderGun(Grid& grid);
    static void createPulsar(Grid& grid);
    static void createRPentamino(Grid& grid);
    static void createLightWeightSS(Grid& grid);
    static void createBlockLayingSE(Grid& grid);
};

class Parser {
public:
    static void processName(std::string& fileLine, bool *parseLifeFileStatus, bool& isSuccessGetLine, std::string& universeName);
    static void processConditions(std::string& fileLine, bool *parseLifeFileStatus, bool& isSuccessGetLine,
                           std::vector<int>& birthCondition, std::vector<int>& survivalCondition);
    static void processSize(std::string& fileLine, bool *parseLifeFileStatus, bool& isSuccessGetLine,
                     int& column, int& row, Grid& grid1, Grid& grid2);
    static void processCells(std::string& fileLine, bool *parseLifeFileStatus, bool& isSuccessGetLine,
                      int& column, int& row, Grid& grid1);
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
    int iterationNum{};
    ParseFileStatus parseLifeFile(char** argv, bool* parseLifeFileStatus);
    void createLifeFile(const std::string& filename);
    GameStatus processCmd(Cmd cmd, GameEngine gameEngine, bool* parseLifeFileStatus);
    void generateUniverse();
    static void processConsole(int argc, char** argv, int& iterations, std::string& filename);
    static void callHelp();
    void runOffline(int argc, char** argv, bool* parseLifeFileStatus);
    void runOnline(bool* parseLifeFileStatus);
public:
    void startGame(int argc, char** argv);
};
