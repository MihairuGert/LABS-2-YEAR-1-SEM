#include "FileReader.h"
#include "TextParser.h"
#include "StatisticsModule.h"
#include "FilePrinter.h"



int main(int argc, char** argv) {
    if (argv[1] == nullptr || argv[2] == nullptr)
        return 1;
    FileReader fileReader = FileReader(argv[1]);
	TextParser textParser;
	textParser.parseTextInFile(fileReader);// here too

	StatisticsModule statisticsModule;
	statisticsModule.countWords(textParser);//here too

	FilePrinter filePrinter = FilePrinter(argv[2]);
	filePrinter.printTableData(statisticsModule); //классы не связанные передавать только значениями

	fileReader.close();
	filePrinter.close();
	return 0;
}