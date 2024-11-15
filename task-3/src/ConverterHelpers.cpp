#include "ConverterHelpers.h"

MixerHelper::MixerHelper(std::string& inputFilename, std::string& outputFilename) : ConverterHelper(inputFilename, outputFilename) {}

void MixerHelper::convert(int start, int finish, double coef) {
    if (fileHandler->isAreFilesSame())
        return;
    if (!fileHandler->isCanBeMixed())
        throw ExceptionMSG("cannot_be_mixed");
    ConverterHelper::convert(start, finish, coef);
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

void MuterHelper::convert(int start, int finish, double coef) {
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
