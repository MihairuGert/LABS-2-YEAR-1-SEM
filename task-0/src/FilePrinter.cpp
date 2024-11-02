#include "FilePrinter.h"

void FilePrinter::open() {
	out->open(filename);
}

void FilePrinter::close() {
	out->close();
	delete out;
}

void FilePrinter::printString(const std::string& string) {
    *out << string;
}

FilePrinter::FilePrinter(const std::string& filename) {
	this->filename = filename;
	auto* out = new std::ofstream;
	this->out = out;
	FilePrinter::open();
}
