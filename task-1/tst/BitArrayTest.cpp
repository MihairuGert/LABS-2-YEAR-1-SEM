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

TEST(functionsAffectingBits, operatorEquality) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    for (int i = 0; i < size; ++i) {
        if (i % 2 == 0)
            bitArray.set(i);
    }
    BitArray bitArrayCopy = bitArray;
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(bitArray[i], bitArrayCopy[i]);
    }
    bitArrayCopy = ~bitArrayCopy;
    for (int i = 0; i < size; ++i) {
        EXPECT_NE(bitArray[i], bitArrayCopy[i]);
    }
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

TEST(functionsAffectingBits, clear) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    EXPECT_EQ(size, bitArray.size());
    bitArray.clear();
    EXPECT_EQ(bitArray.size(), 0);
}

TEST(functionsAffectingBits, push_back) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    bitArray.push_back(true);
    EXPECT_EQ(bitArray[size], true);
    bitArray.push_back(false);
    EXPECT_EQ(bitArray[size + 1], false);
    EXPECT_EQ(bitArray.size(), size + 2);
    bitArray.clear();
    bitArray.push_back(true);
    EXPECT_EQ(bitArray[0], true);
}

TEST(functionsAffectingBits, operatorBitwiseConjuction) {
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
    bitArray1 &= bitArray2;
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(bitArray1[i], false);
    }
    bitArray1.resize(size*2);
    for (int i = 0; i < size*2; ++i) {
        if (i % 2 == 0)
            bitArray1.set(i);
    }
    bitArray1.set(size + size/2);
    bitArray1 &= bitArray2;
    for (int i = 0; i < size * 2; ++i) {
        if (i == size + size/2) {
            EXPECT_EQ(bitArray1[i], true);
            continue;
        }
        if (i % 2 == 0)
            EXPECT_EQ(bitArray1[i], true);
        else
            EXPECT_EQ(bitArray1[i], false);
    }
}

TEST(functionsAffectingBits, operatorBitwiseDisjuction) {
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
    bitArray1 |= bitArray2;
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(bitArray1[i], true);
    }
    bitArray1.reset();
    bitArray1.resize(size*2);
    for (int i = 0; i < size*2; ++i) {
        if (i % 2 == 0)
            bitArray1.set(i);
    }
    bitArray1.set(size + size/2);
    bitArray1 |= bitArray2;
    for (int i = 0; i < size * 2; ++i) {
        if (i == size + size/2) {
            EXPECT_EQ(bitArray1[i], true);
            continue;
        }
        if (i % 2 == 0)
            EXPECT_EQ(bitArray1[i], true);
        else
            EXPECT_EQ(bitArray1[i], false);
    }
}

TEST(functionsAffectingBits, operatorBitwiseXor) {
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
    bitArray1 ^= bitArray2;
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(bitArray1[i], true);
    }
    bitArray1.reset();
    bitArray1.resize(size*2);
    for (int i = 0; i < size*2; ++i) {
        if (i % 2 == 0)
            bitArray1.set(i);
    }
    bitArray1.set(size + size/2);
    bitArray1 ^= bitArray2;
    for (int i = 0; i < size * 2; ++i) {
        if (i == size + size/2) {
            EXPECT_EQ(bitArray1[i], true);
            continue;
        }
        if (i % 2 == 0)
            EXPECT_EQ(bitArray1[i], true);
        else
            EXPECT_EQ(bitArray1[i], false);
    }
    bitArray1 = bitArray2;
    bitArray1 ^= bitArray2;
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(bitArray1[i], false);
    }
}

TEST(functionsAffectingBits, operatorBitwiseLeftShift) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    for (int i = 0; i < size; ++i) {
        if (i % 2 != 0) {
            bitArray.set(i);
        }
    }
    for (int shift = 1; shift <= size; ++shift) {
        bitArray <<= 1;
        for (int i = 0; i < size; ++i) {
            if(i >= size - shift) {
                EXPECT_EQ(bitArray[i], false);
                continue;
            }
            if (i % 2 == 0 && shift % 2 == 1) {
                EXPECT_EQ(bitArray[i], true);
            }
            else if (i % 2 == 0 && shift % 2 == 0) {
                EXPECT_EQ(bitArray[i], false);
            }
        }
    }
    bitArray.reset();
    for (int i = 0; i < size; ++i) {
        bitArray.set(i);
    }
    bitArray <<= 0;
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(bitArray[i], true);
    }
}
