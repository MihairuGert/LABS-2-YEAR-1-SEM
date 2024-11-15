#include "gtest/gtest.h"
#include "ConfigParser.h"
#include <sstream>

TEST(ConfigParserTest, TestCommentCommand) {
    std::istringstream input("# comment kommentariy\n");
    ConfigParser parser(reinterpret_cast<std::ifstream *>(&input));
    Cmd* cmd = parser.getCommand();
    EXPECT_EQ(cmd->getCmdName(), "COMMENT");
    EXPECT_TRUE(cmd->getInterval().empty());
    delete cmd;
}

TEST(ConfigParserTest, TestMuteCommand) {
    std::istringstream input("mute 10 20\n");
    ConfigParser parser(reinterpret_cast<std::ifstream *>(&input));
    Cmd* cmd = parser.getCommand();
    EXPECT_EQ(cmd->getCmdName(), "MUTE");
    EXPECT_EQ(cmd->getInterval(), std::vector<int>({10, 20}));
    delete cmd;
}

TEST(ConfigParserTest, TestMuteCommandInvalidTime) {
    std::istringstream input("mute -10 20\n");
    ConfigParser parser(reinterpret_cast<std::ifstream *>(&input));
    EXPECT_THROW(parser.getCommand(), ExceptionMSG);
}

TEST(ConfigParserTest, TestBoostCommand) {
    std::istringstream input("boost 10 20 1.5\n");
    ConfigParser parser(reinterpret_cast<std::ifstream *>(&input));
    Cmd* cmd = parser.getCommand();
    EXPECT_EQ(cmd->getCmdName(), "BOOST");
    EXPECT_EQ(cmd->getInterval(), std::vector<int>({10, 20}));
    EXPECT_DOUBLE_EQ(cmd->getCoef(), 1.5);
    delete cmd;
}

TEST(ConfigParserTest, TestBoostCommandInvalidTime) {
    std::istringstream input("boost -10 20 1.5\n");
    ConfigParser parser(reinterpret_cast<std::ifstream *>(&input));
    EXPECT_THROW(parser.getCommand(), ExceptionMSG);
}

TEST(ConfigParserTest, TestBoostCommandInvalidCoef) {
    std::istringstream input("boost 10 20 -1.5\n");
    ConfigParser parser(reinterpret_cast<std::ifstream *>(&input));
    EXPECT_THROW(parser.getCommand(), ExceptionMSG);
}

TEST(ConfigParserTest, TestMixCommand) {
    std::istringstream input("mix $1 10\n");
    ConfigParser parser(reinterpret_cast<std::ifstream *>(&input));
    Cmd* cmd = parser.getCommand();
    EXPECT_EQ(cmd->getCmdName(), "MIX");
    EXPECT_EQ(cmd->getInterval(), std::vector<int>({10}));
    EXPECT_EQ(cmd->getInputIndex(), 1);
    delete cmd;
}

TEST(ConfigParserTest, TestMixCommandInvalidTime) {
    std::istringstream input("mix $1 -10\n");
    ConfigParser parser(reinterpret_cast<std::ifstream *>(&input));
    EXPECT_THROW(parser.getCommand(), ExceptionMSG);
}

TEST(ConfigParserTest, TestMixCommandInvalidInputIndex) {
    std::istringstream input("mix $0 10\n");
    ConfigParser parser(reinterpret_cast<std::ifstream *>(&input));
    EXPECT_THROW(parser.getCommand(), ExceptionMSG);
}

TEST(ConfigParserTest, TestUnknownCommand) {
    std::istringstream input("sus\n");
    ConfigParser parser(reinterpret_cast<std::ifstream *>(&input));
    EXPECT_THROW(parser.getCommand(), ExceptionMSG);
}
