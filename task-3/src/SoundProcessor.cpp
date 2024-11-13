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
            convert(muterFactory, cmd->getInterval()[0], cmd->getInterval()[1], previousFilename, outName);
        }
        else if (cmd->getCmdName() == "MIX") {
            MixerFactory mixerFactory;
            convert(mixerFactory, cmd->getInterval()[0], cmd->getInterval()[1], inFilenames[cmd->getInputIndex()], outName);
        }
        if (cmd->getCmdName() != "COMMENT")
            previousFilename = outName;
    }
    config.close();
}

void SoundProcessor::convert(ConverterFactory& converterFactory, int start, int finish, std::string& inFilename,
                             std::string& outFilename) {
    Converter* converter = converterFactory.createConverter(inFilename, outFilename);
    converter->convert(start, finish);
    delete(converter);
}
