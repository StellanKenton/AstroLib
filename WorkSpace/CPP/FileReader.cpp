#include "FileReader.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>

// 构造函数实现
FileReader::FileReader(const std::string& filepath) : filename(filepath) {
    file.open(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开文件: " + filepath);
    }
    std::cout << "✓ 文件已打开: " << filename << std::endl;
}

// 析构函数实现
FileReader::~FileReader() {
    // 文件流的析构函数会自动关闭文件
    std::cout << "✓ 文件已自动关闭: " << filename << " (通过析构函数)" << std::endl;
}

// 读取整个文件内容
std::string FileReader::readAll() {
    if (!file.is_open()) {
        throw std::runtime_error("文件未打开");
    }
    
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    return content;
}

// 逐行读取
bool FileReader::readLine(std::string& line) {
    return static_cast<bool>(std::getline(file, line));
}

// 检查文件是否打开
bool FileReader::isOpen() const {
    return file.is_open();
}

// 创建测试文件
void createTestFile() {
    std::ofstream outFile("test.txt");
    if (outFile.is_open()) {
        outFile << "这是第一行\n";
        outFile << "这是第二行\n";
        outFile << "这是第三行\n";
        outFile << "RAII 原则：资源获取即初始化\n";
        outFile << "智能指针自动管理内存\n";
        // outFile 的析构函数会自动关闭文件
    }
}

// 演示函数：使用智能指针管理 FileReader
void demonstrateSmartPointers() {
    std::cout << "\n=== 演示 1: 使用 std::unique_ptr ===" << std::endl;
    {
        // new 后立刻放入 unique_ptr
        auto reader = std::unique_ptr<FileReader>(new FileReader("test.txt"));
        
        std::cout << "正在读取文件..." << std::endl;
        std::string content = reader->readAll();
        std::cout << "文件内容:\n" << content << std::endl;
        
        // 离开作用域时，unique_ptr 自动删除 FileReader
        // FileReader 的析构函数自动关闭文件
    }
    std::cout << "unique_ptr 已自动释放资源\n" << std::endl;

    std::cout << "=== 演示 2: 使用 std::shared_ptr ===" << std::endl;
    {
        // new 后立刻放入 shared_ptr
        auto reader1 = std::shared_ptr<FileReader>(new FileReader("test.txt"));
        
        {
            auto reader2 = reader1; // 共享所有权
            std::cout << "引用计数: " << reader1.use_count() << std::endl;
        }
        
        std::cout << "引用计数: " << reader1.use_count() << std::endl;
        // 最后一个 shared_ptr 销毁时，才会删除 FileReader
    }
    std::cout << "shared_ptr 已自动释放资源\n" << std::endl;

    std::cout << "=== 演示 3: 使用 std::make_unique (推荐) ===" << std::endl;
    {
        // 更好的方式：使用 make_unique，避免显式 new
        auto reader = std::make_unique<FileReader>("test.txt");
        
        std::string line;
        int lineNum = 1;
        while (reader->readLine(line)) {
            std::cout << "第 " << lineNum++ << " 行: " << line << std::endl;
        }
    }
    std::cout << "make_unique 已自动释放资源\n" << std::endl;
}

