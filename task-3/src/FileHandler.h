#pragma once
#include <fstream>
#include <iostream>
#include "WAVHeader.h"

const int second = 44100 * 2;

class FileHandler {
    std::string inputFilename;
    std::ifstream in;
    int inHeaderEnd;
    int inSubchunk2Size;

    std::string outputFilename;
    std::fstream out;
    int outHeaderEnd {};
    int outSubchunk2Size {};

    int sampleRate;
    bool areFilesSame;
public:
    FileHandler(std::string& inputFilename, std::string& outputFilename);
    ~FileHandler();
    char* getSecondFromIn();
    char* getSecondFromOut();
    void writeString(char* buffer, int offset);
    void moveWriterPointer(int offset);
    void moveReaderPointer(int offset);
    void initialize();
    int getOutStartOffset() const;
    int getInStartOffset() const;
    int getSampleRate() const;
    int getOutSize() const;
    int getInSize() const;
    bool isAreFilesSame() const;
};

class FileReader {
public:
    void read(std::istream& in, char* buffer, int size);
};

class FileWriter {
public:
    void write(std::ostream& out, char* buffer, int size);
};

