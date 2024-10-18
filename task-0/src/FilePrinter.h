#pragma once

#include "FileReader.h"
#include "StatisticsModule.h"

class FilePrinter
{
private:
	std::string filename;
	std::ofstream* out;
public:
	void open();
	void close();
	void printString(const std::string& string);
	explicit FilePrinter(const std::string& filename);
};

