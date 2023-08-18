#include "Hash.hpp"

#define dbg(x) cout << #x << " = " << x << endl

Hash::Hash() {
    this->bucketsNumber = 100;
    this->array.resize(bucketsNumber);
}

Hash::~Hash() {
    // clear?
}

size_t sumDigits(string key) {
    size_t keySum = 0;
    for (size_t i = 0; i < key.size(); i++) keySum += (size_t)key[i];

    return keySum;
}

size_t getDigitsInArraySize(size_t arraySize) {
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

void Hash::rehash() {
    vector<pair<string, int>> actual;

    for (auto& a : array) {
        if (a.second != 0) actual.push_back(a);
    }

    this->bucketsNumber *= 100;

    this->array.resize(bucketsNumber);

    for (auto& a : array) {
        a.first = "";
        a.second = 0;
    }

    keys.clear();

    for (auto& k : actual) {
        this->insert(k.first, k.second);
    }
}

void Hash::insert(string key, int value) {
    size_t index = this->hash(key);

    while (array[index].second != 0) {
        if (array[index].first == key) break;

        index += 1;

        if (index == array.size()) index = 0;
    }

    auto& container = array[index];

    if (container.second == 0) {
        container.first = key;
        container.second = value;
        keys.push_back(key);
    } else {
        container.second++;
    }

    double loadFactor = (double)keys.size() / (double)array.size();
    // dbg(loadFactor);

    if (loadFactor >= 0.5) {
        cout << "rehash" << endl;
        this->rehash();
    }

    // dbg(keys.size());

    // if (keys.size() == bucketsNumber) {
    //     cout << "rehash" << endl;
    //     this->rehash();
    // }
}

bool Hash::find(string key) {
    size_t index = this->hash(key);

    while (this->array[index].second != 0) {
        if (this->array[index].first == key) return true;

        index += 1;

        if (index == this->array.size()) index = 0;
    }

    return false;
}

pair<string, int> Hash::at(string key) {
    size_t index = this->hash(key);

    while (this->array[index].second != 0) {
        if (this->array[index].first == key) break;

        index += 1;

        if (index == array.size()) index = 0;
    }

    return this->array[index];
}