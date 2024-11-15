#include "ConsoleParser.h"
#include "SoundProcessor.h"

int main(int argc, char* argv[]) {
    RunMode status;
    ConsoleParser consoleParser;
    try {
        status = consoleParser.parseConsole(argc, argv);
    }
    catch (const char* error_message) {
        std::cerr << error_message << '\n';
        return 1;
    }
    if (status == RunMode::HELP) {
        SoundProcessor soundProcessor = SoundProcessor();
        soundProcessor.printHelp();
        return 0;
    }
    SoundProcessor soundProcessor = SoundProcessor(consoleParser.getConfigName(), consoleParser.getInputFilenames());
    soundProcessor.runProcess();
    return 0;
}
