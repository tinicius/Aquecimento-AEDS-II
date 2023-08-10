#include "Heap.hpp"

int Heap::size() { return this->array.size(); }

bool Heap::empty() { return this->size() == 0; }

void Heap::push(pair<string, int> item) {
    this->array.push_back(item);
    this->heapify_down(0);
}

pair<string, int> Heap::top() { return this->array[0]; }

void Heap::pop() {
    this->array[0] = this->array.back();
    this->array.pop_back();

    this->heapify_down(0);
}

void Heap::heapify_down(int index) {
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;

    int smaller = index;

    if (left < size() && array[left].second < array[index].second) {
        smaller = left;
    }

    if (right < size() && array[right].second < array[smaller].second) {
        smaller = right;
    }

    if (smaller != index) {
        swap(array[index], array[smaller]);
        heapify_down(smaller);
    }
}
