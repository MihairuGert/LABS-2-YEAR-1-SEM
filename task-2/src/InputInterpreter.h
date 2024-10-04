#pragma once
#include <string>
#include <vector>

class InputInterpreter {
public:
    bool checkFormat(const std::string& string);
    std::string getName(std::string string);
    std::vector<std::vector<int>> getConditions(std::string string);
    std::vector<int> getSize(std::string string);
    std::vector<int> getCell(std::string string);
};

