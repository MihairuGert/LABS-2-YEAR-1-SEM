#include "FileReader.h"

void FileReader::open() {
	in->open(filename);
}

void FileReader::close() {
	in->close();
	delete in;
}

std::string FileReader::getLine() {
	std::string line;
	std::getline(*in, line);
    return line;
}

void FileReader::debugConsoleLogFilenameAdress() {
	std::cout << "File name is " << filename << '\n';
	std::cout << "File address is " << in << "\nPress any key to continue" << '\n';
	std::cin.get();
}

FileReader::FileReader(const std::string& filename) {
	this->filename = filename;
	auto* in = new std::ifstream;
	this->in = in;
	FileReader::open();
}
