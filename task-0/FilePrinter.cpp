#include "FilePrinter.h"

void FilePrinter::open() {
	out->open(filename);
}

void FilePrinter::close() {
	out->close();
	delete out;
}

void FilePrinter::printTableData(StatisticsModule statisticsModule) {
	std::list<WordFrequency> wordsStatistics = statisticsModule.getWordsStatistics();
	*out << "Слово;Частота;Частота(в %)" << '\n';
	while (!wordsStatistics.empty()) {
		*out << wordsStatistics.front().word << ";" << wordsStatistics.front().data << ";"
			<< wordsStatistics.front().percent << "\n";
		wordsStatistics.pop_front();
	}
	//*out << "in total: " << words_number << " words";
}

FilePrinter::FilePrinter(const std::string& filename) {
	this->filename = filename;
	auto* out = new std::ofstream;
	this->out = out;
	FilePrinter::open();
}