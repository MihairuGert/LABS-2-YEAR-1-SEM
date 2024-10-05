#pragma once
#include <string>
#include <vector>

class InputInterpreter {
public:
    static bool checkFormat(const std::string& string);
    static std::string getName(const std::string& string);
    static std::vector<std::vector<int>> getConditions(const std::string& string, bool* parseLifeFileStatus);
    static std::vector<int> getSize(const std::string& string, bool* parseLifeFileStatus);
    static std::vector<int> getCell(const std::string& string);
};

