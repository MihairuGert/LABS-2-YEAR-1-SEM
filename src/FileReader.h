#pragma once

#include <fstream>
#include <string>
#include <iostream>

class FileReader {
private:
	std::string filename;
	std::ifstream* in;
public:
	void open();
	void close();
	std::string getLine();
	void debugConsoleLogFilenameAdress();
	explicit FileReader(const std::string& filename);
};
