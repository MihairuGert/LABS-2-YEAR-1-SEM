#pragma once
#include <fstream>
#include <iostream>
#include <ConfigParser.h>

class SoundProcessor {
    std::ifstream in;
public:
    void runProcess();
};

