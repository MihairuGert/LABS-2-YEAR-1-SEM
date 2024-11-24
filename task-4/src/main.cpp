#include "TuplePrinter.h"
#include "CSVParser.h"

int main(int argc, char** argv) {
    std::ifstream in;
    if (argc > 1) {
        in.open(argv[1]);
    }
    else {
        std::cerr << "Not enough input";
        return 1;
    }
    if (!in.is_open()) {
        std::cerr << "No file";
        return 1;
    }
    auto parser = CSVParser<bool, std::string, std::string>(in, 0);
    for (const std::tuple<bool, std::string, std::string>& rs : parser) {
        std::cout << rs << '\n';
    }
    return 0;
}