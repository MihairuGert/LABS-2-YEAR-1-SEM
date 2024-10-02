#include "BitArray.h"

Block::Block(unsigned int value) {
    this->value = value;
    lastIndex = 0;
    next = nullptr;
}

Block& Block::operator=(bool value) {
    if (value) {
        this->value |= (1 << (bitsCount - lastIndex % bitsCount - 1));
    }
    else {
        this->value &= ~(1 << (bitsCount - lastIndex % bitsCount - 1));
    }
    return *this;
}

Block::operator bool() const {
    return (this->value & (1 << (bitsCount - lastIndex % bitsCount - 1))) != 0;
}

BitArray::BitArray() {
    basePtr = endPtr = nullptr;
    numBits = 0;
}

BitArray::~BitArray() {
    clear();
}

BitArray::BitArray(int numBits, unsigned long value) {
    this->numBits = -1;
    basePtr = endPtr = nullptr;
    resize(numBits, value);
}

BitArray::BitArray(const BitArray& b) {
    *this = BitArray(b.numBits, false);
    Block* curPtrBitArray = (*this).basePtr;
    Block* curPtrBitArrayToCopy = b.basePtr;
    while (curPtrBitArrayToCopy) {
        curPtrBitArray->value = curPtrBitArrayToCopy->value;
        curPtrBitArray = curPtrBitArray->next;
        curPtrBitArrayToCopy = curPtrBitArrayToCopy->next;
    }
}

void BitArray::swap(BitArray& b) {
    int size = (*this).size() <= b.size() ? (*this).size() : b.size();
    for (int i = 0; i < size; i++) {
        bool a = b[i];
        b.set(i, (*this)[i]);
        set(i, a);
    }
}

BitArray& BitArray::operator=(const BitArray& b) {
    int size = b.size();
    resize(size);
    for (int i = 0; i < size; i++) {
        set(i, b[i]);
    }
    return (*this);
}

void BitArray::resize(int numBits, bool value) {
    // Check if bits amount is the same.
    if (numBits == this->numBits)
        return;
    // Check if we should not change bit array memory blocks.
    int numBytesDifference = numBits - this->numBits;
    if (numBytesDifference > -bitsCount && numBytesDifference < bitsCount && this->numBits > 0) {
        this->numBits = numBits;
        return;
    }
    // Check if we should delete bit array memory blocks.
    if (numBits < this->numBits) {
        Block* blocksToDelete = basePtr;
        Block* prev = blocksToDelete;
        for (int i = 0; i < alignBits(numBits) / bitsCount; i++) {
            prev = blocksToDelete;
            blocksToDelete = blocksToDelete->next;
        }
        endPtr = prev;
        endPtr->next = nullptr;
        do {
            Block* blockToDelete = blocksToDelete;
            blocksToDelete = blocksToDelete->next;
            delete(blockToDelete);
        } while (blocksToDelete);
        this->numBits = numBits;
        return;
    }
    // Check for value input.
    unsigned int byteValue;
    if (!value)
        byteValue = FALSE_BLOCK;
    else
        byteValue = TRUE_BLOCK;
    // Add more bit array memory blocks.
    int i = 0;
    if (!basePtr) {
        basePtr = new Block(byteValue);
        endPtr = basePtr;
        i++;
    }
    for (; i < alignBits(numBits) / bitsCount - alignBits(this->numBits) / bitsCount; i++) {
        auto* block = new Block(byteValue);
        endPtr->next = block;
        endPtr = block;
    }
    this->numBits = numBits;
}

void BitArray::clear() {
    resize(0);
}

void BitArray::push_back(bool bit) {
    int numBitsCopy = numBits;
    resize(numBits + 1);
    set(numBitsCopy, bit);
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (size() != b.size() || b.empty() || empty()) {
        return *this;
    }
    for (int i = 0; i < b.size(); i++) {
        set(i, (*this)[i] && b[i]);
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (size() != b.size() || b.empty() || empty()) {
        return *this;
    }
    for (int i = 0; i < b.size(); i++) {
        set(i, (*this)[i] || b[i]);
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (size() != b.size() || b.empty() || empty()) {
        return *this;
    }
    for (int i = 0; i < b.size(); i++) {
        set(i, (*this)[i] ^ b[i]);
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    if (n == 0 || (*this).empty()) {
        return *this;
    }
    if (n < 0) {
        return (*this) >>= (-1) * n;
    }
    n %= numBits;
    for (int i = n; i < numBits; i++) {
        set(i - n, (*this)[i]);
        set(i, false);
    }
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n == 0 || (*this).empty()) {
        return *this;
    }
    if (n < 0) {
        return (*this) <<= (-1) * n;
    }
    n %= numBits;
    for (int i = numBits - n; i > 0; i--) {
        set(i + n, (*this)[i]);
        set(i, false);
    }
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray bitArray = BitArray(*this);
    bitArray <<= n;
    return bitArray;
}

BitArray BitArray::operator>>(int n) const {
    BitArray bitArray = BitArray(*this);
    bitArray >>= n;
    return bitArray;
}

BitArray& BitArray::set(int n, bool val) {
    if (n < 0 || n >= numBits) {
        return *this;
    }
    int positionInBitArray = n / bitsCount;
    if (val) {
        (*getBlock(positionInBitArray)).value = (*getBlock(positionInBitArray)).value | getTrueMask(n % bitsCount);
    }
    else {
        (*getBlock(positionInBitArray)).value = (*getBlock(positionInBitArray)).value & getFalseMask(n % bitsCount);
    }
    getBlock(positionInBitArray)->lastIndex = n % 8;
    return *this;
}

BitArray& BitArray::set() {
    Block* positionPtr = basePtr;
    while(positionPtr) {
        positionPtr->value = TRUE_BLOCK;
        positionPtr = positionPtr->next;
    }
    return *this;
}

BitArray& BitArray::reset(int n) {
    set(n, false);
    return *this;
}

BitArray& BitArray::reset() {
    Block* positionPtr = basePtr;
    while (positionPtr) {
        positionPtr->value = FALSE_BLOCK;
        positionPtr = positionPtr->next;
    }
    return *this;
}

bool BitArray::any() const {
    bool flag = false;
    for (int i = 0; i < numBits; i++) {
        flag = (*this)[i];
        if (flag) {
            break;
        }
    }
    return flag;
}

bool BitArray::none() const {
    return !any();
}

BitArray BitArray::operator~() const {
    BitArray bitArray = BitArray(*this);
    for (int i = 0; i < bitArray.size(); i++) {
        if (bitArray[i]) {
            bitArray.set(i, false);
        }
        else {
            bitArray.set(i, true);
        }
    }
    return bitArray;
}

int BitArray::count() const {
    int res = 0;
    for (int i = 0; i < numBits; i++) {
        if ((*this)[i]) {
            res++;
        }
    }
    return res;
}

Block& BitArray::operator[](int i) const {
    if (i < 0 || i >= numBits) {
        return *getBlock(0);
    }
    Block* block = getBlock(i / bitsCount);
    block->lastIndex = i;
    return *block;
}

int BitArray::size() const {
    return numBits;
}

bool BitArray::empty() const {
    return numBits == 0;
}

std::string BitArray::to_string() const {
    std::string res;
    for (int i = 0; i < numBits; i++) {
        int ind = (*this)[i] ? 1 : 0;
        res.push_back(ind + '0');
    }
    return res;
}

int BitArray::alignBits(int numBits) {
    if (numBits <= 0) {
        return 0;
    }
    if (numBits % bitsCount != 0) {
        numBits += (bitsCount - numBits % bitsCount);
    }
    return numBits;
}

unsigned int BitArray::getTrueMask(int position) {
    unsigned int mask = FIRST_BYTE;
    return mask >> position;
}

unsigned int BitArray::getFalseMask(int position) const {
    return TRUE_BLOCK - logPow(2, bitsCount - 1 - position);
}

Block* BitArray::getBlock(int position) const{
    Block* positionPtr = basePtr;
    for (int i = 0; i < position; i++) {
        positionPtr = positionPtr->next;
    }
    return positionPtr;
}

unsigned int BitArray::logPow(int num, int pow) const {
    if (pow == 0) {
        return 1;
    }
    if (pow == 1) {
        return num;
    }
    if (pow % 2 == 0) {
        return logPow(num * num, pow / 2);
    }
    return logPow(num, pow - 1) * num;
}

bool operator==(const BitArray& a, const BitArray& b) {
    int sizeA = a.size();
    int sizeB = b.size();
    if (sizeA != sizeB) {
        return false;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray bitArray = BitArray(b1);
    bitArray &= b2;
    return bitArray;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray bitArray = BitArray(b1);
    bitArray |= b2;
    return bitArray;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray bitArray = BitArray(b1);
    bitArray ^= b2;
    return bitArray;
}
