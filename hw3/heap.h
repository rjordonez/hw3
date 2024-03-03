#ifndef HEAP_H
#define HEAP_H

#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T>>
class Heap {
public:
    Heap(int m = 2, PComparator c = PComparator()) : arity(m), comp(c) {
        if (m < 2) {
            throw std::invalid_argument("Heap arity must be at least 2");
        }
    }

    ~Heap() = default;

    void push(const T& item) {
        data.push_back(item);
        heapifyUp(data.size() - 1);
    }

    T const & top() const {
        if (empty()) {
            throw std::underflow_error("Heap is empty");
        }
        return data.front();
    }

    void pop() {
        if (empty()) {
            throw std::underflow_error("Heap is empty");
        }
        std::swap(data.front(), data.back());
        data.pop_back();
        heapifyDown(0);
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

private:
    std::vector<T> data;
    int arity;
    PComparator comp;

    void heapifyUp(int index) {
        while (index > 0 && comp(data[index], data[parent(index)])) {
            std::swap(data[index], data[parent(index)]);
            index = parent(index);
        }
    }


    int parent(int index) const {
        return (index - 1) / arity;
    }
    void heapifyDown(size_t index) {  // change 'int' to 'size_t'
    size_t childIndex = firstChild(index);
    while (childIndex < data.size()) {
        size_t minChild = minChildIndex(index);  // change 'int' to 'size_t'
        if (!comp(data[minChild], data[index])) {
            break;
        }
        std::swap(data[index], data[minChild]);
        index = minChild;
        childIndex = firstChild(index);
    }
}

size_t firstChild(size_t index) const {  // change 'int' to 'size_t'
    return index * arity + 1;
}

size_t minChildIndex(size_t index) const {  // change 'int' to 'size_t'
    size_t first = firstChild(index);
    size_t last = std::min(first + arity, data.size());
    size_t minChild = first;
    for (size_t i = first + 1; i < last; ++i) {  // change 'int' to 'size_t'
        if (comp(data[i], data[minChild])) {
            minChild = i;
        }
    }
    return minChild;
}


};


#endif
