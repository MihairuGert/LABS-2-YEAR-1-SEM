#include <iostream>
#include "BitArray.h"

int main() {
    BitArray bitArray = BitArray(10);
    bitArray[0] = 1;
    bitArray[3] = 1;
    std::cout << bitArray.to_string() << '\n';
    bitArray = ~bitArray;
    std::cout << bitArray.to_string() << '\n';
    return 0;
}
