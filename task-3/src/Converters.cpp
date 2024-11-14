#include "Converters.h"

Mixer::Mixer(std::string& inputFilename, std::string& outputFilename) : Converter(inputFilename, outputFilename) {}

void Mixer::convert(int start, int finish, double coef) {
    if (fileHandler->isAreFilesSame())
        return;
    if (!fileHandler->isCanBeMixed())
        throw ExceptionMSG("cannot_be_mixed");
    Converter::convert(start, finish, coef);
    int startInBytes = start * fileHandler->getSampleRate() * 2;
    fileHandler->initialize();
    int fileSizeInBytes = fileHandler->getOutStartOffset();
    while (fileSizeInBytes != fileHandler->getOutSize()) {
        if (fileSizeInBytes > fileHandler->getInSize()) {
            return;
        }
        if (fileSizeInBytes >= startInBytes) {
            char* bufferIn = fileHandler->getSecondFromIn();
            char* bufferOut = fileHandler->getSecondFromOut();
            for (int i = 0; i < second; ++i) {
                bufferOut[i] = static_cast<char>(((bufferIn[i] + bufferOut[i]) / 2));
            }
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

void Muter::convert(int start, int finish, double coef) {
    int startInBytes = start * fileHandler->getSampleRate() * 2;
    int finishInBytes = finish * fileHandler->getSampleRate() * 2;
    int fileSizeInBytes = fileHandler->getInStartOffset();
    fileHandler->initialize();
    if (fileHandler->isAreFilesSame()) {
        while (fileSizeInBytes <= fileHandler->getInSize()) {
            if (fileSizeInBytes >= startInBytes && fileSizeInBytes <= finishInBytes) {
                char* buffer = new char[second];
                for (int i = 0; i < second; ++i) {
                    buffer[i] = 0;
                }
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
            for (int i = 0; i < second; ++i) {
                buffer[i] = 0;
            }
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

Muter::Muter(std::string& inputFilename, std::string& outputFilename) : Converter(inputFilename, outputFilename) {}

Booster::Booster(std::string &inputFilename, std::string &outputFilename, double coef) : Converter(inputFilename, outputFilename) {}

Converter* MuterFactory::createConverter(std::string& inputFilename, std::string& outputFilename) {
    return new Muter(inputFilename, outputFilename);
}

Converter* MixerFactory::createConverter(std::string& inputFilename, std::string& outputFilename) {
    return new Mixer(inputFilename, outputFilename);
}

Converter *BoosterFactory::createConverter(std::string &inputFilename, std::string &outputFilename) {
    return new Booster(inputFilename, outputFilename);
}

void Converter::convert(int start, int finish, double coef) {}

Converter::Converter(std::string& inputFilename, std::string& outputFilename) {
    fileHandler = new FileHandler(inputFilename, outputFilename);
}

Converter::~Converter() {
    delete(fileHandler);
}

Booster::Booster(std::string &inputFilename, std::string &outputFilename) : Converter(inputFilename, outputFilename) {}

void Booster::convert(int start, int finish, double coef) {
    int startInBytes = start * fileHandler->getSampleRate() * 2;
    int finishInBytes = finish * fileHandler->getSampleRate() * 2;
    int fileSizeInBytes = fileHandler->getInStartOffset();
    fileHandler->initialize();
    if (fileHandler->isAreFilesSame()) {
        while (fileSizeInBytes <= fileHandler->getInSize()) {
            if (fileSizeInBytes >= startInBytes && fileSizeInBytes <= finishInBytes) {
                char* buffer = fileHandler->getSecondFromOut();
                for (int i = 0; i < second; ++i) {
                    buffer[i] = static_cast<char>(buffer[i] * 2);
                }
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
            for (int i = 0; i < second; ++i) {
                buffer[i] = static_cast<char>(buffer[i] * coef);
            }
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
