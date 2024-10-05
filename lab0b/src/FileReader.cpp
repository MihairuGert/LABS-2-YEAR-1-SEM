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

FileReader::FileReader(const std::string& filename) {
	this->filename = filename;
	auto* in = new std::ifstream;
	this->in = in;
	FileReader::open();
}

bool FileReader::isEOF() {
    return !in->peek();
}
