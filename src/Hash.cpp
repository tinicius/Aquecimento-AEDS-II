#include "Hash.hpp"

#define dbg(x) cout << #x << " = " << x << endl

#define RESERVE_VALUE 100000

Hash::Hash() {
    this->array.reserve(RESERVE_VALUE);
    this->containerFill.reserve(RESERVE_VALUE);
}

Hash::~Hash() {
    // clear?
}

size_t sumDigits(string key) {
    size_t keySum = 0;
    for (int i = 0; i < key.size(); i++) keySum += (size_t)key[i];

    return keySum;
}

size_t getDigitsInArraySize(size_t arraySize) {
    if (arraySize == 0) arraySize = RESERVE_VALUE;

    size_t digitsInArraySize = 1;

    while (arraySize / 10 > 0) {
        arraySize /= 10;
        digitsInArraySize++;
    }

    return digitsInArraySize;
}

size_t getDigitsInSquare(size_t square) {
    size_t squareDigits = 1;

    while (square / 10 > 0) {
        square /= 10;
        squareDigits++;
    }

    return squareDigits;
}

size_t getSquareMiddle(size_t squareDigits, size_t digitsInArraySize,
                       size_t square) {
    size_t removeCount = 0;

    if (squareDigits > digitsInArraySize)
        removeCount = (squareDigits - digitsInArraySize) / 2;
    else
        removeCount = (digitsInArraySize - squareDigits) / 2;

    for (size_t i = 0; i < removeCount; i++) {
        square /= 10;
    }

    size_t mult = 1;

    size_t index = 0;

    for (size_t i = 0; i < digitsInArraySize - 1; i++) {
        size_t mod = square % 10;
        square /= 10;

        index += mod * mult;
        mult *= 10;
    }

    return index;
}

size_t Hash::hash(string key) {
    size_t keySum = sumDigits(key);
    size_t square = keySum * keySum;

    size_t digitsInArraySize = getDigitsInArraySize(this->array.size());

    size_t squareDigits = getDigitsInSquare(square);

    size_t middle = getSquareMiddle(squareDigits, digitsInArraySize, square);

    return middle;
};

void Hash::insert(string key) {

    // system("clear");

    if (this->array.size() >= RESERVE_VALUE) {
        this->array.reserve(this->array.size() + RESERVE_VALUE);
    }

    size_t index = this->hash(key);

    // dbg(index);

    // dbg(this->array[index].first);

    while (
        this->containerFill[index] != 0 ||
        (this->containerFill[index] == 1 && this->array[index].first == key)) {
        // cout << index<< " ";
        index += 1;

        if (index == RESERVE_VALUE) index = 0;
    }

    this->array[index].first = key;
    this->array[index].second++;

    this->containerFill[index] = 1;
    entries.push_back(key);
}

pair<string, int> Hash::at(string key) {
    size_t index = this->hash(key);

    while (this->array[index].first != key) {
        index += 1;

        if (index == RESERVE_VALUE) index = 0;
    }

    return this->array[index];
}