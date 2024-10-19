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
enum class ParseFileStatus {SUCCESS = 0, NO_FORMAT}; //dangerous!

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
    ParseFileStatus parseLifeFile(char** argv, bool* parseLifeFileStatus);
    void createLifeFile(const std::string& filename);
    GameStatus processCmd(Cmd cmd, GameEngine gameEngine, bool* parseLifeFileStatus);
    void generateUniverse();
    static void createGliderGun(Grid& grid);
    static void createPulsar(Grid& grid);
    static void createRPentamino(Grid& grid);
    static void processConsole(int argc, char** argv, int& iterations, std::string& filename);
public:
    void startGame(int argc, char** argv);
};
