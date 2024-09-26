#include "FilePrinter.h"
#include "gtest/gtest.h"
#include <fstream>

TEST(FilePrinterTest, printString) {
    std::string filename = "test_print_string.txt";
    std::string testString = "Hello, World!";
    FilePrinter printer(filename);
    printer.printString(testString);
    printer.close();
    std::ifstream in(filename);
    std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    EXPECT_EQ(content, testString);
}
