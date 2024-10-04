#pragma once

#include <fstream>
#include <string>

class FileReader {
private:
    std::string filename;
    std::ifstream* in;
public:
    void open();
    void close();
    bool isEOF();
    std::string getLine();
    explicit FileReader(const std::string& filename);
};