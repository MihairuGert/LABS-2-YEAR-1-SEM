#pragma once
#include <vector>
#include <string>
#include <cstring>
#include "ExceptionMSG.h"

enum class RunMode {HELP = 0, RUN};

class ConsoleParser {
    std::string configFilename;
    std::vector<std::string> inputFilenames;
    bool isWav(char* str1) const noexcept;
public:
    RunMode parseConsole(int argc, char* argv[]);
    std::string getConfigName() const noexcept;
    std::vector<std::string> getInputFilenames() const noexcept;
};
