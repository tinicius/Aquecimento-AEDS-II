#include "Hash.hpp"

Hash::Hash() { this->array.resize(100); }

Hash::~Hash() {}

size_t sumDigits(string key) {
    size_t keySum = 0;
    for (size_t i = 0; i < key.size(); i++) keySum += (size_t)key[i];

    return keySum;
}

size_t getSquareMiddle(size_t squareDigits, size_t keyDigits, size_t square) {
    size_t removeCount = 0;

    if (squareDigits > keyDigits)
        removeCount = squareDigits - keyDigits;
    else
        removeCount = keyDigits - squareDigits;

    for (size_t i = 0; i < removeCount / 2; i++) {
        square /= 10;
    }

    size_t mult = 1;

    size_t index = 0;

    for (size_t i = 0; i < keyDigits; i++) {
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

    size_t squareDigits = floor(log10(square) + 1);
    size_t keyDigits = floor(log10(array.size()) + 1);

    size_t middle = getSquareMiddle(squareDigits, keyDigits, square);

    if (middle >= this->array.size()) return middle % this->array.size();

    return middle;
};

void Hash::rehash() {
    vector<pair<string, int>> actual;

    for (auto& a : array) {
        if (a.second != 0) actual.push_back(a);
    }

    this->array.resize(array.size() * 100);

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

    if (loadFactor >= 0.75) {
        this->rehash();
    }
}

void Hash::insert(string key) {
    size_t index = this->hash(key);

    while (array[index].second != 0) {
        if (array[index].first == key) break;

        index += 1;

        if (index == array.size()) index = 0;
    }

    auto& container = array[index];

    if (container.second == 0) {
        container.first = key;
        container.second = 1;
        keys.push_back(key);
    } else {
        container.second++;
    }

    double loadFactor = (double)keys.size() / (double)array.size();

    if (loadFactor >= 0.5) {
        this->rehash();
    }
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