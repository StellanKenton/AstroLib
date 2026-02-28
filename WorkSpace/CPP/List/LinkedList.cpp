#include "LinkedList.hpp"

// ============================================================================
// 旧版本实现
// ============================================================================
namespace OldVersion {
    Node::Node(int val) : data(val), next(nullptr) {}
    
    Node::~Node() {
        std::cout << "  [旧版本] 析构节点: " << data << std::endl;
        delete next;  // 递归删除下一个节点
    }
    
    LinkedList::LinkedList() : head(nullptr) {}
    
    LinkedList::~LinkedList() {
        std::cout << "[旧版本] 开始销毁链表..." << std::endl;
        delete head;  // 手动删除
    }
    
    void LinkedList::push_front(int val) {
        Node* newNode = new Node(val);  // 使用 new
        newNode->next = head;
        head = newNode;
    }
    
    void LinkedList::print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
}

// ============================================================================
// 新版本实现
// ============================================================================
namespace ModernVersion {
    Node::Node(int val) : data(val), next(nullptr) {}
    
    Node::~Node() {
        std::cout << "  [新版本] 析构节点: " << data << std::endl;
        // 不需要手动 delete，unique_ptr 自动管理
    }
    
    LinkedList::LinkedList() : head(nullptr) {}
    
    LinkedList::~LinkedList() {
        std::cout << "[新版本] 开始销毁链表..." << std::endl;
        // unique_ptr 自动释放，无需手动 delete
    }
    
    void LinkedList::push_front(int val) {
        // 使用 std::make_unique（C++14）创建节点
        auto newNode = std::make_unique<Node>(val);
        
        // 使用移动语义转移所有权
        newNode->next = std::move(head);
        head = std::move(newNode);
    }
    
    void LinkedList::print() const {
        Node* current = head.get();  // 获取原始指针用于遍历
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next.get();
        }
        std::cout << "nullptr" << std::endl;
    }
    
    std::unique_ptr<Node> LinkedList::pop_front() {
        if (!head) return nullptr;
        
        auto oldHead = std::move(head);  // 转移所有权
        head = std::move(oldHead->next);
        return oldHead;  // 返回被移除的节点
    }
}

