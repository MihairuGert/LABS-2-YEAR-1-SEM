#include "ConsoleParser.h"
#include "SoundProcessor.h"

int main(int argc, char* argv[]) {
    ConsoleParser consoleParser;
    try {
        consoleParser.parseConsole(argc, argv);
    }
    catch (const char* error_message) {
        std::cerr << error_message << '\n';
        return 1;
    }
    SoundProcessor soundProcessor = SoundProcessor(consoleParser.getConfigName(), consoleParser.getInputFilenames());
    soundProcessor.runProcess();
    return 0;
}
