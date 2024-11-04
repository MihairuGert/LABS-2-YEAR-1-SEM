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
    int outNumber;
public:
    Cmd(std::string name, std::vector<int> interval, int outNum) : cmdName(name), interval(interval), outNumber(outNum) {};
    std::string getCmdName() const noexcept;
    std::vector<int> getInterval() const noexcept;
};

class ConfigParser {
    std::ifstream* in;
public:
    ConfigParser(std::ifstream* in) : in(in) {};
    Cmd* getCommand();
};
