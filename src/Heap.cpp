#include "Heap.hpp"

int Heap::size() { return this->array.size(); }

bool Heap::empty() { return this->size() == 0; }

void Heap::push(pair<string, int> item) {
    this->array.push_back(item);
    this->heapify_up(size() - 1);
}

pair<string, int> Heap::top() { return this->array[0]; }

void Heap::pop() {
    if (this->array.size() == 0) return;

    this->array[0] = this->array.back();
    this->array.pop_back();

    heapify_down(0);
}

void Heap::heapify_down(int index) {
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;

    int smaller = index;

    int childLeft = this->array[left].second;
    int childRight = this->array[right].second;

    int indexFreq = this->array[index].second;

    if (left < this->size() && childLeft < indexFreq) {
        smaller = left;
    }

    if (right < this->size() && childRight < childLeft) {
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

    int parentFreq = array[parent].second;
    int indexFreq = array[index].second;

    if (parent != index && parentFreq > indexFreq) {
        swap(array[parent], array[index]);
        heapify_up(parent);
    }
}

void Heap::showHeapContainer() {
    cout << "Heap: \n";

    for (int i = 0; i < this->array.size(); i++)
        cout << this->array[i].first << "\t";

    cout << endl;
}