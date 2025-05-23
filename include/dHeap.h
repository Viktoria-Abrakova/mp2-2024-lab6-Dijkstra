#pragma once
#include "myvector.h"
#include <stdexcept>
#include <algorithm>

template <typename T>
class DHeap {
private:
    myVector<T> data;
    int d;

    void validateD(int value) const {
        if (value < 2) throw std::invalid_argument("D must be ≥ 2");
    }

    int parent(int i) const { return (i - 1) / d; }
    int firstChild(int i) const { return d * i + 1; }

    void heapifyUp(int i) {
        while (i > 0 && data[i] < data[parent(i)]) {
            std::swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int minIndex = i;
        int first = firstChild(i);
        int last = std::min(first + d, static_cast<int>(data.size()));

        for (int j = first; j < last; ++j) {
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            std::swap(data[i], data[minIndex]);
            heapifyDown(minIndex);
        }
    }

public:
    explicit DHeap(int d) : d(d) { validateD(d); }

    void push(const T& value) {
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }

    const T& top() const {
        if (data.empty()) throw std::out_of_range("Heap is empty");
        return data[0];
    }

    void pop() {
        if (data.empty()) throw std::out_of_range("Heap is empty");
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) heapifyDown(0);
    }

    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }
    int getArity() const { return d; }

    void setArity(int newD) {
        validateD(newD);
        if (newD != d) {
            d = newD;
            for (int i = parent(data.size() - 1); i >= 0; --i) {
                heapifyDown(i);
            }
        }
    }
};