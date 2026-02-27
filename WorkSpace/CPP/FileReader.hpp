#pragma once

#include <fstream>
#include <string>
#include <concepts>

// 文件读取器类 - 利用析构函数自动关闭文件
class FileReader {
private:
    std::ifstream file;
    std::string filename;

public:
    // 构造函数：打开文件
    explicit FileReader(const std::string& filepath);

    // 析构函数：自动关闭文件（不调用 .close()）
    ~FileReader();

    // 禁止拷贝
    FileReader(const FileReader&) = delete;
    FileReader& operator=(const FileReader&) = delete;

    // 允许移动
    FileReader(FileReader&&) = default;
    FileReader& operator=(FileReader&&) = default;

    // 读取整个文件内容
    std::string readAll();

    // 逐行读取
    bool readLine(std::string& line);

    // 检查文件是否打开
    bool isOpen() const;
};

// 创建测试文件
void createTestFile();

// 演示函数：使用智能指针管理 FileReader
void demonstrateSmartPointers();

