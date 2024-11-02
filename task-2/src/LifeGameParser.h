#pragma once
#include <string>
#include <vector>
#include <cstring>
#include "GameEngine.h"
#include "FileReader.h"

class InputInterpreter {
public:
    bool checkFormat(const std::string& string);
    std::string getName(const std::string& string);
    std::vector<std::vector<int>> getConditions(const std::string& string, bool* parsingErrors);
    std::vector<int> getSize(const std::string& string, bool* parsingErrors);
    std::vector<int> getCell(const std::string& string);
};

class Parser {
public:
    void processName(std::string& fileLine, bool *parsingErrors, bool& isSuccessGetLine, std::string& universeName);
    void processConditions(std::string& fileLine, bool *parsingErrors
                           , bool& isSuccessGetLine,
                                  std::vector<int>& birthCondition, std::vector<int>& survivalCondition);
    void processSize(std::string& fileLine, bool *parsingErrors, bool& isSuccessGetLine,
                            int& column, int& row, Grid& grid);
    void processCells(std::string& fileLine, bool *parsingErrors, bool& isSuccessGetLine,
                             int& column, int& row, Grid& grid);
};

class LifeGameParser {
private:
    std::vector<int> birthCondition;
    std::vector<int> survivalCondition;
    int row;
    int column;
    Grid grid;
    std::string universeName{};
    std::string filename{};
    int iterationsOffline{};
    void processConsole(int argc, char** argv, int& iterations, std::string& filename);
public:
    std::vector<int> getBirthCondition() const;
    std::vector<int> getSurvivalCondition() const;
    std::string getFilename() const;
    int getRow() const;
    int getColumn() const;
    int getIterationsOffline() const;
    Grid getGrid() const;
    std::string getUniverseName() const;
    ParseFileStatus parseLifeFile(int argc, char** argv, bool* parsingErrors);
};
