#include "FileReader.hpp"
#include <iostream>
#include <memory>

int main() {
    std::cout << "=== C++ RAII 和智能指针演示 ===" << std::endl;
    std::cout << "规则：new 后必须立刻放入智能指针\n" << std::endl;

    try {
        // 创建测试文件
        createTestFile();
        std::cout << "✓ 测试文件已创建\n" << std::endl;

        // 演示智能指针的使用
        demonstrateSmartPointers();

        std::cout << "\n=== 总结 ===" << std::endl;
        std::cout << "✓ 所有 new 都立刻放入了智能指针" << std::endl;
        std::cout << "✓ 文件通过析构函数自动关闭，无需调用 .close()" << std::endl;
        std::cout << "✓ 没有内存泄漏，没有资源泄漏" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

