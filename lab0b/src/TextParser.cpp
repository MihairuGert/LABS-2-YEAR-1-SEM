#include "TextParser.h"

std::list<std::string> TextParser::parseString(const std::string& line) {
    std::list<std::string> res;
    std::string word;
    for (char i : line) {
        if (!(i < '0' || (i > '9' && i < 'A')
            || (i > 'Z' && i < 'a') || i > 'z')) {
            word.push_back(i);
        }
        else {
            if (word.empty()) {
                continue;
            }
            res.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()) {
        res.push_back(word);
    }
    return res;
}
