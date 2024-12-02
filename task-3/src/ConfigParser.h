#pragma once
#include "ExceptionMSG.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

class Cmd {
    std::string cmdName;
    std::vector<int> interval;
    int inputIndex{};
    double doubleArg{};
public:
    Cmd(std::string name, std::vector<int> interval) : cmdName(name), interval(interval) {};
    Cmd(std::string name, std::vector<int> interval, int inputIndex) : cmdName(name), interval(interval), inputIndex(inputIndex) {};
    Cmd(std::string name, std::vector<int> interval, int inputIndex, double doubleArg) : cmdName(name), interval(interval), inputIndex(inputIndex), doubleArg(doubleArg) {};
    std::string getCmdName() const;
    std::vector<int> getInterval() const;
    int getInputIndex() const;
    double getCoef() const;
};

class ConfigParser {
    std::ifstream* in;
public:
    ConfigParser(std::ifstream* in) : in(in) {};
    Cmd* getCommand();
};
