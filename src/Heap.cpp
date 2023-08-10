#include "Heap.hpp"

int Heap::size() { return this->array.size(); }

bool Heap::empty() { return this->size() == 0; }

void Heap::push(pair<string, int> item) {
    this->array.push_back(item);
    this->heapify_up(size() - 1);
}

pair<string, int> Heap::top() { return this->array[0]; }

void Heap::pop() {
    this->array[0] = this->array.back();
    this->array.pop_back();

    heapify_down(0);
}

void Heap::heapify_down(int index) {
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;

    int smaller = index;

    if (left < size() && this->array[left].second < this->array[index].second) {
        smaller = left;
    }

    if (right < size() &&
        this->array[right].second < this->array[left].second) {
        smaller = right;
    }

    if (smaller != index) {
        swap(this->array[smaller], this->array[index]);
        heapify_down(smaller);
    }
}

void Heap::heapify_up(int index) {
    int parent = (index - 1) / 2;

    if (parent < 0) return;

    if (parent != index && array[parent].second > array[index].second) {
        swap(array[parent], array[index]);
        heapify_up(parent);
    }

    return;
}
