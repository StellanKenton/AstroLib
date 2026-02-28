#include "FileReader.hpp"
#include <iostream>
#include <memory>

int main() {

    try {
        // 创建测试文件
        createTestFile();
        // 演示智能指针的使用
        demonstrateSmartPointers();

    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

