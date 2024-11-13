#include "ConsoleParser.h"

void ConsoleParser::parseConsole(int argc, char **argv)  {
    if (argc <= 1) {
        throw ExceptionMSG("no_console_command");
    }
    if (argc <= 4) {
        throw ExceptionMSG("not_enough_files_to_run");
    }
    for (int i = 1; i < argc; ++i) {
        if (i == 1 && !strcmp(argv[i], "-c")) {
            configFilename = argv[i + 1];
            ++i;
            continue;
        }
        else if (i == 1 && strcmp(argv[i], "-c") != 0) {
            throw ExceptionMSG("incorrect_console_command_format");
        }
        else if (i > 2 && !isWav(argv[i]))
            throw ExceptionMSG("not_wav");
        inputFilenames.emplace_back(argv[i]);
    }
}

std::string ConsoleParser::getConfigName() const noexcept {
    return configFilename;
}

std::vector<std::string> ConsoleParser::getInputFilenames() const noexcept {
    return inputFilenames;
}

bool ConsoleParser::isWav(char *str1) const noexcept {
    char* ptr = strstr(str1, ".wav");
    if (str1 + strlen(str1) - ptr != 4) {
        return false;
    }
    return true;
}
