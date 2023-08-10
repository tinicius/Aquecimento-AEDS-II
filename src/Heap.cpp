#include <Heap.hpp>

int Heap::size() { return this->array.size(); }

void Heap::push(pair<string, int> item) {
    this->array.push_back(item);
    this->heapify_down(this->size() - 1);
}

void Heap::show() {
    for (auto i : this->array) cout << i.first << " " << i.second << endl;
}

void Heap::heapify_down(int index) {
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;

    int largest = index;

    if (left < size() && array[left].second > array[index].second) {
        largest = left;
    }

    if (right < size() && array[right].second > array[largest].second) {
        largest = right;
    }

    if (largest != index) {
        swap(array[index], array[largest]);
        heapify_down(largest);
    }
}
