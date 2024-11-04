#pragma once
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include "ExceptionMSG.h"

const int BUFFER_SIZE = 5;

class WAVHeaderParser {
    std::ifstream file;
    // The RIFF Chunk descriptor.
    std::string chunkId = "RIFF";
    std::string chunkSize = "0000";
    std::string format = "WAFE";
    //
    std::string subchunk1Id = "fmt ";
    int subchunk1Size = 16;
    int audioFormat = 1;
    int numChannels = 1;
    int sampleRate = 44100;
    int byteRate = subchunk1Size;
    int blockAlign{};
    int bitsPerSample = 16;
    //
    std::string subchunk2Id = "data";
    int subchunk2Size = 0;
    //
    int headerSize = 0;
    int binaryStringToInt(char* string, int bytes, bool isBigEndian) const noexcept;
public:
    void parseWAV(std::string filename);
    int getHeaderSize() const noexcept;
};
