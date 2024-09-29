#include "StatisticsModule.h"
#include "gtest/gtest.h"

TEST(Statistics, createStatistcsList) {
    StatisticsModule statisticsModule;
    std::list<std::string> wordsList;
    statisticsModule.createStatistcsList(wordsList);

    // Check for handling empty input.
    EXPECT_EQ(statisticsModule.getWordsStatistics().size(), 0);
    wordsList.emplace_back("meow");
    statisticsModule.createStatistcsList(wordsList);

    // Check for handling one word input.
    EXPECT_EQ(statisticsModule.getWordsStatistics().size(), 1);
    EXPECT_EQ(statisticsModule.getWordsStatistics().front().data, 1);
    EXPECT_EQ(statisticsModule.getWordsStatistics().front().percent, 100);

    // Check for handling two word input.
    wordsList.emplace_back("meow");
    statisticsModule.createStatistcsList(wordsList);
    EXPECT_EQ(statisticsModule.getWordsStatistics().size(), 1);
    EXPECT_EQ(statisticsModule.getWordsStatistics().front().data, 2);
    EXPECT_EQ(statisticsModule.getWordsStatistics().front().percent, 100);\

    // Check for handling a lot of similar words input.
    int cycleLimit = 10;
    for(int i = 0; i < cycleLimit; i++) {
        wordsList.emplace_back("a");
    }
    statisticsModule.createStatistcsList(wordsList);
    EXPECT_EQ(statisticsModule.getWordsStatistics().size(), 2);
    for (auto& i : statisticsModule.getWordsStatistics()) {
        if (i.word == "meow") {
            EXPECT_EQ(i.data, 2);
            EXPECT_EQ(i.percent, 2.0 / (cycleLimit + 2) * 100);
        }
        else {
            EXPECT_EQ(i.data, cycleLimit);
            EXPECT_EQ(i.percent, cycleLimit / (cycleLimit + 2.0) * 100);
        }
    }
}

TEST(Statistics, findPositionInList) {
    StatisticsModule statisticsModule;
    std::list<std::string> wordsList;
    wordsList.emplace_back("1");
    wordsList.emplace_back("2");
    wordsList.emplace_back("3");
    statisticsModule.createStatistcsList(wordsList);
    EXPECT_EQ(statisticsModule.getWordsStatistics().size(), 3);
    WordFrequency wordFrequency = WordFrequency("1", 1, 1 / 3.0 * 100);
    statisticsModule.findPositionInList(wordFrequency);
    for (auto& i : statisticsModule.getWordsStatistics()) {
        if (i.word == "1") {
            EXPECT_EQ(i.data, 2);
            EXPECT_EQ(i.percent, 2.0 / 3 * 100);
        }
    }
}