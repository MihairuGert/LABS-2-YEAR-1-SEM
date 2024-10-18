#include "StatisticsModule.h"

bool StatisticsModule::compare(WordFrequency& first, WordFrequency& second) {
    return (first.data > second.data);
}

void StatisticsModule::createStatistcsList(const std::list<std::string>& wordsList) {
    wordsStatistics->clear();
	wordsAmount = wordsList.size();
	for (const std::string& i : wordsList) {
        WordFrequency wordFrequency = WordFrequency(i, 1, (double) 1 / wordsAmount * 100);
        findPositionInList(wordFrequency);
    }
    wordsStatistics->sort(compare);
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

std::list<WordFrequency> StatisticsModule::getStatistic() {
    if (!wordsBank) {
        return {};
    }
    createStatistcsList(*wordsBank);
    return *wordsStatistics;
}

StatisticsModule::StatisticsModule() {
	auto* words = new std::list<WordFrequency>;
    auto* wordsBank = new std::list<std::string>;
	this->wordsStatistics = words;
    this->wordsBank = wordsBank;
	wordsAmount = 0;
}

void StatisticsModule::addWord(const std::string& word) {
    wordsBank->push_back(word);
}
