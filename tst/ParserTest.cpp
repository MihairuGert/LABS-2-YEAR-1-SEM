#include "TextParser.h"
#include "gtest/gtest.h"

TEST(Parser, parseString) {
    std::string line = "test test!@#$%^&*()_+test\n~`test<>{}[]test.test?/№;:test";
    TextParser textParser;
    textParser.parseString(line);
    std::list<std::string> strings;
    for (int i = 0; i < 7; ++i) {
        strings.push_back("test");
    }
    EXPECT_EQ(textParser.getWordsList(), strings);
    line.clear();
    strings.clear();
    line = "";
    textParser.parseString(line);
    textParser.clear();
    EXPECT_EQ(textParser.getWordsList(), strings);
}