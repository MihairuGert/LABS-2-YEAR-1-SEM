#pragma once
#include <fstream>
#include <string>
#include <list>

typedef struct WordFrequency {
	std::string word;
	int data;

	WordFrequency(const std::string& word, int data) : word(word), data(data) {}
} WordFrequency;

namespace CSVModule {
	void PrintTableHeadInFile(std::ostream& out);
	void PrintTableData(std::ostream& out, std::list<WordFrequency>& words, int& words_number);
}