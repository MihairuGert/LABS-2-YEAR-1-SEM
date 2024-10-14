#pragma once

#include <list>
#include "FileReader.h"

class TextParser
{
public:
    std::list<std::string> parseString(const std::string& line);
};

