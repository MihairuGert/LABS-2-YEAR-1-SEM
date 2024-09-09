#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include "out.h"

bool compare(WordFrequency& first, WordFrequency& second) {
	return (first.data > second.data);
}

void FindPositionInList(std::list<WordFrequency>& words, WordFrequency& word_frequency) {
	for (WordFrequency& i : words) {
		if (i.word.compare(word_frequency.word) == 0) {
			i.data++;
			return;
		}
	}
	words.push_back(word_frequency);
}

void FillWordsList(std::list<WordFrequency>& words, WordFrequency& word_frequency, int& words_number) {
	std::string res;
	for (int i = 0; i < word_frequency.word.length(); i++) {
		if (!(word_frequency.word[i] < '0' || (word_frequency.word[i] > '9' && word_frequency.word[i] < 'A')
			|| (word_frequency.word[i] > 'Z' && word_frequency.word[i] < 'a') || word_frequency.word[i] > 'z')) {
			res.push_back(word_frequency.word[i]);
		}
		else{
			if (res.empty()) {
				continue;
			}
			WordFrequency temp = WordFrequency(res, 1);
			FindPositionInList(words, temp);
			words_number++;
			res.clear();
		}
	}
	if (!res.empty()) {
		WordFrequency temp = WordFrequency(res, 1);
		FindPositionInList(words, temp);
		words_number++;
	}
}
int main(int argc, char** argv) {
	std::ofstream out(argv[2]);
	CSVModule::PrintTableHeadInFile(out);
	std::ifstream in(argv[1]);
	std::list<WordFrequency> words;
	std::string buffer;
	int words_number = 0;
	while (std::getline(in, buffer)) {
		std::stringstream ss(buffer);
		while (std::getline(ss, buffer, ' ')) {
			WordFrequency word_frequency = WordFrequency(buffer, 1);
			FillWordsList(words, word_frequency, words_number);
		}
	}
	words.sort(compare);
	CSVModule::PrintTableData(out, words, words_number);
	out.close();
	in.close();
	return 0;
}