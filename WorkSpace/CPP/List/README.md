# std::unique_ptr 链表重构示例

## 编译和运行

```bash
g++ -std=c++14 main.cpp -o list_demo
./list_demo
```

## 项目说明

本项目演示了如何将使用原始指针的链表重构为使用 `std::unique_ptr` 的现代C++实现。

## 核心知识点

### 1. 零开销抽象（Zero-overhead Abstraction）
- `std::unique_ptr` 在编译时优化，运行时没有额外开销
- 大小与原始指针相同（sizeof(unique_ptr<T>) == sizeof(T*)）
- 性能等同于手动管理的原始指针

### 2. 移动语义在指针中的应用
```cpp
// 转移所有权
auto newNode = std::make_unique<Node>(val);
newNode->next = std::move(head);  // 移动，不是拷贝
head = std::move(newNode);
```

### 3. std::make_unique
- C++14 引入，推荐使用
- 异常安全
- 语法简洁：`std::make_unique<T>(args)` vs `std::unique_ptr<T>(new T(args))`

## 对比总结

| 特性 | 原始指针 | std::unique_ptr |
|------|---------|-----------------|
| 内存管理 | 手动 delete | 自动释放 |
| 所有权 | 不明确 | 明确的独占所有权 |
| 拷贝 | 需要手动禁止 | 自动禁止 |
| 移动 | 不支持 | 原生支持 |
| 异常安全 | 容易泄漏 | 自动清理 |
| 性能开销 | 无 | 无（零开销） |

## 输出示例

程序会展示三个场景：
1. 旧版本使用原始指针的实现
2. 新版本使用 unique_ptr 的实现
3. 移动语义的演示

每个场景都会显示析构过程，帮助理解内存管理的差异。

