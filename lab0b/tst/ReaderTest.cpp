#include "FileReader.h"
#include "gtest/gtest.h"
#include <fstream>

TEST(FileReaderTest, getLine1) {
    std::string filename = "test_getLine.txt";
    std::string testString = "Hello, World!";
    std::ofstream test(filename);
    test << testString;
    test.close();
    FileReader reader(filename);
    std::string line = reader.getLine();
    reader.close();
    EXPECT_EQ(line, testString);
}

TEST(FileReaderTest, getLine2) {
    std::string filename = "test_getLine.txt";
    std::string testString;
    std::ofstream test(filename);
    FileReader reader(filename);
    std::string line = reader.getLine();
    reader.close();
    EXPECT_EQ(line, testString);
}
