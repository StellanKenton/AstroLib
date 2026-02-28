#ifndef RINGBUFFER_CPP
#define RINGBUFFER_CPP

#include "RingBuffer.hpp"
#include <algorithm>
#include <utility>

template <typename T>
RingBuffer<T>::RingBuffer(size_t size) 
    : buffer(std::make_unique<T[]>(size)), 
      capacity(size), head(0), tail(0), count(0) {
    if (size == 0) {
        throw std::invalid_argument("RingBuffer size must be greater than 0");
    }
}

template <typename T>
bool RingBuffer<T>::push(const T& item) {
    if (isFull()) {
        return false;
    }
    
    buffer[tail] = item;
    tail = (tail + 1) % capacity;
    ++count;
    return true;
}

template <typename T>
bool RingBuffer<T>::push(T&& item) {
    if (isFull()) {
        return false;
    }
    
    buffer[tail] = std::move(item);
    tail = (tail + 1) % capacity;
    ++count;
    return true;
}

template <typename T>
bool RingBuffer<T>::pop(T& item) {
    if (isEmpty()) {
        return false;
    }
    
    item = buffer[head];
    head = (head + 1) % capacity;
    --count;
    return true;
}

template <typename T>
bool RingBuffer<T>::peek(T& item) const {
    if (isEmpty()) {
        return false;
    }
    
    item = buffer[head];
    return true;
}

template <typename T>
std::optional<T> RingBuffer<T>::pop() {
    if (isEmpty()) {
        return std::nullopt;
    }
    
    T item = std::move(buffer[head]);
    head = (head + 1) % capacity;
    --count;
    return item;
}

template <typename T>
std::optional<T> RingBuffer<T>::peek() const {
    if (isEmpty()) {
        return std::nullopt;
    }
    
    return buffer[head];
}

template <typename T>
bool RingBuffer<T>::isEmpty() const noexcept {
    return count == 0;
}

template <typename T>
bool RingBuffer<T>::isFull() const noexcept {
    return count == capacity;
}

template <typename T>
size_t RingBuffer<T>::size() const noexcept {
    return count;
}

template <typename T>
size_t RingBuffer<T>::getCapacity() const noexcept {
    return capacity;
}

template <typename T>
void RingBuffer<T>::clear() noexcept {
    head = 0;
    tail = 0;
    count = 0;
}

template <typename T>
size_t RingBuffer<T>::pushMultiple(const T* items, size_t num) {
    size_t pushed = 0;
    for (size_t i = 0; i < num && !isFull(); ++i) {
        if (push(items[i])) {
            ++pushed;
        }
    }
    return pushed;
}

template <typename T>
size_t RingBuffer<T>::pushMultiple(const std::vector<T>& items) {
    return pushMultiple(items.data(), items.size());
}

template <typename T>
size_t RingBuffer<T>::popMultiple(T* items, size_t num) {
    size_t popped = 0;
    for (size_t i = 0; i < num && !isEmpty(); ++i) {
        if (pop(items[i])) {
            ++popped;
        }
    }
    return popped;
}

template <typename T>
std::vector<T> RingBuffer<T>::popMultiple(size_t num) {
    std::vector<T> result;
    result.reserve(std::min(num, count));
    
    for (size_t i = 0; i < num && !isEmpty(); ++i) {
        auto item = pop();
        if (item) {
            result.push_back(std::move(*item));
        }
    }
    
    return result;
}

// 迭代器实现
template <typename T>
RingBuffer<T>::Iterator::Iterator(const RingBuffer* buffer, size_t pos)
    : rb(buffer), position(pos) {
    index = (rb->head + position) % rb->capacity;
}

template <typename T>
T& RingBuffer<T>::Iterator::operator*() const {
    return rb->buffer[index];
}

template <typename T>
typename RingBuffer<T>::Iterator& RingBuffer<T>::Iterator::operator++() {
    ++position;
    index = (rb->head + position) % rb->capacity;
    return *this;
}

template <typename T>
bool RingBuffer<T>::Iterator::operator!=(const Iterator& other) const {
    return position != other.position;
}

template <typename T>
typename RingBuffer<T>::Iterator RingBuffer<T>::begin() const {
    return Iterator(this, 0);
}

template <typename T>
typename RingBuffer<T>::Iterator RingBuffer<T>::end() const {
    return Iterator(this, count);
}

#endif // RINGBUFFER_CPP

