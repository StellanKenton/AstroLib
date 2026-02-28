#include "RingBuffer.hpp"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

void testBasicOperations() {
    cout << "=== 测试基本操作 ===" << endl;
    
    RingBuffer<int> rb(5);
    
    // 测试初始状态
    assert(rb.isEmpty());
    assert(!rb.isFull());
    assert(rb.size() == 0);
    assert(rb.getCapacity() == 5);
    cout << "✓ 初始化成功" << endl;
    
    // 测试 push
    assert(rb.push(10));
    assert(rb.push(20));
    assert(rb.push(30));
    assert(rb.size() == 3);
    cout << "✓ Push 操作成功" << endl;
    
    // 测试 peek
    int value;
    assert(rb.peek(value));
    assert(value == 10);
    assert(rb.size() == 3); // peek 不改变大小
    cout << "✓ Peek 操作成功，值为: " << value << endl;
    
    // 测试 pop
    assert(rb.pop(value));
    assert(value == 10);
    assert(rb.size() == 2);
    cout << "✓ Pop 操作成功，值为: " << value << endl;
    
    assert(rb.pop(value));
    assert(value == 20);
    cout << "✓ Pop 操作成功，值为: " << value << endl;
}

void testFullAndEmpty() {
    cout << "\n=== 测试满和空状态 ===" << endl;
    
    RingBuffer<int> rb(3);
    
    // 填满缓冲区
    assert(rb.push(1));
    assert(rb.push(2));
    assert(rb.push(3));
    assert(rb.isFull());
    assert(!rb.push(4)); // 应该失败
    cout << "✓ 缓冲区已满，无法继续 push" << endl;
    
    // 清空缓冲区
    int value;
    assert(rb.pop(value));
    assert(rb.pop(value));
    assert(rb.pop(value));
    assert(rb.isEmpty());
    assert(!rb.pop(value)); // 应该失败
    assert(!rb.peek(value)); // 应该失败
    cout << "✓ 缓冲区已空，无法 pop 或 peek" << endl;
}

void testCircularBehavior() {
    cout << "\n=== 测试环形行为 ===" << endl;
    
    RingBuffer<int> rb(3);
    
    // 填满
    rb.push(1);
    rb.push(2);
    rb.push(3);
    
    // 弹出一些
    int value;
    rb.pop(value);
    rb.pop(value);
    
    // 再次填充（测试环形）
    assert(rb.push(4));
    assert(rb.push(5));
    assert(rb.isFull());
    
    // 验证顺序
    assert(rb.pop(value) && value == 3);
    assert(rb.pop(value) && value == 4);
    assert(rb.pop(value) && value == 5);
    assert(rb.isEmpty());
    
    cout << "✓ 环形缓冲区工作正常" << endl;
}

void testClear() {
    cout << "\n=== 测试清空操作 ===" << endl;
    
    RingBuffer<int> rb(5);
    rb.push(1);
    rb.push(2);
    rb.push(3);
    
    rb.clear();
    assert(rb.isEmpty());
    assert(rb.size() == 0);
    
    // 清空后应该可以正常使用
    assert(rb.push(10));
    int value;
    assert(rb.pop(value) && value == 10);
    
    cout << "✓ 清空操作成功" << endl;
}

void testBatchOperations() {
    cout << "\n=== 测试批量操作 ===" << endl;
    
    RingBuffer<int> rb(10);
    
    // 批量 push
    int pushData[] = {1, 2, 3, 4, 5};
    size_t pushed = rb.pushMultiple(pushData, 5);
    assert(pushed == 5);
    assert(rb.size() == 5);
    cout << "✓ 批量 push 了 " << pushed << " 个元素" << endl;
    
    // 批量 pop
    int popData[3];
    size_t popped = rb.popMultiple(popData, 3);
    assert(popped == 3);
    assert(popData[0] == 1 && popData[1] == 2 && popData[2] == 3);
    assert(rb.size() == 2);
    cout << "✓ 批量 pop 了 " << popped << " 个元素" << endl;
}

void testWithStrings() {
    cout << "\n=== 测试字符串类型 ===" << endl;
    
    RingBuffer<string> rb(3);
    
    rb.push("Hello");
    rb.push("World");
    rb.push("C++");
    
    string str;
    rb.pop(str);
    cout << "✓ 弹出字符串: " << str << endl;
    
    rb.push("RingBuffer");
    
    while (!rb.isEmpty()) {
        rb.pop(str);
        cout << "  - " << str << endl;
    }
}

void testMoveSemantics() {
    cout << "\n=== 测试移动语义 ===" << endl;
    
    RingBuffer<int> rb1(5);
    rb1.push(1);
    rb1.push(2);
    rb1.push(3);
    
    // 移动构造
    RingBuffer<int> rb2(std::move(rb1));
    assert(rb2.size() == 3);
    
    int value;
    assert(rb2.pop(value) && value == 1);
    cout << "✓ 移动构造成功" << endl;
    
    // 移动赋值
    RingBuffer<int> rb3(10);
    rb3 = std::move(rb2);
    assert(rb3.size() == 2);
    assert(rb3.pop(value) && value == 2);
    cout << "✓ 移动赋值成功" << endl;
    
    // 测试右值 push
    RingBuffer<string> rb4(3);
    rb4.push(string("临时对象"));
    assert(rb4.size() == 1);
    cout << "✓ 右值 push 成功" << endl;
}

void testOptionalAPI() {
    cout << "\n=== 测试 Optional API ===" << endl;
    
    RingBuffer<int> rb(5);
    rb.push(100);
    rb.push(200);
    rb.push(300);
    
    // 使用 optional 版本的 pop
    auto value1 = rb.pop();
    assert(value1.has_value());
    assert(*value1 == 100);
    cout << "✓ Optional pop 成功，值为: " << *value1 << endl;
    
    // 使用 optional 版本的 peek
    auto value2 = rb.peek();
    assert(value2.has_value());
    assert(*value2 == 200);
    assert(rb.size() == 2); // peek 不改变大小
    cout << "✓ Optional peek 成功，值为: " << *value2 << endl;
    
    // 清空后测试
    rb.clear();
    auto empty = rb.pop();
    assert(!empty.has_value());
    cout << "✓ 空缓冲区返回 nullopt" << endl;
}

void testVectorAPI() {
    cout << "\n=== 测试 Vector API ===" << endl;
    
    RingBuffer<int> rb(10);
    
    // 使用 vector 批量 push
    vector<int> data = {10, 20, 30, 40, 50};
    size_t pushed = rb.pushMultiple(data);
    assert(pushed == 5);
    cout << "✓ Vector 批量 push 了 " << pushed << " 个元素" << endl;
    
    // 使用 vector 批量 pop
    auto popped = rb.popMultiple(3);
    assert(popped.size() == 3);
    assert(popped[0] == 10 && popped[1] == 20 && popped[2] == 30);
    cout << "✓ Vector 批量 pop 了 " << popped.size() << " 个元素" << endl;
}

void testIterator() {
    cout << "\n=== 测试迭代器 ===" << endl;
    
    RingBuffer<int> rb(5);
    rb.push(1);
    rb.push(2);
    rb.push(3);
    rb.push(4);
    
    cout << "  缓冲区内容: ";
    for (const auto& item : rb) {
        cout << item << " ";
    }
    cout << endl;
    
    // 验证迭代器顺序
    auto it = rb.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    cout << "✓ 迭代器工作正常" << endl;
}

void performanceTest() {
    cout << "\n=== 性能测试 ===" << endl;
    
    const size_t BUFFER_SIZE = 1000;
    const size_t OPERATIONS = 100000;
    
    RingBuffer<int> rb(BUFFER_SIZE);
    
    // 交替 push 和 pop
    for (size_t i = 0; i < OPERATIONS; ++i) {
        rb.push(i);
        if (i % 2 == 0) {
            int value;
            rb.pop(value);
        }
    }
    
    cout << "✓ 完成 " << OPERATIONS << " 次操作" << endl;
    cout << "  最终缓冲区大小: " << rb.size() << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "    环形缓冲区 (RingBuffer) 测试程序    " << endl;
    cout << "========================================" << endl;
    
    try {
        testBasicOperations();
        testFullAndEmpty();
        testCircularBehavior();
        testClear();
        testBatchOperations();
        testWithStrings();
        testMoveSemantics();
        testOptionalAPI();
        testVectorAPI();
        testIterator();
        performanceTest();
        
        cout << "\n========================================" << endl;
        cout << "         所有测试通过！✓✓✓" << endl;
        cout << "========================================" << endl;
        
    } catch (const exception& e) {
        cerr << "错误: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}

