#include "Converters.h"

Mixer::Mixer(std::string& inputFilename, std::string& outputFilename) : Converter(inputFilename, outputFilename) {}

//std::string Mixer::getFileName() const noexcept {
//    return Converter::getFileName();
//}

void Mixer::convert(int start, int finish) {
    if (areFilesSame)
        return;
    if (!canBeMixed)
        throw ExceptionMSG("cannot_be_mixed");
    Converter::convert(start, finish);
    int startInBytes = start * sampleRate * 2;
    int fileSizeInBytes = headerEnd;
    char buffer1[2];
    char buffer2[2];
    FileWriter fileWriter;
    //std::cout << out.tellp() << ' ' << out.tellg() << ' ' << in.tellg() << '\n';
    while (fileSizeInBytes != subchunk2Size) {
        if (fileSizeInBytes >= startInBytes) {
            in.read(buffer1, 2);
            out.read(buffer2, 2);
            char bufferResult[2];
            // From math: sums below cannot get more than 256.
            bufferResult[0] = static_cast<char>(((buffer1[0] + buffer2[0]) / 2));
            bufferResult[1] = static_cast<char>(((buffer1[1] + buffer2[1]) / 2));
            out.write(bufferResult, 2);

        }
        else {
            in.seekg(2, std::ios::cur);
            out.seekp(2, std::ios::cur);
        }
        fileSizeInBytes += 2;
    }
}

void Muter::convert(int start, int finish) {
    if (!areFilesSame)
        Converter::convert(start, finish);
    int startInBytes = start * sampleRate * 2;
    int finishInBytes = finish * sampleRate * 2;
    int fileSizeInBytes = headerEnd;
    FileWriter fileWriter;
    char buffer[2];
    if (areFilesSame) {
        while (fileSizeInBytes != subchunk2Size) {
            if (fileSizeInBytes >= startInBytes && fileSizeInBytes <= finishInBytes) {
                fileWriter.writeBinaryInFile(out,0,2);
            }
            else {
                out.seekp(2, std::ios::cur);
            }
            fileSizeInBytes += 2;
        }
        return;
    }
    while (!in.eof()) {
        if (fileSizeInBytes >= startInBytes && fileSizeInBytes <= finishInBytes) {
            fileWriter.writeBinaryInFile(out,0,2);
            in.seekg(2, std::ios::cur);
        }
        else {
            in.read(buffer, 2);
            out.write(buffer, 2);
        }
        fileSizeInBytes += 2;
    }
}

Muter::Muter(std::string& inputFilename, std::string& outputFilename) : Converter(inputFilename, outputFilename) {}

//std::string Muter::getFileName() const noexcept {
//    return Converter::getFileName();
//}

Converter* MuterFactory::createConverter(std::string& inputFilename, std::string& outputFilename) {
    return new Muter(inputFilename, outputFilename);
}

Converter* MixerFactory::createConverter(std::string& inputFilename, std::string& outputFilename) {
    return new Mixer(inputFilename, outputFilename);
}

void Converter::convert(int start, int finish) {
    in.seekg(headerEnd, std::ios::beg);
}

Converter::Converter(std::string& inputFilename, std::string& outputFilename) : inputFilename(inputFilename), outputFilename(outputFilename) {
    WAVHeaderParser wavHeaderParser;
    try {
        wavHeaderParser.parseWAV(inputFilename);
    }
    catch (const char* error_message) {
        std::cerr << error_message << '\n';
    }
    headerEnd = wavHeaderParser.getHeaderSize();
    WAVHeaderWriter wavHeaderWriter = WAVHeaderWriter(wavHeaderParser);
    areFilesSame = inputFilename == outputFilename;
    if (!areFilesSame) {
        in.open(inputFilename, std::ios::binary);
    }
    out.open(outputFilename, std::ios::binary | std::ios::in | std::ios::out);
    if (!out.is_open()) {
        out.open(outputFilename, std::ios::binary | std::ios::out);
        canBeMixed = false;
    }
    wavHeaderWriter.writeWavHeader(out);
    // attention
    out.seekg(headerEnd, std::ios::beg);
    subchunk2Size = wavHeaderWriter.getSubchunk2SizeRate();
    sampleRate = wavHeaderWriter.getSampleRate();
}

//std::string Converter::getFileName() const noexcept {
//    return filename;
//}

int Converter::getHeaderEnd() const noexcept {
    return headerEnd;
}

Converter::~Converter() {
    if (!areFilesSame)
        in.close();
    out.close();
}
