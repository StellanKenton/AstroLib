#include "LinkedList.hpp"
#include <iostream>

// ============================================================================
// 演示和对比
// ============================================================================
void demonstrateOldVersion() {
    std::cout << "\n========== 旧版本：使用原始指针 ==========\n" << std::endl;
    
    OldVersion::LinkedList list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    
    std::cout << "链表内容: ";
    list.print();
    
    std::cout << "\n离开作用域，手动释放内存：" << std::endl;
}

void demonstrateModernVersion() {
    std::cout << "\n========== 新版本：使用 std::unique_ptr ==========\n" << std::endl;
    
    ModernVersion::LinkedList list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    
    std::cout << "链表内容: ";
    list.print();
    
    std::cout << "\n演示所有权转移（pop_front）：" << std::endl;
    auto node = list.pop_front();
    std::cout << "弹出的节点值: " << node->data << std::endl;
    std::cout << "剩余链表: ";
    list.print();
    
    std::cout << "\n离开作用域，自动释放内存：" << std::endl;
}

void demonstrateMoveSemantics() {
    std::cout << "\n========== 演示移动语义 ==========\n" << std::endl;
    
    ModernVersion::LinkedList list1;
    list1.push_front(30);
    list1.push_front(20);
    list1.push_front(10);
    
    std::cout << "list1: ";
    list1.print();
    
    // 移动构造
    ModernVersion::LinkedList list2 = std::move(list1);
    std::cout << "移动后 list2: ";
    list2.print();
    
    std::cout << "\n离开作用域：" << std::endl;
}

int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "  std::unique_ptr 演示：独占所有权的智能指针" << std::endl;
    std::cout << "==================================================" << std::endl;
    
    // 演示旧版本
    demonstrateOldVersion();
    
    // 演示新版本
    demonstrateModernVersion();
    
    // 演示移动语义
    demonstrateMoveSemantics();
    
    std::cout << "\n==================================================" << std::endl;
    std::cout << "关键知识点总结：" << std::endl;
    std::cout << "1. 零开销抽象：unique_ptr 没有运行时开销" << std::endl;
    std::cout << "2. 移动语义：使用 std::move 转移所有权" << std::endl;
    std::cout << "3. std::make_unique：安全创建 unique_ptr" << std::endl;
    std::cout << "4. 自动内存管理：无需手动 delete" << std::endl;
    std::cout << "5. 独占所有权：不可拷贝，只能移动" << std::endl;
    std::cout << "==================================================" << std::endl;
    
    return 0;
}
