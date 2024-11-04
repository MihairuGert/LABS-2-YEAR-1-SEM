#include "SoundProcessor.h"

void SoundProcessor::runProcess() {
    // TODO: GET FROM ARGV
    in.open("config.txt");

    ConfigParser configParser = ConfigParser(&in);
    while(!in.eof()) {
        Cmd* cmd = configParser.getCommand();
        std::cout << cmd->getCmdName() << ' ';
        if (!cmd->getInterval().empty()) {
            for (int i = 0; i < cmd->getInterval().size(); i++) {
                std::cout << cmd->getInterval()[i] << ' ';
            }
        }
        std::cout << '\n';
    }
}
