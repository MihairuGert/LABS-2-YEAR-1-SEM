#include "SoundProcessor.h"

void SoundProcessor::runProcess() {
    config.open(configFilename);
    ConfigParser configParser = ConfigParser(&config);
    std::string previousFilename = inFilenames[1];
    std::string outName = inFilenames[0];
    remove(outName.c_str());
    while(!config.eof()) {
        Cmd* cmd = configParser.getCommand();
        if (cmd->getCmdName() == "MUTE") {
            MuterFactory muterFactory;
            convert(muterFactory, cmd->getInterval()[0], cmd->getInterval()[1],DEFAULT_COEFFICIENT, previousFilename, outName);
        }
        else if (cmd->getCmdName() == "MIX") {
            MixerFactory mixerFactory;
            convert(mixerFactory, cmd->getInterval()[0], cmd->getInterval()[1],DEFAULT_COEFFICIENT, inFilenames[cmd->getInputIndex()], outName);
        }
        else if (cmd->getCmdName() == "BOOST") {
            BoosterFactory boosterFactory;
            convert(boosterFactory, cmd->getInterval()[0], cmd->getInterval()[1], cmd->getCoef(), previousFilename, outName);
        }
        if (cmd->getCmdName() != "COMMENT")
            previousFilename = outName;
    }
    config.close();
}

void SoundProcessor::convert(ConverterFactory& converterFactory, int start, int finish, double coef, std::string& inFilename,
                             std::string& outFilename) {
    Converter* converter = converterFactory.createConverter(inFilename, outFilename);
    converter->convert(start, finish, coef);
    delete(converter);
}
