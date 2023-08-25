#include "Heap.hpp"

int Heap::size() { return array.size(); }

bool Heap::empty() { return size() == 0; }

void Heap::push(pair<string, int> item) {
    array.push_back(item);
    heapify_up(size() - 1);
}

pair<string, int> Heap::top() { return array[0]; }

void Heap::pop() {
    if (array.size() == 0) return;

    array[0] = array.back();
    array.pop_back();

    heapify_down(0);
}

void Heap::heapify_down(int index) {
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;

    int smallerIndex = index;

    int childLeftFreq = array[left].second;
    int childRightFreq = array[right].second;

    int parentFreq = array[index].second;

    if (left < size() && childLeftFreq < parentFreq) {
        smallerIndex = left;
    }

    if (right < size() && childRightFreq < array[smallerIndex].second) {
        smallerIndex = right;
    }

    if (smallerIndex != index) {
        swap(array[smallerIndex], array[index]);
        heapify_down(smallerIndex);
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

void Heap::showHeapArray() {
    cout << "Elementos na Heap: \n";

    for (size_t i = 0; i < array.size(); i++)
        cout << array[i].first << " " << array[i].second << endl;

    cout << endl;
}