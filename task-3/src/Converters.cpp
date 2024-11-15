#include "Converters.h"

char *Converter::convert(char *outStream, char *inStream, double coef) {
    return nullptr;
}

char *Muter::convert(char *outStream, char *inStream, double coef) {
    for (int i = 0; i < second; ++i) {
        outStream[i] = 0;
    }
    return outStream;
}

std::string Muter::getName() const {
    return "Muter";
}

std::string Muter::getBriefDescription() const {
    return "Mutes a wave file from begin to end.";
}

std::string Muter::getParameters() const {
    return "mute <begin[sec.]> <end[sec.]>";
}

char *Mixer::convert(char *outStream, char *inStream, double coef) {
    for (int i = 0; i < second; ++i) {
        outStream[i] = static_cast<char>(((outStream[i] + inStream[i]) / 2));
    }
    return outStream;
}

std::string Mixer::getName() const {
    return "Mixer";
}

std::string Mixer::getBriefDescription() const {
    return "Mixes two wave files from begin until one ends: $n, where n is the order in a console line,\n"
           "and the output file of a previous converter or the first file from the line.";
}

std::string Mixer::getParameters() const {
    return "mix $<n> <begin = 0>";
}

char *Booster::convert(char *outStream, char *inStream, double coef) {
    for (int i = 0; i < second; ++i) {
        outStream[i] = static_cast<char>(outStream[i] * coef);
    }
    return outStream;
}

std::string Booster::getName() const {
    return "Booster";
}

std::string Booster::getBriefDescription() const {
    return "Increases/decreases the volume from begin to end. If 0 < coefficient < 1, decreases, if > 1, increases.\n"
           "Highly not recommended to use coefficient > 1.5.";
}

std::string Booster::getParameters() const {
    return "boost <begin[sec.]> <end[sec.]> <coefficient>";
}

Converter* MuterFactory::createConverter() const {
    return new Muter();
}

Converter* MixerFactory::createConverter() const {
    return new Mixer();
}

Converter *BoosterFactory::createConverter() const {
    return new Booster();
}

