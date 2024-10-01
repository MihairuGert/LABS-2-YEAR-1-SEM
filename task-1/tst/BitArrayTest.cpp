#include "gtest/gtest.h"
#include "BitArray.h"

TEST(functionsAffectingBits, swap) {
    // Test swap function with equal-size Bit Arrays.
    int size = 100;
    BitArray bitArray1 = BitArray(size);
    BitArray bitArray2 = BitArray(size);
    for (int i = 0; i < size; ++i) {
        if (i % 2 == 0) {
            bitArray1.set(i);
        } else {
            bitArray2.set(i);
        }
    }
    BitArray bitArray1saved = bitArray1;
    BitArray bitArray2saved = bitArray2;
    bitArray1.swap(bitArray2);
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(bitArray1[i], bitArray2saved[i]);
        EXPECT_EQ(bitArray2[i], bitArray1saved[i]);
    }
    // Test swap function with not equal-size Bit Arrays.
    bitArray1.resize(size + 1);
    bitArray1saved = bitArray1;
    bitArray1.swap(bitArray2);
    for (int i = 0; i < size + 1; ++i) {
        if (i == size) {
            EXPECT_EQ(bitArray1[i], bitArray1saved[i]);
            break;
        }
        EXPECT_NE(bitArray1[i], bitArray2[i]);
    }
//    std::cout << bitArray1.to_string() << '\n';
//    std::cout << bitArray2.to_string() << '\n';
}

TEST(functionsAffectingBits, resize) {
    int size = 100;
    BitArray bitArray1 = BitArray(0);
    bitArray1.resize(size);
    bitArray1.set(size - 1);
    EXPECT_EQ(bitArray1.size(), size);
    size /= 10;
    bitArray1.resize(size);
    bitArray1.set(size - 1);
    EXPECT_EQ(bitArray1.size(), size);
    bitArray1.resize(size);
    EXPECT_EQ(bitArray1[size - 1], true);
    bitArray1.resize(size);
    EXPECT_EQ(bitArray1.size(), size);
    bitArray1.resize(size + 10);
    EXPECT_EQ(bitArray1[size - 1], true);
}