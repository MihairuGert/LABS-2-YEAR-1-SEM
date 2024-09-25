#include "TextParser.h"

void TextParser::parseString(const std::string& line) {
    std::string res;
    for (char i : line) {
        if (!(i < '0' || (i > '9' && i < 'A')
            || (i > 'Z' && i < 'a') || i > 'z')) {
            res.push_back(i);
        }
        else {
            if (res.empty()) {
                continue;
            }
            (*wordsList).push_back(res);
            res.clear();
        }
    }
    if (!res.empty()) {
        (*wordsList).push_back(res);
    }
}

std::list<std::string> TextParser::getWordsList() {
    return *wordsList;
}

TextParser::TextParser() {
    auto* wordsList = new std::list<std::string>;
    this->wordsList = wordsList;
}