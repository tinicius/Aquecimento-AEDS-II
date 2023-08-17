#ifndef HASH_HPP
#define HASH_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Hash {
   private:
       vector<bool> containerFill;

    // size_t hash(string key);

   public:
    vector<pair<string, int>> array;
    vector<string> entries;
    Hash();
    virtual ~Hash();
    void insert(string key);
    pair<string, int> at(string key);

    size_t hash(string key);
};

#endif