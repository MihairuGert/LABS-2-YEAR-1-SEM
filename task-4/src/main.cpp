#include "TuplePrinter.h"
#include "CSVParser.h"

int main(int argc, char** argv) {
    std::tuple<int, double, std::string, int> t = {1, 2.71, "meow", 54};
    std::cout << t;
    return 0;
}