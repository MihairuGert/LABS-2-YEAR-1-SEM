#pragma once
#include <string>
#include <fstream>
#include "WAVHeader.h"
#include "FileHandler.h"

class ConverterHelper {
protected:
    FileHandler* fileHandler;
public:
    ConverterHelper(std::string& inputFilename, std::string& outputFilename);
    ~ConverterHelper();
    virtual void convert(int start, int finish, double coef);
};

class MuterHelper : public ConverterHelper {
public:
    MuterHelper(std::string& inputFilename, std::string& outputFilename);
    void convert(int start, int finish, double coef) override;
};

class MixerHelper : public ConverterHelper {
public:
    MixerHelper(std::string& inputFilename, std::string& outputFilename);
    void convert(int start, int finish, double coef) override;
};

class BoosterHelper : public ConverterHelper {
public:
    BoosterHelper(std::string& inputFilename, std::string& outputFilename);
    BoosterHelper(std::string& inputFilename, std::string& outputFilename, double coef);
    void convert(int start, int finish, double coef) override;
};

class ConverterHelperFactory {
public:
    virtual ConverterHelper* createConverter(std::string& inputFilename, std::string& outputFilename) = 0;
};

class MuterHelperFactory : public ConverterHelperFactory {
public:
    ConverterHelper* createConverter(std::string& inputFilename, std::string& outputFilename) override;
};

class MixerHelperFactory : public ConverterHelperFactory {
public:
    ConverterHelper* createConverter(std::string& inputFilename, std::string& outputFilename) override;
};

class BoosterHelperFactory : public ConverterHelperFactory {
public:
    ConverterHelper* createConverter(std::string& inputFilename, std::string& outputFilename) override;
};
