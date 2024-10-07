#pragma once

#include <iostream>

const unsigned int FIRST_BYTE = 0x80000000;
const unsigned int TRUE_BLOCK = 0xffffffff;
const unsigned int FALSE_BLOCK = 0;
const int BITS_COUNT = sizeof(int) * 8;

class Block {
public:
    Block* next;
    unsigned int value;
    unsigned int lastIndex;
    explicit Block(unsigned int data);
    Block& operator=(bool value);
    operator bool() const;
};

class BitArray
{
private:
    // Points on bit array first 8 elements (unsigned int).
    Block* basePtr{};

    // Points on bit array last 8 elements (unsigned int).
    Block* endPtr{};

    // The bits number stored in bit array.
    int numBits{};

    // Alignment of the number of bits to a number divisible by 8.
    static int alignBits(int numBits) ;

    // Gets bit mask: true bit set in position in zero unsigned int.
    static unsigned int getTrueMask(int position) ;

    // Gets bit mask: zero bit set in position in true unsigned int.
    unsigned int getFalseMask(int position) const;

    // Gets block on the position in bit array.
    Block* getBlock(int position) const;

    // Logarithmic positive pow function.
    unsigned int logPow(int num, int pow) const;
public:
    // Basic BitArray constructor.
    BitArray();

    // Basic BitArray destructor.
    ~BitArray();

    // Constructs a bit array storing a specified number of bits.
    explicit BitArray(int numBits, unsigned long value = 0);

    // Constructs new bit array based on b bit array. New memory is allocated.
    BitArray(const BitArray& b);

    // Swaps values between two bit arrays. If the sizes are not equal, swaps only the lesser part.
    void swap(BitArray& b);

    // Assigns one bit array to another.
    BitArray& operator=(const BitArray& b);

    // Changes the size of the array. In case of expansion, new elements
    // are initialized with the value = value.
    void resize(int numBits, bool value = false);

    // Clears array.
    void clear();

    // Adds new bit in the end of bit array. New memory
    // allocated if needed.
    void push_back(bool bit);

    // Bit operations. Works only for equal size bit arrays.
    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);

    // Bitwise shifts, filling with zeroes.
    BitArray& operator<<=(int n);
    BitArray& operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;

    // Sets the bit with index n to val (by default val is true).
    BitArray& set(int n, bool val = true);

    // Sets all the array true.
    BitArray& set();

    // Sets the bit with index n to false.
    BitArray& reset(int n);

    // Sets all the array false.
    BitArray& reset();

    // True, if bit array consists true bit.
    bool any() const;

    // True, if all bit array bits are false.
    bool none() const;

    // Bit inversion.
    BitArray operator~() const;

    // Count true bits amount.
    int count() const;

    // Returns a reference to a bit value at the position i.
    Block& operator[](int i);

    // Returns a bit value at the position i and does not edit anything.
    bool operator[](int i) const;

    // Returns bit array size.
    int size() const;

    // Returns true if bit array is empty else return false.
    bool empty() const;

    // Returns string made of bits.
    std::string to_string() const;

    // Counts blocks amount.
    int getBlockAmount() const;
};

bool operator==(const BitArray& a, const BitArray& b);
bool operator!=(const BitArray& a, const BitArray& b);

BitArray operator&(const BitArray& b1, const BitArray& b2);
BitArray operator|(const BitArray& b1, const BitArray& b2);
BitArray operator^(const BitArray& b1, const BitArray& b2);
