#pragma once
#include <string>
#include <fstream>

class Converter {
    int headerEnd;
public:
    virtual void convert(const std::ifstream& in, int start, int finish);
    void setHeaderEnd(int headerEnd);
};

class Muter : public Converter {
public:
    void convert(const std::ifstream& in, int start, int finish) override;
};

class Mixer : public Converter {
public:
    void convert(const std::ifstream& in, int start, int finish) override;
};

class ConverterFactory {
public:
    virtual Converter* createConverter() = 0;
};

class MuterFactory : public ConverterFactory {
public:
    Converter* createConverter() override;
};

class MixerFactory : public ConverterFactory {
public:
    Converter* createConverter() override;
};
