#include "SoundProcessor.h"

void SoundProcessor::runProcess() {
    // TODO: GET FROM ARGV AND MAKE VECTOR OF INPUT FILES
    config.open("config.txt");
    ConfigParser configParser = ConfigParser(&config);
    std::string previousFilename = "severe_tire_damage.wav";
    //std::string defaultOutName = "out.wav";
    std::string outName = "out.wav";
    int it = 0;
    while(!config.eof()) {
        Cmd* cmd = configParser.getCommand();
        // TODO ADD FABRIC HERE
        if (cmd->getCmdName() == "MUTE") {
            MuterFactory muterFactory;
            Converter* muter = muterFactory.createConverter(previousFilename, outName);
            std::cout << "start\n";
            muter->convert(cmd->getInterval()[0], cmd->getInterval()[1]);
            std::cout << "finish\n";
            delete(muter);
            previousFilename = outName;
            it++;
            std::cout << it << '\n';
        }
//        std::cout << cmd->getCmdName() << ' ';
//        if (!cmd->getInterval().empty()) {
//            for (int i = 0; i < cmd->getInterval().size(); i++) {
//                std::cout << cmd->getInterval()[i] << ' ';
//            }
//        }
//        std::cout << '\n';
    }
    out.close();
    config.close();
}
