#include "SoundProcessor.h"

void SoundProcessor::runProcess() {
    // TODO: GET FROM ARGV
    config.open("config.txt");
    ConfigParser configParser = ConfigParser(&config);
    std::string previousFilename = "severe_tire_damage.wav";
    //std::string defaultOutName = "out.wav";
    std::string outName = "out.wav";
    while(!config.eof()) {
        Cmd* cmd = configParser.getCommand();
        if (cmd->getCmdName() == "MUTE") {
            MuterFactory muterFactory;
            Converter* muter = muterFactory.createConverter(previousFilename, outName);
            muter->convert(0, 2);
            //
            delete(muter);
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
