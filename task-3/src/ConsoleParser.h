#pragma once
#include <vector>
#include <string>
#include <cstring>
#include "ExceptionMSG.h"

class ConsoleParser {
    std::string configFilename;
    std::vector<std::string> inputFilenames;
    bool isWav(char* str1) const noexcept;
public:
    void parseConsole(int argc, char* argv[]);
    std::string getConfigName() const noexcept;
    std::vector<std::string> getInputFilenames() const noexcept;
};
