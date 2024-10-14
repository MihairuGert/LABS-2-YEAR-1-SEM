#include <iostream>
#include "BitArray.h"

int main() {
    BitArray bitArray = BitArray(10);
    bitArray[32] = true;
    std::cout << bitArray.to_string();
    return 0;
}
