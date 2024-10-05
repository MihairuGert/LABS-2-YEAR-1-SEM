#include <iostream>
#include "BitArray.h"

int main() {
    BitArray bitArray = BitArray(10);
    std::cout << bitArray.to_string();
    return 0;
}
