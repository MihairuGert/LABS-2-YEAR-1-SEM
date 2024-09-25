#include "FileReader.h"
#include "TextParser.h"
#include "StatisticsModule.h"
#include "FilePrinter.h"

void parseText(FileReader fileReader, TextParser textParser) {
    while (true) {
        std::string stringToParse = fileReader.getLine();
        if (stringToParse.empty()) {
            break;
        }
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
	statisticsModule.countWords(textParser.getWordsList());

	FilePrinter filePrinter = FilePrinter(argv[2]);
	filePrinter.printString(statisticsModule.getStatisticsTable());

	fileReader.close();
	filePrinter.close();
	return 0;
}