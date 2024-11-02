#include <random>
#include "gtest/gtest.h"
#include "BitArray.h"

TEST(constructors, basictBitArrayConstructor) {
    BitArray bitArray = BitArray();
    EXPECT_EQ(0, bitArray.size());
}

TEST(constructors, explicitBitArrayConstructor) {
    int size = 100;
    BitArray bitArray = BitArray(size, true);
    EXPECT_EQ(size, bitArray.size());
    bitArray.reset(size / 2);
    EXPECT_EQ(size - 1, bitArray.count());
}

TEST(constructors, copyBitArrayConstructor) {
    int size = 100;
    BitArray bitArray = BitArray(size, true);
    BitArray bitArray1 = BitArray(bitArray);
    EXPECT_EQ(size, bitArray1.size());
    bitArray1.reset(size / 2);
    EXPECT_EQ(size - 1, bitArray1.count());
    EXPECT_NE(bitArray1.count(), bitArray.count());
    bitArray1.clear();
    EXPECT_EQ(size, bitArray.size());
}

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
    bitArray.set();
    bitArray <<= 0;
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(bitArray[i], true);
    }
}

TEST(functionsAffectingBits, operatorBitwiseRightShift) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    for (int i = 0; i < size; ++i) {
        if (i % 2 != 0) {
            bitArray.set(i);
        }
    }
    for (int shift = 1; shift <= size; ++shift) {
        bitArray >>= 1;
        for (int i = 0; i < size; ++i) {
            if(i <= shift) {
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
    bitArray.set();
    bitArray <<= 0;
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(bitArray[i], true);
    }
}

TEST(functionsAffectingBits, set) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    bitArray.set(0);
    EXPECT_EQ(bitArray.to_string()[0], '1');
    bitArray.set(0, false);
    EXPECT_EQ(bitArray.to_string()[0], '0');
    BitArray bitArrayCopy = bitArray;
    EXPECT_NO_THROW(bitArray.set(size + 1));
    EXPECT_TRUE(bitArray == bitArrayCopy);
    EXPECT_NO_THROW(bitArray.set(-1));
    EXPECT_TRUE(bitArray == bitArrayCopy);
}

TEST(functionsAffectingBits, setAll) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    bitArray.set();
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(bitArray[i], true);
    }
}

TEST(functionsAffectingBits, reset) {
    int size = 100;
    BitArray bitArray = BitArray(size, true);
    bitArray.reset(0);
    EXPECT_EQ(bitArray.to_string()[0], '0');
    BitArray bitArrayCopy = bitArray;
    EXPECT_NO_THROW(bitArray.reset(size + 1));
    EXPECT_TRUE(bitArray == bitArrayCopy);
    EXPECT_NO_THROW(bitArray.reset(-1));
    EXPECT_TRUE(bitArray == bitArrayCopy);
}

TEST(functionsAffectingBits, resetAll) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    bitArray.reset();
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(bitArray[i], false);
    }
}

TEST(functionsGettingInfo, any) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    bitArray.set(size / 2);
    EXPECT_TRUE(bitArray.any());
    bitArray.reset(size / 2);
    EXPECT_FALSE(bitArray.any());
}

TEST(functionsGettingInfo, none) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    bitArray.set(size / 2);
    EXPECT_FALSE(bitArray.none());
    bitArray.reset(size / 2);
    EXPECT_TRUE(bitArray.none());
}

TEST(functionsAffectingBits, opertorBitwiseInversion) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    for (int i = 0; i < size; ++i) {
        if (i % 2 == 0) {
            bitArray.set(i);
        }
    }
    BitArray bitArrayInv = ~bitArray;
    for (int i = 0; i < size; ++i) {
        EXPECT_NE(bitArray[i], bitArrayInv[i]);
    }
}

TEST(functionsGettingInfo, count) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,size - 1);
    int randTrueBits = dist(gen);
    int uniqueTrueBits = 0;
    for (int i = 0; i < randTrueBits; ++i) {
        int pos = dist(gen);
        if (!bitArray[pos]) {
            bitArray[pos] = true;
            uniqueTrueBits++;
        }
    }
    EXPECT_EQ(uniqueTrueBits, bitArray.count());
}

TEST(functionsAffectingBits, operatorSubscript) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    bitArray[0] = true;
    EXPECT_EQ(bitArray.to_string()[0], '1');
    bitArray[0] = false;
    EXPECT_EQ(bitArray.to_string()[0], '0');
    bitArray[size / 2] = true;
    EXPECT_TRUE(bitArray[size / 2] == true);
    EXPECT_TRUE(bitArray[size / 2 - 1] == false);
    EXPECT_TRUE(bitArray[size / 2 + 1] == false);
}

TEST(functionsAffectingBits, operatorSubscriptOverflow) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    bitArray[size] = true;
    EXPECT_EQ(bitArray.to_string()[size], '1');
    EXPECT_EQ(bitArray.getBlockAmount(), size / BITS_COUNT + 1);
}

TEST(functionsGettingInfo, size) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    EXPECT_EQ(bitArray.size(), size);
    bitArray.resize(size / 2);
    EXPECT_EQ(bitArray.size(), size / 2);
}

TEST(functionsGettingInfo, empty) {
    int size = 0;
    BitArray bitArray = BitArray(size);
    EXPECT_TRUE(bitArray.empty());
    bitArray.resize(size + 100);
    EXPECT_FALSE(bitArray.empty());
}

TEST(functionsGettingInfo, to_string) {
    int size = 100;
    BitArray bitArray = BitArray(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,size - 1);
    int randTrueBits = dist(gen);
    int uniqueTrueBits = 0;
    for (int i = 0; i < randTrueBits; ++i) {
        int pos = dist(gen);
        if (!bitArray[pos]) {
            bitArray[pos] = true;
            uniqueTrueBits++;
        }
    }
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (bitArray.to_string()[i] - '0') {
            count++;
        }
    }
    EXPECT_EQ(uniqueTrueBits, count);
    bitArray.clear();
    EXPECT_TRUE(bitArray.to_string().empty());
}

TEST(functionsGettingInfo, operatorTwoBitArraysEQ) {
    int size = 100;
    BitArray bitArray1 = BitArray(size);
    BitArray bitArray2 = BitArray(size);
    EXPECT_TRUE(bitArray1 == bitArray2);
    bitArray1[size / 2] = true;
    EXPECT_FALSE(bitArray1 == bitArray2);
    bitArray1 = bitArray2;
    bitArray1.resize(size*2);
    EXPECT_FALSE(bitArray1 == bitArray2);
}

TEST(functionsGettingInfo, operatorTwoBitArraysNE) {
    int size = 100;
    BitArray bitArray1 = BitArray(size);
    BitArray bitArray2 = BitArray(size);
    EXPECT_FALSE(bitArray1 != bitArray2);
    bitArray1[size / 2] = true;
    EXPECT_TRUE(bitArray1 != bitArray2);
    bitArray1 = bitArray2;
    bitArray1.resize(size*2);
    EXPECT_TRUE(bitArray1 != bitArray2);
}

// <--------------> INFO <-------------->
// &, |, ^ two bits array functions are implemented
// through &=, |=, ^= functions respectively.
// Those functions have already been tested.
// <--------------> **** <-------------->
