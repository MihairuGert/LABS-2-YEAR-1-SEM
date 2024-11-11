#pragma once
#include <fstream>

class FileWriter {
public:
    void writeBinaryInFile(std::ostream &out, int value, int bytes);
};