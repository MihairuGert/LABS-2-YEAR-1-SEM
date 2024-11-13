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
    int inputIndex;
public:
    Cmd(std::string name, std::vector<int> interval, int inputIndex) : cmdName(name), interval(interval), inputIndex(inputIndex) {};
    std::string getCmdName() const noexcept;
    std::vector<int> getInterval() const noexcept;
    int getInputIndex() const noexcept;
};

class ConfigParser {
    std::ifstream* in;
public:
    ConfigParser(std::ifstream* in) : in(in) {};
    Cmd* getCommand();
};
