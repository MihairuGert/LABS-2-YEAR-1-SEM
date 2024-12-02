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
        return 2;
    }
    auto parser = CSVParser<bool, std::string, std::string>(in, 0);
    try {
        for (const std::tuple<bool, std::string, std::string>& rs : parser) {
            std::cout << rs << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
        return 3;
    }
    return 0;
}