#pragma once
#include <string>
#include <fstream>
#include "WAVHeader.h"
#include "FileHandler.h"

class Converter {
protected:
    FileHandler* fileHandler;
public:
    Converter(std::string& inputFilename, std::string& outputFilename);
    ~Converter();
    virtual void convert(int start, int finish);
    //virtual std::string getFileName() const noexcept;
};

class Muter : public Converter {
public:
    Muter(std::string& inputFilename, std::string& outputFilename);
    void convert(int start, int finish) override;
    //std::string getFileName() const noexcept override;
};

class Mixer : public Converter {
public:
    Mixer(std::string& inputFilename, std::string& outputFilename);
    void convert(int start, int finish) override;
    //std::string getFileName() const noexcept override;
};

class ConverterFactory {
public:
    virtual Converter* createConverter(std::string& inputFilename, std::string& outputFilename) = 0;
};

class MuterFactory : public ConverterFactory {
public:
    Converter* createConverter(std::string& inputFilename, std::string& outputFilename) override;
};

class MixerFactory : public ConverterFactory {
public:
    Converter* createConverter(std::string& inputFilename, std::string& outputFilename) override;
};
