#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Heap {
   private:
    vector<pair<string, int>> array;
    void heapify_down(int index);

   public:
    int size();
    void push(pair<string, int> item);
    void show();
};