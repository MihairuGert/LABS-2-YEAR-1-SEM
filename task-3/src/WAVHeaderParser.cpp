#include "WAVHeaderParser.h"

int WAVHeaderParser::binaryStringToInt(char* string, int bytes, bool isBigEndian) const noexcept {
    int res = 0;
    for (int i = 0; i < bytes - 1; i++) {
        res |= (unsigned char) string[isBigEndian ? bytes - 1 - i : i];
        res <<= 8;
    }
    res |= (unsigned char) string[(bytes - 1) * !isBigEndian];
    return res;
}

int WAVHeaderParser::getHeaderSize() const noexcept {
    return headerSize;
}

void WAVHeaderParser::parseWAV(std::string filename) {
    file.open(filename, std::ios::binary);
    char buffer[BUFFER_SIZE];

    file.read(buffer, 4);
    chunkId = buffer;
    if (chunkId != "RIFF")
        throw ExceptionMSG("incorrect_chunk_id");

    file.read(buffer, 4);
    chunkSize = buffer;

    file.read(buffer, 4);
    format = buffer;
    if (format != "WAVE")
        throw ExceptionMSG("incorrect_format");

    file.read(buffer, 4);
    subchunk1Id = buffer;

    file.read(buffer, 4);
    subchunk1Size = binaryStringToInt(buffer, 4, true);
    if (subchunk1Size != 16)
        throw ExceptionMSG("not_pcm_format");

    file.read(buffer, 2);
    audioFormat = binaryStringToInt(buffer, 2, true);
    if (audioFormat != 1)
        throw ExceptionMSG("must_be_no_compress");

    file.read(buffer, 2);
    numChannels = binaryStringToInt(buffer, 2, true);
    if (numChannels != 1)
        throw ExceptionMSG("must_be_mono_channel");

    file.read(buffer, 4);
    sampleRate = binaryStringToInt(buffer, 4, true);
    if (sampleRate != 44100)
        throw ExceptionMSG("must_be_44100_hz");

    file.read(buffer, 4);
    byteRate = binaryStringToInt(buffer, 4, true);

    file.read(buffer, 2);
    blockAlign = binaryStringToInt(buffer, 2, true);

    file.read(buffer, 2);
    bitsPerSample = binaryStringToInt(buffer, 2, true);
    if (bitsPerSample != 16)
        throw ExceptionMSG("must_be_16_bits_per_sample");

    file.read(buffer, 4);
    subchunk2Id = buffer;

    file.read(buffer, 4);
    subchunk2Size = binaryStringToInt(buffer, 4, true);

    file.seekg(subchunk2Size, std::ios::cur);

    file.read(buffer, 4);
    headerSize = subchunk2Size + 48;
}
