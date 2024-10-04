#include "InputInterpreter.h"

bool InputInterpreter::checkFormat(const std::string& string) {
    if (string != "#Life 1.06") {
        return false;
    }
    return true;
}

std::string InputInterpreter::getName(std::string string) {\
    char prev2 = 0;
    char prev1 = 0;
    std::string res;
    bool hasNameStarted = false;
    for (const auto& ch : string) {
        if (ch == 'N' && prev1 == '#') {
            hasNameStarted = true;
            prev2 = prev1;
            prev1 = ch;
            continue;
        }
        if (hasNameStarted && prev2 != '#' && prev1 != 'N' && ch != ' ') {
            res.push_back(ch);
        }
        prev2 = prev1;
        prev1 = ch;
    }
    return res;
}

std::vector<std::vector<int>> InputInterpreter::getConditions(std::string string) {
    std::vector<std::vector<int>> rules;
    rules.resize(2);
    char prev2 = 0;
    char prev1 = 0;
    bool hasRulesStarted = false;
    bool hasBirthStarted = false;
    bool hasSurviveStarted = false;
    for (const auto& ch : string) {
        if (ch == 'R' && prev1 == '#') {
            hasRulesStarted = true;
            prev2 = prev1;
            prev1 = ch;
            continue;
        }
        if (hasRulesStarted && prev2 != '#' && prev1 != 'R' && ch != ' ' && ch != '/') {
            if (hasBirthStarted) {
                rules[0].push_back(ch - '0');
            }
            else if (hasSurviveStarted) {
                rules[1].push_back(ch - '0');
            }
            else if (ch == 'B') {
                hasBirthStarted = true;
            }
            else if (ch == 'S') {
                hasSurviveStarted = true;
            }
        } else if (ch == '/') {
            hasBirthStarted = false;
        }
        prev2 = prev1;
        prev1 = ch;
    }
    return rules;
}

std::vector<int> InputInterpreter::getCell(std::string string) {
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

std::vector<int> InputInterpreter::getSize(std::string string) {
    std::vector<int> res;
    res.resize(2);
    res[0] = 0;
    res[1] = 0;
    int index = 0;
    int digit = 1;
    for (const char& ch : string) {
        if (ch == 'R') {
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
