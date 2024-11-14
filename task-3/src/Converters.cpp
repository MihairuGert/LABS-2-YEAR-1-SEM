#include "Converters.h"

Mixer::Mixer(std::string& inputFilename, std::string& outputFilename) : Converter(inputFilename, outputFilename) {}

void Mixer::convert(int start, int finish) {
    if (fileHandler->isAreFilesSame())
        return;
    if (!fileHandler->isCanBeMixed())
        throw ExceptionMSG("cannot_be_mixed");
    Converter::convert(start, finish);
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

void Muter::convert(int start, int finish) {
    int startInBytes = start * fileHandler->getSampleRate() * 2;
    int finishInBytes = finish * fileHandler->getSampleRate() * 2;
    int fileSizeInBytes = fileHandler->getInStartOffset();
    fileHandler->initialize();
    if (fileHandler->isAreFilesSame()) {
        while (fileSizeInBytes != fileHandler->getInSize()) {
            if (fileSizeInBytes >= startInBytes && fileSizeInBytes <= finishInBytes) {
                fileHandler->writeInt(0, second, 0);
            }
            else {
                fileHandler->moveWriterPointer(second);
            }
            fileSizeInBytes += second;
        }
        return;
    }
    int a = fileHandler->getInSize();
    while (fileSizeInBytes <= fileHandler->getInSize()) {
        if (fileSizeInBytes >= startInBytes && fileSizeInBytes <= finishInBytes) {
            fileHandler->writeInt(0, second, 0);
            fileHandler->moveReaderPointer(second);
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

Converter* MuterFactory::createConverter(std::string& inputFilename, std::string& outputFilename) {
    return new Muter(inputFilename, outputFilename);
}

Converter* MixerFactory::createConverter(std::string& inputFilename, std::string& outputFilename) {
    return new Mixer(inputFilename, outputFilename);
}

void Converter::convert(int start, int finish) {
}

Converter::Converter(std::string& inputFilename, std::string& outputFilename) {
    fileHandler = new FileHandler(inputFilename, outputFilename);
}

Converter::~Converter() {
    delete(fileHandler);
}
