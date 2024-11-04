#include "WAVHeaderParser.h"

int main() {
    WAVHeaderParser wavHeaderParser;
    try {
         wavHeaderParser.parseWAV("severe_tire_damage.wav");
    }
    catch (const char* error_message) {
        std::cerr << error_message << '\n';
    }
    std::cout << wavHeaderParser.getHeaderSize();
    return 0;
}
