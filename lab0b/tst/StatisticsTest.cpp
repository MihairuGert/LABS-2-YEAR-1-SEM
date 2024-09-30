#include "StatisticsModule.h"
#include "gtest/gtest.h"

TEST(Statistics, getWordsStatistics) {
    StatisticsModule statisticsModule;
    std::list<std::string> wordsList;
    auto statistics = statisticsModule.getWordsStatistics(wordsList);

    // Check for handling empty input.
    EXPECT_EQ(statistics.size(), 0);
    wordsList.emplace_back("meow");
    statistics = statisticsModule.getWordsStatistics(wordsList);

    // Check for handling one word input.
    EXPECT_EQ(statistics.size(), 1);
    EXPECT_EQ(statistics.front().data, 1);
    EXPECT_EQ(statistics.front().percent, 100);

    // Check for handling two word input.
    wordsList.emplace_back("meow");
    statistics = statisticsModule.getWordsStatistics(wordsList);
    EXPECT_EQ(statistics.size(), 1);
    EXPECT_EQ(statistics.front().data, 2);
    EXPECT_EQ(statistics.front().percent, 100);

    // Check for handling a lot of similar words input.
    int cycleLimit = 10;
    for(int i = 0; i < cycleLimit; i++) {
        wordsList.emplace_back("a");
    }
    statistics = statisticsModule.getWordsStatistics(wordsList);
    EXPECT_EQ(statistics.size(), 2);
    for (auto& i : statistics) {
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
