#include "StatisticsModule.h"
#include "gtest/gtest.h"

TEST(Statistics, addWordToStatistic) {
    StatisticsModule statisticsModule;
    std::list<std::string> wordsList;
    statisticsModule.addWord("meow");
    int cycleLimit = 10;
    for(int i = 0; i < cycleLimit; i++) {
        statisticsModule.addWord("a");
    }
    const auto& statistics = statisticsModule.getStatistic();
    EXPECT_EQ(statistics.size(), 2);
    for (auto& i : statistics) {
        if (i.word == "meow") {
            EXPECT_EQ(i.data, 1);
            EXPECT_EQ(i.percent, 1.0 / (cycleLimit + 1) * 100);
        }
        else {
            EXPECT_EQ(i.data, cycleLimit);
            EXPECT_EQ(i.percent, cycleLimit / (cycleLimit + 1.0) * 100);
        }
    }
}