#pragma once

#include <string>

class Converter {
protected:
    const int second = 44100 * 2;
public:
    virtual char* convert(char* outStream, char* inStream = nullptr, double coef = 1);
    virtual std::string getName() const = 0;
    virtual std::string getBriefDescription() const = 0;
    virtual std::string getParameters() const = 0;
};

class Muter : public Converter {
public:
    char* convert(char* outStream, char* inStream = nullptr, double coef = 1) override;
    std::string getName() const override;
    std::string getBriefDescription() const override;
    std::string getParameters() const override;
};

class Mixer : public Converter {
public:
    char* convert(char* outStream, char* inStream = nullptr, double coef = 1) override;
    std::string getName() const override;
    std::string getBriefDescription() const override;
    std::string getParameters() const override;
};

class Booster : public Converter {
public:
    char* convert(char* outStream, char* inStream = nullptr, double coef = 1) override;
    std::string getName() const override;
    std::string getBriefDescription() const override;
    std::string getParameters() const override;
};

class ConverterFactory {
public:
    virtual Converter* createConverter() const = 0;
};

class MuterFactory : public ConverterFactory {
public:
    Converter* createConverter() const override;
};

class MixerFactory : public ConverterFactory {
public:
    Converter* createConverter() const override;
};

class BoosterFactory : public ConverterFactory {
public:
    Converter* createConverter() const override;
};
