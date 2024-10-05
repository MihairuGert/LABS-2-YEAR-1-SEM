#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Grid.h"

class Cmd {
private:
    std::string name;
    std::string attributesString;
public:
    explicit Cmd(const std::string& cmd);
    std::string getName();
    std::string getAttributes();
};

class Interface {
private:
    static void printGrid(const Grid& grid);
public:
    static void printInterface(const Grid& grid, const std::vector<int>& birthCondition, const std::vector<int>& survivalCondition,
                        const std::string& universeName, int iterationNum, const bool* parseLifeFIleStatus);
    static Cmd getCommand();
    static void printHelp();
};
