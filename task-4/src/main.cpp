#include "TuplePrinter.h"
#include "CSVParser.h"

int main(int argc, char** argv) {
    std::ifstream in;
    in.open("tst.csv");
    auto parser = CSVParser<int, std::string, std::string>(in, 0, ';', '\n');
    for (const std::tuple<int, std::string, std::string>& rs : parser) {
        std::cout << rs << '\n';
    }
    return 0;
}