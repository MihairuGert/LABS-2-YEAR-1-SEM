#pragma once
#include <iostream>
#include <sstream>
#include <list>

typedef struct WordFrequency {
	std::string word;
	int data;
	double percent;

	WordFrequency(const std::string& word, int data, double percent) : word(word), data(data), percent(percent) {}
} WordFrequency;

class StatisticsModule
{
private:
	std::list<WordFrequency>* wordsStatistics;
    std::list<std::string>* wordsBank;
	int wordsAmount{};
    static bool compare(WordFrequency& first, WordFrequency& second);
    void createStatistcsList(const std::list<std::string>& wordsList);
    void findPositionInList(WordFrequency& wordFrequency);
public:
    std::list<WordFrequency> getStatistic();
    void addWord(const std::string& word);
	StatisticsModule();
};

