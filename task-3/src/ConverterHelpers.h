#pragma once
#include <string>
#include <fstream>
#include "WAVHeader.h"
#include "FileHandler.h"
#include "Converters.h"

class ConverterHelper {
protected:
    FileHandler* fileHandler;
public:
    ConverterHelper(std::string& inputFilename, std::string& outputFilename);
    ~ConverterHelper();
    virtual void convert(int start, int finish, double coef);
    virtual char* callConverter(const ConverterFactory& factory, char* outStream, char* inStream = nullptr, double coef = 1);
};

class MuterHelper : public ConverterHelper {
public:
    MuterHelper(std::string& inputFilename, std::string& outputFilename);
    void convert(int start, int finish, double coef) override;
    char* callConverter(const ConverterFactory& factory, char* outStream, char* inStream = nullptr, double coef = 1) override;
};

class MixerHelper : public ConverterHelper {
public:
    MixerHelper(std::string& inputFilename, std::string& outputFilename);
    void convert(int start, int finish, double coef) override;
    char* callConverter(const ConverterFactory& factory, char* outStream, char* inStream = nullptr, double coef = 1) override;
};

class BoosterHelper : public ConverterHelper {
public:
    BoosterHelper(std::string& inputFilename, std::string& outputFilename);
    BoosterHelper(std::string& inputFilename, std::string& outputFilename, double coef);
    void convert(int start, int finish, double coef) override;
    char* callConverter(const ConverterFactory& factory, char* outStream, char* inStream = nullptr, double coef = 1) override;
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
