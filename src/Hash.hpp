#ifndef HASH_HPP
#define HASH_HPP

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Hash {
   private:
    vector<pair<string, int>> array;
    size_t hash(string key);
    void rehash();

   public:
    Hash();
    virtual ~Hash();
    vector<string> keys;
    void insert(string key);
    void insert(string key, int value);
    bool find(string key);
    pair<string, int> at(string key);
};

#endif