#include "gtest/gtest.h"
#include "ConsoleParser.h"
#include <sstream>
#include <vector>

TEST(ConsoleParserTest, TestHelpCommand) {
    char* argv[] = {(char*)"program", (char*)"-h"};
    int argc = 2;
    ConsoleParser parser;
    EXPECT_EQ(parser.parseConsole(argc, argv), RunMode::HELP);
}

TEST(ConsoleParserTest, TestNotEnoughFiles) {
    char* argv[] = {(char*)"program", (char*)"-c", (char*)"config.txt"};
    int argc = 3;
    ConsoleParser parser;
    EXPECT_THROW(parser.parseConsole(argc, argv), ExceptionMSG);
}

TEST(ConsoleParserTest, TestIncorrectConsoleCommandFormat) {
    char* argv[] = {(char*)"program", (char*)"123456789abcdef", (char*)"file1.wav", (char*)"file2.wav"};
    int argc = 4;
    ConsoleParser parser;
    EXPECT_THROW(parser.parseConsole(argc, argv), ExceptionMSG);
}

TEST(ConsoleParserTest, TestIncorrectAudioFormat) {
    char* argv[] = {(char*)"program", (char*)"-c", (char*)"config.txt", (char*)"file1.wav", (char*)"file2.mp3"};
    int argc = 5;
    ConsoleParser parser;
    EXPECT_THROW(parser.parseConsole(argc, argv), ExceptionMSG);
}

TEST(ConsoleParserTest, TestValidCommand) {
    char* argv[] = {(char*)"program", (char*)"-c", (char*)"config.txt", (char*)"file1.wav", (char*)"file2.wav"};
    int argc = 5;
    ConsoleParser parser;
    EXPECT_EQ(parser.parseConsole(argc, argv), RunMode::RUN);
    EXPECT_EQ(parser.getConfigName(), "config.txt");
    EXPECT_EQ(parser.getInputFilenames(), std::vector<std::string>({"file1.wav", "file2.wav"}));
}
