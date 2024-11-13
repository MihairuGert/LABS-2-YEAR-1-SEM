#include "SoundProcessor.h"

void SoundProcessor::runProcess() {
    config.open(configFilename);
    ConfigParser configParser = ConfigParser(&config);
    std::string previousFilename = inFilenames[1];
    std::string outName = inFilenames[0];
    while(!config.eof()) {
        Cmd* cmd = configParser.getCommand();
        // TODO ADD FACTORY HERE
        if (cmd->getCmdName() == "MUTE") {
            MuterFactory muterFactory;
            Converter* muter = muterFactory.createConverter(previousFilename, outName);
            muter->convert(cmd->getInterval()[0], cmd->getInterval()[1]);
            delete(muter);
            previousFilename = outName;
        }
        if (cmd->getCmdName() == "MIX") {
            MixerFactory mixerFactory;
            Converter* mixer = mixerFactory.createConverter(inFilenames[cmd->getInputIndex()], outName);
            mixer->convert(cmd->getInterval()[0], -1);
            delete(mixer);
            previousFilename = outName;
        }
    }
    out.close();
    config.close();
}