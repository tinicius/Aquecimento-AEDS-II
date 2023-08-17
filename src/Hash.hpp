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
    size_t hash(string key);

   public:
    Hash();
    virtual ~Hash();
    vector<string> keys;
    void insert(string key);
    bool find(string key);
    pair<string, int> at(string key);
};

#endif