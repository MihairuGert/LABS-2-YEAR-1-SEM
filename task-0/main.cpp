#include "FileReader.h"
#include "TextParser.h"
#include "StatisticsModule.h"
#include "FilePrinter.h"

int main(int argc, char** argv) {
	FileReader fileReader = FileReader(argv[1]);
	TextParser textParser;
	textParser.parseTextInFile(fileReader);

	StatisticsModule statisticsModule;
	statisticsModule.countWords(textParser);

	FilePrinter filePrinter = FilePrinter(argv[2]);
	filePrinter.printTableData(statisticsModule);

	fileReader.close();
	filePrinter.close();
	return 0;
}