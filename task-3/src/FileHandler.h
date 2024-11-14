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
    bool canBeMixed = true;
    void writeBinaryInFile(int value, int bytes);
public:
    FileHandler(std::string& inputFilename, std::string& outputFilename);
    ~FileHandler();
    char* getSecondFromIn();
    char* getSecondFromOut();
    void writeString(char* buffer, int offset);
    void writeInt(int value, int bytes, int offset);
    void moveWriterPointer(int offset);
    void moveReaderPointer(int offset);
    void initialize();
    int getOutStartOffset() const;
    int getInStartOffset() const;
    int getSampleRate() const;
    int getOutSize() const;
    int getInSize() const;
    bool isAreFilesSame() const;
    bool isCanBeMixed() const;
};
