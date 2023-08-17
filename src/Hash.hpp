#ifndef HASH_HPP
#define HASH_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Hash {
   private:
    vector<pair<string, int>> array;
    vector<bool> containerFill;
    // size_t hash(string key);

   public:
    Hash();
    virtual ~Hash();
    void insert(string key, int value);
    pair<string, int> at(string key);

    size_t hash(string key);
};

#endif