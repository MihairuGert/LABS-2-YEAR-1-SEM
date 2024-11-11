#pragma once
#include <fstream>
#include <iostream>
#include "ConfigParser.h"
#include "WAVHeader.h"
#include "Converters.h"

class SoundProcessor {
    std::ifstream config;
    std::ofstream out;
    int headerEnd;
public:
    void runProcess();
};

