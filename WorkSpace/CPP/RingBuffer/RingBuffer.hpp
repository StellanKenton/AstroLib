#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <stdexcept>
#include <cstddef>
#include <memory>
#include <optional>
#include <vector>

template <typename T>
class RingBuffer {
private:
    std::unique_ptr<T[]> buffer;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t count;

public:
    // 构造函数
    explicit RingBuffer(size_t size);
    
    // 默认析构函数（智能指针自动管理内存）
    ~RingBuffer() = default;
    
    // 禁用拷贝构造和赋值
    RingBuffer(const RingBuffer&) = delete;
    RingBuffer& operator=(const RingBuffer&) = delete;
    
    // 移动构造和赋值（使用默认实现）
    RingBuffer(RingBuffer&& other) noexcept = default;
    RingBuffer& operator=(RingBuffer&& other) noexcept = default;
    
    // 核心操作（返回 bool）
    bool push(const T& item);
    bool push(T&& item);  // 右值引用版本
    bool pop(T& item);
    bool peek(T& item) const;
    
    // 现代 C++ 风格操作（返回 optional）
    std::optional<T> pop();
    std::optional<T> peek() const;
    
    // 状态查询
    bool isEmpty() const noexcept;
    bool isFull() const noexcept;
    size_t size() const noexcept;
    size_t getCapacity() const noexcept;
    void clear() noexcept;
    
    // 批量操作
    size_t pushMultiple(const T* items, size_t num);
    size_t pushMultiple(const std::vector<T>& items);
    size_t popMultiple(T* items, size_t num);
    std::vector<T> popMultiple(size_t num);
    
    // 迭代器支持（只读）
    class Iterator {
    private:
        const RingBuffer* rb;
        size_t index;
        size_t position;
        
    public:
        Iterator(const RingBuffer* buffer, size_t pos);
        T& operator*() const;
        Iterator& operator++();
        bool operator!=(const Iterator& other) const;
    };
    
    Iterator begin() const;
    Iterator end() const;
};

#include "RingBuffer.cpp"

#endif // RINGBUFFER_HPP

