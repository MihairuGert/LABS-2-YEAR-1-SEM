#include "FileReader.h"
#include "TextParser.h"
#include "StatisticsModule.h"
#include "FilePrinter.h"
#include <sstream>

int main(int argc, char** argv) {
    if (argv[1] == nullptr || argv[2] == nullptr)
        return 1;
    FileReader fileReader = FileReader(argv[1]);
	TextParser textParser;
	StatisticsModule statisticsModule;

    while (!fileReader.isEOF()) {
        std::string stringToParse = fileReader.getLine();
        std::list<std::string> line = textParser.parseString(stringToParse);
        for (const auto& i : line) {
            statisticsModule.addWord(i);
        }
    }

	FilePrinter filePrinter = FilePrinter(argv[2]);
    filePrinter.printString("Word;Frequency;Frequency(in %)\n");
    for (const auto& i : statisticsModule.getStatistic()) {
        std::stringstream ss;
        ss << i.word << ';' << i.data << ';' << i.percent << '\n';
        filePrinter.printString(ss.str());
    }
	fileReader.close();
	filePrinter.close();
	return 0;
}