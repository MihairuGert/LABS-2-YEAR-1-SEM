#include "out.h"

namespace CSVModule {
	void PrintTableHeadInFile(std::ostream& out) {
		out << "Слово;Частота;Частота (в %)\n";
	}
	void PrintTableData(std::ostream& out, std::list<WordFrequency>& words, int& words_number) {
		while (words.size() != 0) {
			out << words.front().word << ";" << words.front().data << ";"
				<< ((double)words.front().data/words_number) * 100 << "\n";
			words.pop_front();
		}
		//out << "in total: " << words_number << " words";
	}
}

