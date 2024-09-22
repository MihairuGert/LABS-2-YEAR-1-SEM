#include "StatisticsModule.h"

void StatisticsModule::countWords(TextParser textParser) {
	std::list<std::string> wordsList = textParser.getWordsList();
	wordsAmount = wordsList.size();
	for (const std::string& i : wordsList) {
		WordFrequency wordFrequency = WordFrequency(i, 1, (double) 1 / wordsAmount * 100);
		findPositionInList(wordFrequency);
	}
}

void StatisticsModule::findPositionInList(WordFrequency& wordFrequency) {
	for (WordFrequency& i : *wordsStatistics) {
		if (i.word == wordFrequency.word) {
			i.data++;
			i.percent = (double)i.data / wordsAmount * 100;
			return;
		}
	}
	(*wordsStatistics).push_back(wordFrequency);
}

std::list<WordFrequency> StatisticsModule::getWordsStatistics() {
	return *wordsStatistics;
}

StatisticsModule::StatisticsModule() {
	auto* words = new std::list<WordFrequency>;
	this->wordsStatistics = words;
	wordsAmount = 0;
}