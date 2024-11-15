#pragma once
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include "ConfigParser.h"
#include "WAVHeader.h"
#include "ConverterHelpers.h"
#include "FileHandler.h"

class SoundProcessor {
    const int DEFAULT_COEFFICIENT = 1;
    std::ifstream config;
    std::string configFilename;
    std::vector<std::string> inFilenames;
    void convert(ConverterHelperFactory& converterFactory, int start, int finish, double boostCoef, std::string& inFilename, std::string& outFilename);
public:
    SoundProcessor(std::string configFilename, std::vector<std::string> inFilenames) : configFilename(std::move(configFilename)), inFilenames(std::move(inFilenames)) {};
    void runProcess();
};

