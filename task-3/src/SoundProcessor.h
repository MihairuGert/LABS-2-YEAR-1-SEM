#pragma once
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include "ConfigParser.h"
#include "WAVHeader.h"
#include "Converters.h"

class SoundProcessor {
    std::ifstream config;
    std::ofstream out;
    std::string configFilename;
    std::vector<std::string> inFilenames;
    void convert(ConverterFactory converterFactory, int start, int finish, std::string inFilename, std::string outFilename);
public:
    SoundProcessor(std::string configFilename, std::vector<std::string> inFilenames) : configFilename(std::move(configFilename)), inFilenames(std::move(inFilenames)) {};
    void runProcess();
};

