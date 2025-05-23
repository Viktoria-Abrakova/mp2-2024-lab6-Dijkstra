#pragma once
#include "myvector.h"

template <typename T>
class Stack {
private:
    myVector<T> data_;

public:
    void push(const T& value) { data_.push_back(value); }
    void pop() { data_.pop_back(); }

    T& top() { return data_.back(); }
    const T& top() const { return data_.back(); }

    bool empty() const { return data_.empty(); }
    size_t size() const { return data_.size(); }
    void clear() { data_.clear(); }
};