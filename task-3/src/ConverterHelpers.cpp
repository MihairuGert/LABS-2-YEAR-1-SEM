#include "ConverterHelpers.h"

MixerHelper::MixerHelper(std::string& inputFilename, std::string& outputFilename) : ConverterHelper(inputFilename, outputFilename) {}

void MixerHelper::convert(int start, int finish, double coef) {
    ConverterHelper::convert(start, finish, coef);
    int startInBytes = start * fileHandler->getSampleRate() * 2;
    fileHandler->initialize();
    int fileSizeInBytes = fileHandler->getOutStartOffset();
    MixerFactory mixerFactory;
    while (fileSizeInBytes <= fileHandler->getOutSize()) {
        if (fileSizeInBytes > fileHandler->getInSize()) {
            return;
        }
        if (fileSizeInBytes >= startInBytes) {
            char* bufferIn = fileHandler->getSecondFromIn();
            char* bufferOut = fileHandler->getSecondFromOut();
            bufferOut = callConverter(mixerFactory, bufferOut, bufferIn);
            fileHandler->writeString(bufferOut, -second);
            delete(bufferIn);
            delete(bufferOut);
        }
        else {
            fileHandler->moveWriterPointer(second);
        }
        fileSizeInBytes += second;
    }
}

void MuterHelper::convert(int start, int finish, double coef) {
    int startInBytes = start * fileHandler->getSampleRate() * 2;
    int finishInBytes = finish * fileHandler->getSampleRate() * 2;
    int fileSizeInBytes = fileHandler->getInStartOffset();
    fileHandler->initialize();
    MuterFactory muterFactory;
    if (fileHandler->isAreFilesSame()) {
        while (fileSizeInBytes <= fileHandler->getInSize()) {
            if (fileSizeInBytes >= startInBytes && fileSizeInBytes <= finishInBytes) {
                char* buffer = new char[second];
                callConverter(muterFactory, buffer);
                fileHandler->writeString(buffer, 0);
                delete[](buffer);
            }
            else {
                fileHandler->moveWriterPointer(second);
            }
            fileSizeInBytes += second;
        }
        return;
    }
    while (fileSizeInBytes <= fileHandler->getInSize()) {
        if (fileSizeInBytes >= startInBytes && fileSizeInBytes <= finishInBytes) {
            char* buffer = fileHandler->getSecondFromIn();
            callConverter(muterFactory, buffer);
            fileHandler->writeString(buffer, 0);
            delete(buffer);
        }
        else {
            char* buffer = fileHandler->getSecondFromIn();
            fileHandler->writeString(buffer, 0);
            delete(buffer);
        }
        fileSizeInBytes += second;
    }
}

MuterHelper::MuterHelper(std::string& inputFilename, std::string& outputFilename) : ConverterHelper(inputFilename, outputFilename) {}

BoosterHelper::BoosterHelper(std::string &inputFilename, std::string &outputFilename, double coef) : ConverterHelper(inputFilename, outputFilename) {}

ConverterHelper* MuterHelperFactory::createConverter(std::string& inputFilename, std::string& outputFilename) {
    return new MuterHelper(inputFilename, outputFilename);
}

ConverterHelper* MixerHelperFactory::createConverter(std::string& inputFilename, std::string& outputFilename) {
    return new MixerHelper(inputFilename, outputFilename);
}

ConverterHelper *BoosterHelperFactory::createConverter(std::string &inputFilename, std::string &outputFilename) {
    return new BoosterHelper(inputFilename, outputFilename);
}

void ConverterHelper::convert(int start, int finish, double coef) {}

ConverterHelper::ConverterHelper(std::string& inputFilename, std::string& outputFilename) {
    fileHandler = new FileHandler(inputFilename, outputFilename);
}

ConverterHelper::~ConverterHelper() {
    delete(fileHandler);
}

BoosterHelper::BoosterHelper(std::string &inputFilename, std::string &outputFilename) : ConverterHelper(inputFilename, outputFilename) {}

void BoosterHelper::convert(int start, int finish, double coef) {
    int startInBytes = start * fileHandler->getSampleRate() * 2;
    int finishInBytes = finish * fileHandler->getSampleRate() * 2;
    int fileSizeInBytes = fileHandler->getInStartOffset();
    fileHandler->initialize();
    BoosterFactory boosterFactory;
    if (fileHandler->isAreFilesSame()) {
        while (fileSizeInBytes <= fileHandler->getInSize()) {
            if (fileSizeInBytes >= startInBytes && fileSizeInBytes <= finishInBytes) {
                char* buffer = fileHandler->getSecondFromOut();
                buffer = callConverter(boosterFactory, buffer, nullptr, coef);
                fileHandler->writeString(buffer, -second);
                delete(buffer);
            }
            else {
                fileHandler->moveWriterPointer(second);
            }
            fileSizeInBytes += second;
        }
        return;
    }
    while (fileSizeInBytes < fileHandler->getInSize()) {
        if (fileSizeInBytes >= startInBytes && fileSizeInBytes <= finishInBytes) {
            char* buffer = fileHandler->getSecondFromIn();
            buffer = callConverter(boosterFactory, buffer, nullptr, coef);
            fileHandler->writeString(buffer, 0);
            delete(buffer);
        }
        else {
            char* buffer = fileHandler->getSecondFromIn();
            fileHandler->writeString(buffer, 0);
            delete(buffer);
        }
        fileSizeInBytes += second;
    }
}

char* ConverterHelper::callConverter(const ConverterFactory& factory, char* stream1, char* inStream, double coef) {
    Converter* converter = factory.createConverter();
    stream1 = converter->convert(stream1, inStream, coef);
    return stream1;
}

char *MuterHelper::callConverter(const ConverterFactory &factory, char *outStream, char *inStream, double coef) {
    return ConverterHelper::callConverter(factory, outStream, inStream, coef);
}

char *MixerHelper::callConverter(const ConverterFactory &factory, char *outStream, char *inStream, double coef) {
    return ConverterHelper::callConverter(factory, outStream, inStream, coef);
}

char *BoosterHelper::callConverter(const ConverterFactory &factory, char *outStream, char *inStream, double coef) {
    return ConverterHelper::callConverter(factory, outStream, inStream, coef);
}

