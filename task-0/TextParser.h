#pragma once

#include <list>
#include "FileReader.h"

class TextParser
{
private:
	std::list<std::string>* wordsList;
public:
	void parseString(const std::string& line);
	void parseTextInFile(FileReader fileReader);
	std::list<std::string> getWordsList();
	TextParser();
};

