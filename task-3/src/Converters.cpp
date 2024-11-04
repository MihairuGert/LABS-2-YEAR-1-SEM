#include "Converters.h"

void Mixer::convert(const std::ifstream &in, int start, int finish) {
    Converter::convert(in, start, finish);
}

void Muter::convert(const std::ifstream &in, int start, int finish) {
    Converter::convert(in, start, finish);
}

Converter* MuterFactory::createConverter() {
    return new Muter();
}

Converter* MixerFactory::createConverter() {
    return new Mixer();
}

void Converter::convert(const std::ifstream &in, int start, int finish) {

}

void Converter::setHeaderEnd(int headerEnd) {
    this->headerEnd = headerEnd;
}
