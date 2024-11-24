#include "TuplePrinter.h"
#include "CSVParser.h"

int main(int argc, char** argv) {
    //std::tuple<int, double, std::string, int> t = {1, 2.71, "meow", 54};
    //std::cout << t;
    std::ifstream in;
    in.open("tst.csv");
    // TODO OFFSET
    auto parser = CSVParser<int, std::string, std::string>(in, 0);
//    for (std::tuple<int, std::string, std::string> rs : parser) {
//        std::cout << rs << '\n';
//    }

//    std::tuple<int, std::string, int> tuple = parser.getTuple();
//    std::cout << tuple;
//    tuple = parser.getTuple();
//    std::cout << tuple;
//    tuple = parser.getTuple();
//    std::cout << tuple;
    //parser.getTuple();
    return 0;
}