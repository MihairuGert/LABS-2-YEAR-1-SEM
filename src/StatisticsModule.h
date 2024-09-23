#pragma once

#include "FileReader.h"
#include "TextParser.h"

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
public:
	void countWords(TextParser textParser);
	void findPositionInList(WordFrequency& wordFrequency);
	std::list<WordFrequency> getWordsStatistics();
	StatisticsModule();
};

class Tests
{
public:
    void getStatTest();
    void getFileReaderTest();
    void getTextParserTest();
    void getFilePrinterTest();
};

