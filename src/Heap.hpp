#ifndef HEAP_HPP
#define HEAP_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Heap {
   private:
    vector<pair<string, int>> array;
    void heapify_up(int index);
    void heapify_down(int index);

   public:
    int size();
    bool empty();
    void push(pair<string, int> item);
    pair<string, int> top();
    void pop();
};

#endif