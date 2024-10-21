#pragma once
#include <string>
#include <vector>
#include <cstring>
#include "GameEngine.h"
#include "FileReader.h"

class InputInterpreter {
public:
    static bool checkFormat(const std::string& string);
    static std::string getName(const std::string& string);
    static std::vector<std::vector<int>> getConditions(const std::string& string, bool* parseLifeFileStatus);
    static std::vector<int> getSize(const std::string& string, bool* parseLifeFileStatus);
    static std::vector<int> getCell(const std::string& string);
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

class LifeGameParser {
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
    static void processConsole(int argc, char** argv, int& iterations, std::string& filename);
public:
    std::vector<int> getBirthCondition() const;
    std::vector<int> getSurvivalCondition() const;
    std::string getFilename() const;
    int getRow() const;
    int getColumn() const;
    int getIterationsOffline() const;
    Grid getGrid1() const;
    std::string getUniverseName() const;
    ParseFileStatus parseLifeFile(int argc, char** argv, bool* parseLifeFileStatus);
};
