#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <memory>
#include <iostream>

// ============================================================================
// 旧版本：使用原始指针
// ============================================================================
namespace OldVersion {
    struct Node {
        int data;
        Node* next;
        
        Node(int val);
        ~Node();
    };
    
    class LinkedList {
    private:
        Node* head;
        
    public:
        LinkedList();
        ~LinkedList();
        
        // 禁止拷贝
        LinkedList(const LinkedList&) = delete;
        LinkedList& operator=(const LinkedList&) = delete;
        
        void push_front(int val);
        void print() const;
    };
}

// ============================================================================
// 新版本：使用 std::unique_ptr
// ============================================================================
namespace ModernVersion {
    struct Node {
        int data;
        std::unique_ptr<Node> next;
        
        Node(int val);
        ~Node();
    };
    
    class LinkedList {
    private:
        std::unique_ptr<Node> head;
        
    public:
        LinkedList();
        ~LinkedList();
        
        // 禁止拷贝
        LinkedList(const LinkedList&) = delete;
        LinkedList& operator=(const LinkedList&) = delete;
        
        // 支持移动语义
        LinkedList(LinkedList&&) = default;
        LinkedList& operator=(LinkedList&&) = default;
        
        void push_front(int val);
        void print() const;
        std::unique_ptr<Node> pop_front();
    };
}

#endif // LINKEDLIST_HPP

