#pragma once

#include <fstream>
#include <string>
#include <iostream>

class FilePrinter
{
private:
    std::string filename;
    std::ofstream* out;
public:
    void open();
    void close();
    void printString(const std::string& string);
    void printInt(int n);
    explicit FilePrinter(const std::string& filename);
};
