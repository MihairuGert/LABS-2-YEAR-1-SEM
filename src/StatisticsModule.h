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
	int wordsAmount;
    static bool compare(WordFrequency& first, WordFrequency& second);
public:
	void countWords(const std::list<std::string>& wordsList);
	void findPositionInList(WordFrequency& wordFrequency);
	std::list<WordFrequency> getWordsStatistics();
    std::string getStatisticsTable();
	StatisticsModule();
};

