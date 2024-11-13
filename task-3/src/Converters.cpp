#include "Converters.h"

Mixer::Mixer(std::string& inputFilename, std::string& outputFilename) : Converter(inputFilename, outputFilename) {}

void Mixer::convert(int start, int finish) {
    if (areFilesSame)
        return;
    if (!canBeMixed)
        throw ExceptionMSG("cannot_be_mixed");
    Converter::convert(start, finish);
    int startInBytes = start * sampleRate * 2;
    int fileSizeInBytes = outHeaderEnd;
    char buffer1[2];
    char buffer2[2];
    in.seekg(inHeaderEnd, std::ios::beg);
    out.seekg(outHeaderEnd, std::ios::beg);
    while (fileSizeInBytes != outSubchunk2Size) {
        if (fileSizeInBytes > inSubchunk2Size) {
            return;
        }
        if (fileSizeInBytes >= startInBytes) {
            in.read(buffer1, 2);
            out.read(buffer2, 2);
            char bufferResult[2];
            // From math: sums below cannot get more than 256.
            bufferResult[0] = static_cast<char>(((buffer1[0] + buffer2[0]) / 2));
            bufferResult[1] = static_cast<char>(((buffer1[1] + buffer2[1]) / 2));
            out.seekp(-2, std::ios::cur);
            out.write(bufferResult, 2);
        }
        else {
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
    int fileSizeInBytes = inHeaderEnd;
    FileWriter fileWriter;
    char buffer[2];
    if (areFilesSame) {
        while (fileSizeInBytes != inSubchunk2Size) {
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

Converter* MuterFactory::createConverter(std::string& inputFilename, std::string& outputFilename) {
    return new Muter(inputFilename, outputFilename);
}

Converter* MixerFactory::createConverter(std::string& inputFilename, std::string& outputFilename) {
    return new Mixer(inputFilename, outputFilename);
}

void Converter::convert(int start, int finish) {
    in.seekg(inHeaderEnd, std::ios::beg);
}

Converter::Converter(std::string& inputFilename, std::string& outputFilename) : inputFilename(inputFilename), outputFilename(outputFilename) {
    WAVHeaderParser inWavHeaderParser;
    try {
        inWavHeaderParser.parseWAV(inputFilename);
    }
    catch (const char* error_message) {
        std::cerr << error_message << '\n';
    }
    inHeaderEnd = inWavHeaderParser.getHeaderSize();

    areFilesSame = inputFilename == outputFilename;
    if (!areFilesSame) {
        in.open(inputFilename, std::ios::binary);
    }
    out.open(outputFilename, std::ios::binary | std::ios::in | std::ios::out);

    bool wasOutOpen = out.is_open() && out.peek() != -1;
    WAVHeaderParser outWavHeaderParser;
    if (wasOutOpen) {
        try {
            outWavHeaderParser.parseWAV(outputFilename);
        }
        catch (const char *error_message) {
            std::cerr << error_message << '\n';
        }
        outHeaderEnd = outWavHeaderParser.getHeaderSize();
    }
    else {
        out.open(outputFilename, std::ios::binary | std::ios::out);
        canBeMixed = false;
    }

    if (!wasOutOpen) {
        WAVHeaderWriter wavHeaderWriter = WAVHeaderWriter(inWavHeaderParser);
        wavHeaderWriter.writeWavHeader(out);
    }
    // attention
    out.seekg(inHeaderEnd, std::ios::beg);
    inSubchunk2Size = inWavHeaderParser.getSubchunk2Size();
    if (wasOutOpen)
        outSubchunk2Size = outWavHeaderParser.getSubchunk2Size();
    sampleRate = inWavHeaderParser.getSampleRate();
}

Converter::~Converter() {
    if (!areFilesSame)
        in.close();
    out.close();
}
