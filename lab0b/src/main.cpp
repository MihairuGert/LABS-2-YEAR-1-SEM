#include "FileReader.h"
#include "TextParser.h"
#include "StatisticsModule.h"
#include "FilePrinter.h"
#include <sstream>

void parseText(FileReader fileReader, TextParser textParser) {
    while (!fileReader.isEOF()) {
        std::string stringToParse = fileReader.getLine();
        textParser.parseString(stringToParse);
    }
}

int main(int argc, char** argv) {
    if (argv[1] == nullptr || argv[2] == nullptr)
        return 1;
    FileReader fileReader = FileReader(argv[1]);
	TextParser textParser;
	parseText(fileReader, textParser);

	StatisticsModule statisticsModule;

	FilePrinter filePrinter = FilePrinter(argv[2]);
    filePrinter.printString("Word;Frequency;Frequency(in %)\n");
    for (const auto& i : statisticsModule.getWordsStatistics(textParser.getWordsList())) {
        std::stringstream ss;
        ss << i.word << ';' << i.data << ';' << i.percent << '\n';
        filePrinter.printString(ss.str());
    }
	fileReader.close();
	filePrinter.close();
	return 0;
}