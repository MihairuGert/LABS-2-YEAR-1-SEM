#include "SoundProcessor.h"

// TODO GTESTS

void SoundProcessor::runProcess() {
    config.open(configFilename);
    ConfigParser configParser = ConfigParser(&config);
    std::string previousFilename = inFilenames[1];
    std::string outName = inFilenames[0];
    prepareOutput(outName, previousFilename);
    while(!config.eof()) {
        Cmd* cmd = configParser.getCommand();
        if (cmd->getCmdName() == "MUTE") {
            MuterHelperFactory muterFactory;
            convert(muterFactory, cmd->getInterval()[0], cmd->getInterval()[1],DEFAULT_COEFFICIENT, previousFilename, outName);
        }
        else if (cmd->getCmdName() == "MIX") {
            MixerHelperFactory mixerFactory;
            convert(mixerFactory, cmd->getInterval()[0], cmd->getInterval()[1],DEFAULT_COEFFICIENT, inFilenames[cmd->getInputIndex()], outName);
        }
        else if (cmd->getCmdName() == "BOOST") {
            BoosterHelperFactory boosterFactory;
            convert(boosterFactory, cmd->getInterval()[0], cmd->getInterval()[1], cmd->getCoef(), previousFilename, outName);
        }
        if (cmd->getCmdName() != "COMMENT")
            previousFilename = outName;
    }
    config.close();
}

void SoundProcessor::convert(ConverterHelperFactory& converterFactory, int start, int finish, double coef, std::string& inFilename,
                             std::string& outFilename) {
    ConverterHelper* converterHelper = converterFactory.createConverter(inFilename, outFilename);
    converterHelper->convert(start, finish, coef);
    delete(converterHelper);
}

SoundProcessor::SoundProcessor() {}

void SoundProcessor::printHelp() {
    std::vector<Converter*> availableConverters = getAvailableConvertersList();
    std::cout << "* List of available converters: " << '\n';
    for (const auto& i : availableConverters) {
        std::cout << i->getName() << '\n';
        std::cout << '\t' << i->getParameters() << '\n';
        std::cout << i->getBriefDescription() << "\n\n";
    }
}

void SoundProcessor::prepareOutput(std::string outName, std::string firstInput) {
    remove(outName.c_str());
    MuterHelperFactory muterFactory;
    convert(muterFactory, 0, 0, DEFAULT_COEFFICIENT, firstInput, outName);
}

std::vector<Converter*> SoundProcessor::getAvailableConvertersList() {
    std::vector<Converter*> availableConverters;
    MuterFactory muterFactory;
    availableConverters.push_back(muterFactory.createConverter());
    MixerFactory mixerFactory;
    availableConverters.push_back(mixerFactory.createConverter());
    BoosterFactory boosterFactory;
    availableConverters.push_back(boosterFactory.createConverter());
    return availableConverters;
}
