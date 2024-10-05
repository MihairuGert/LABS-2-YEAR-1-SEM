#include <iostream>
#include "InputInterpreter.h"

bool InputInterpreter::checkFormat(const std::string& string) {
    if (string != "#Life 1.06") {
        return false;
    }
    return true;
}

std::string InputInterpreter::getName(const std::string& string) {
    int start = string.find("#N ") + 3;
    if (start == 2) {
        return "";
    }
    return string.substr(start);
}

std::vector<std::vector<int>> InputInterpreter::getConditions(const std::string& string, bool* parseLifeFileStatus) {
    std::vector<std::vector<int>> rules;
    rules.resize(2);
    int start = string.find('B') + 1;
    int end = string.find('/');
    std::string data = string.substr(start, end - start);
    if (start == 0 || end == -1) {
        parseLifeFileStatus[2] = true;
        rules[0] = {3};
        rules[1] = {2, 3};
        return rules;
    } else {
        for (const auto &ch: data) {
            if (ch < '0' || ch > '9') {
                continue;
            }
            rules[0].push_back(ch - '0');
        }
    }
    if (rules[0].empty()) {
        rules[0] = {3};
    }
    start = string.find('S') + 1;
    if (start == 0) {
        parseLifeFileStatus[2] = true;
        rules[1] = {2, 3};
        return rules;
    } else {
        data = string.substr(start);
        for (const auto &ch: data) {
            if (ch < '0' || ch > '9') {
                continue;
            }
            rules[1].push_back(ch - '0');
        }
    }
    if (rules[1].empty()) {
        rules[1] = {2, 3};
    }
    return rules;
}

std::vector<int> InputInterpreter::getCell(const std::string& string) {
    std::vector<int> res;
    res.resize(2);
    res[0] = 0;
    res[1] = 0;
    int index = 0;
    int digit = 1;
    for (const char& ch : string) {
        if (ch == ' ') {
            ++index;
            digit = 1;
            continue;
        }
        if (ch > '9' || ch < '0') {
            continue;
        }
        res[index] = ch - '0' + res[index] * digit;
        digit *= 10;
    }
    return res;
}

std::vector<int> InputInterpreter::getSize(const std::string& string, bool* parseLifeFileStatus) {
    std::vector<int> res;
    res.resize(2);
    int start = string.find('C') + 1;
    int end = string.find('/');
    if (start == 0 || end == -1) {
        res[0] = 50;
        res[1] = 50;
        parseLifeFileStatus[3] = true;
        return res;
    } else {
        int column = std::stoi(string.substr(start, end - start));
        res[0] = column;
    }
    start = string.find('R') + 1;
    if (start == 0) {
        res[1] = 50;
        parseLifeFileStatus[3] = true;
        return res;
    } else {
        int row = std::stoi(string.substr(start));
        res[1] = row;
    }
    return res;
}
