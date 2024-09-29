#pragma once

#include <list>
#include "FileReader.h"

class TextParser
{
private:
	std::list<std::string>* wordsList;
public:
    void clear();
	void parseString(const std::string& line);
	std::list<std::string> getWordsList();
	TextParser();
};

