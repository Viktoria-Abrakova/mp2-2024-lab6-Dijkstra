#pragma once
#include <algorithm>
#include <stdexcept>

template <typename T>
class myVector {
private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

public:
    myVector() = default;

    explicit myVector(size_t size, const T& value = T())
        : data_(new T[size]), size_(size), capacity_(size) {
        for (size_t i = 0; i < size; ++i) {
            data_[i] = value;
        }
    }

    ~myVector() { delete[] data_; }

    myVector(const myVector& other)
        : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    myVector(myVector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }

    myVector& operator=(const myVector& other) {
        if (this != &other) {
            myVector tmp(other);
            swap(tmp);
        }
        return *this;
    }

    myVector& operator=(myVector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        return *this;
    }

    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }

    T& back() {
        if (size_ == 0) throw std::out_of_range("Vector is empty");
        return data_[size_ - 1];
    }

    const T& back() const {
        if (size_ == 0) throw std::out_of_range("Vector is empty");
        return data_[size_ - 1];
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ ? capacity_ * 2 : 1);
        }
        data_[size_++] = value;
    }

    void pop_back() {
        if (size_ == 0) throw std::out_of_range("Vector is empty");
        --size_;
    }

    void resize(size_t newSize, const T& value = T()) {
        if (newSize > capacity_) {
            reserve(newSize);
        }
        if (newSize > size_) {
            for (size_t i = size_; i < newSize; ++i) {
                data_[i] = value;
            }
        }
        size_ = newSize;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) return;

        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    void clear() noexcept { size_ = 0; }

    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return capacity_; }
    bool empty() const noexcept { return size_ == 0; }

    void swap(myVector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
};