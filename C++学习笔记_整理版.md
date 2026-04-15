# C++ 学习笔记（整理版）

> 按主题分类，方便查找和复习

---

## 📑 目录

1. [基础数据类型](#1-基础数据类型)
2. [内存管理](#2-内存管理)
3. [指针与引用](#3-指针与引用)
4. [数组与容器](#4-数组与容器)
5. [字符串处理](#5-字符串处理)
6. [函数进阶](#6-函数进阶)
7. [模板编程](#7-模板编程)
8. [位运算与进制](#8-位运算与进制)
9. [UE实战应用](#9-ue实战应用)

---

## 1. 基础数据类型

### 1.1 变量初始化

**现代C++推荐使用 `{}` 初始化**

```cpp
int value{10};  // 推荐
int value = 10; // 传统方式
```

**优点**：
- ✅ 统一的风格
- ✅ 防止数据窄化（隐式转换）
- ✅ 类型不匹配时编译器报错

**注意**：只在初始化时用，赋值时不要用

---

### 1.2 整数类型

| 类型 | 字节数 | 范围 |
|------|--------|------|
| `short` | 2字节 | -32,768 ~ 32,767 |
| `int` | 4字节 | -2,147,483,648 ~ 2,147,483,647 |
| `long` | 4字节（Windows）| 平台相关（历史遗留问题）|
| `long long` | 8字节 | 超大整数 |

**注意**：
- `int` = `signed int`（默认有符号）
- `long` 在不同平台大小不同，跨平台开发要注意

---

### 1.3 浮点数类型

**float（32位）**：
```
┌─────┬──────────┬─────────────────────┐
│ 符号 │  指数    │      有效数字        │
│ 1位  │  8位     │      23位           │
└─────┴──────────┴─────────────────────┘
```

- 精度：约7位十进制数字
- 范围：±3.4 × 10³⁸

---

### 1.4 常量修饰符对比

| 特性 | `const` | `constexpr` | `constinit` |
|------|---------|-------------|-------------|
| 初始化时机 | 运行时（可能晚）| 编译时 | 编译时 |
| 初始化后能改吗？| ❌ 不能 | ❌ 不能 | ✅ 可以 |
| 必须用常量初始化？| ❌ 不一定 | ✅ 必须 | ✅ 必须 |
| 解决初始化顺序问题？| ❌ 不能 | ✅ 可以 | ✅ 专门为此设计 |

**使用建议**：
- 编译时常量 → `constexpr`
- 运行时不可变 → `const`
- 全局变量初始化顺序问题 → `constinit`

---

## 2. 内存管理

### 2.1 堆（Heap）vs 栈（Stack）

| 特性 | 栈（Stack）| 堆（Heap）|
|------|-----------|-----------|
| 大小 | 小（Windows默认1MB）| 大（受系统内存限制）|
| 速度 | 快 | 慢 |
| 管理 | 自动（编译器）| 手动（程序员）|
| 内存布局 | 连续 | 可能碎片化 |
| 生命周期 | 作用域结束自动释放 | 需要手动delete |

**通俗理解**：
- **栈**：像叠盘子，后进先出，自动管理
- **堆**：像仓库，随意摆放，需要手动整理

---

### 2.2 内存层级

```
CPU
 ↓
L1 缓存（最快，几KB）
 ↓
L2 缓存（快，几百KB）
 ↓
L3 缓存（较快，几MB）
 ↓
RAM 内存（栈、堆、全局变量都在这里）
 ↓
硬盘（最慢）
```

**关键点**：
- L1/L2/L3 在CPU内部，速度极快
- 栈、堆、全局变量都在RAM上，速度相同
- **栈快**是因为内存连续，CPU缓存命中率高
- **堆慢**是因为内存碎片化，缓存未命中率高

---

### 2.3 内存分配示例

```cpp
// 栈上分配（自动管理）
int stack_var = 10;  // 函数结束自动释放

// 堆上分配（手动管理）
int* heap_var = new int(10);  // 需要手动释放
delete heap_var;
heap_var = nullptr;  // 防止悬空指针
```

---

## 3. 指针与引用

### 3.1 指针基础

**指针 = 存储地址的变量**

```cpp
int value = 42;
int* ptr = &value;  // ptr存储value的地址

std::cout << ptr;   // 输出地址
std::cout << *ptr;  // 输出值42
```

**关键概念**：
- `&` 取地址符
- `*` 解引用符
- 指针大小：64位系统8字节，32位系统4字节

---

### 3.2 指针操作

```cpp
// 动态内存分配
int* ptr = new int(10);        // 单个变量
int* arr = new int[5]{1,2,3};  // 数组

// 释放内存
delete ptr;      // 释放单个变量
delete[] arr;    // 释放数组（注意[]）

// 防止悬空指针
ptr = nullptr;
arr = nullptr;
```

**指针算术**：
```cpp
int arr[5] = {10, 20, 30, 40, 50};
int* p = arr;

p++;        // 移动sizeof(int)字节（通常4字节）
*(p + 2);   // 访问arr[2]
```

---

### 3.3 指针常见问题

#### 悬空指针（Dangling Pointer）
```cpp
int* p = new int(42);
delete p;
// p现在是悬空指针，使用*p会崩溃！

// 解决方案
delete p;
p = nullptr;  // 立即置空
```

#### 内存泄漏（Memory Leak）
```cpp
void BadFunction() {
    int* p = new int(100);
    // 函数结束，p被销毁，但new出来的内存没释放！
}

void GoodFunction() {
    int* p = new int(100);
    delete p;  // 正确释放
}
```

#### 申请内存失败处理
```cpp
int* ptr = new(std::nothrow) int(2);  // 失败返回nullptr，不抛异常
if (ptr == nullptr) {
    // 处理失败情况
}
```

---

### 3.4 引用（Reference）

**引用 = 变量的别名**

```cpp
int original = 100;
int& ref = original;  // ref是original的别名

ref = 200;  // 修改ref就是修改original
```

**特性**：
- ✅ 必须初始化，不能为空
- ✅ 一旦绑定，不能改绑到其他变量
- ✅ 不占用额外内存（编译器优化）

---

### 3.5 指针 vs 引用

| 特性 | 指针 | 引用 |
|------|------|------|
| 可以为空 | ✅ (nullptr) | ❌ 必须初始化 |
| 可以重新指向 | ✅ | ❌ 一旦绑定不可改 |
| 需要解引用 | ✅ (*p) | ❌ 直接使用 |
| 语法复杂度 | 较高 | 简单 |
| 适用场景 | 动态内存、可选参数 | 函数参数、返回值 |

**使用建议**：
- 函数参数传递 → 引用（`const T&`）
- 动态内存管理 → 指针
- 可能为空的情况 → 指针

---

## 4. 数组与容器

### 4.1 多维数组的问题

**不推荐嵌套数组**：
```cpp
// ❌ 不推荐
int arr[3][4];  // 可能内存不连续
```

**推荐用一维数组模拟**：
```cpp
// ✅ 推荐
int arr[12];  // 3行4列，内存连续
```

**原因**：
1. 多维数组容易内存碎片化
2. CPU缓存未命中率高
3. 嵌套数组容易爆栈（Windows栈默认1MB）

---

### 4.2 多维数组索引公式

**二维数组**：
```cpp
// 访问 arr[row][col]
index = row * 总列数 + col
```

**三维数组**：
```cpp
// 访问 arr[page][row][col]
index = page * 总行数 * 总列数 + row * 总列数 + col
```

**示例**：
```cpp
// 3页 × 4行 × 5列
int arr[60];  // 一维数组模拟

// 访问第2页、第3行、第4列
int index = 2 * 4 * 5 + 3 * 5 + 4;  // = 59
```

---

### 4.3 数组工具函数

```cpp
#include <array>

int arr[5] = {1, 2, 3, 4, 5};

std::size(arr);  // 返回5（元素数量）
```

---

## 5. 字符串处理

### 5.1 std::string

```cpp
#include <string>

std::string str = "Hello";

str.capacity();        // 容量
str.shrink_to_fit();   // 缩小到实际大小
```

---

### 5.2 std::string_view（C++17）

**设计目的**：避免 `char[]` → `std::string` 的拷贝

```cpp
#include <string_view>

char arr[] = "Hello";
std::string_view view{arr};  // 只记录地址和长度，不拷贝

// 打印地址
std::cout << (const void*)view.data() << std::endl;
```

**特点**：
- ✅ 零拷贝，只是"看"
- ✅ 轻量级，只存地址和长度
- ❌ 不拥有数据，原数据销毁后失效

---

## 6. 函数进阶

### 6.1 函数重载规则

**重载只看参数**：类型、个数、顺序

```cpp
void func(int a);           // ✅
void func(double a);        // ✅ 类型不同
void func(int a, int b);    // ✅ 个数不同
void func(double a, int b); // ✅ 顺序不同

// ❌ 返回值不同不算重载
int func(int a);
double func(int a);  // 错误！
```

**const重载规则**：
```cpp
// 顶层const不算重载（❌）
void func(int a);
void func(const int a);  // 错误！参数拷贝，const无意义

// 底层const算重载（✅）
void func(int& a);
void func(const int& a);  // 正确！可以重载
```

---

### 6.2 静态变量

```cpp
// 全局变量（整个程序可见）
int global_var = 10;

// 静态全局变量（只在当前.cpp可见）
static int static_var = 20;
```

**优点**：
- 生命周期和全局变量一样
- 可见范围限制在当前文件，防止命名冲突

---

### 6.3 内联函数

**作用**：编译时将函数体直接插入调用处，减少函数调用开销

```cpp
inline int add(int a, int b) {
    return a + b;
}
```

**UE中的用法**：
```cpp
FORCEINLINE float FastCalculation() {
    return x * y + z;
}
```

**注意**：
- 编译器可以拒绝内联
- 虚函数、递归、大函数不会内联

---

### 6.4 递归

**定义**：函数自己调用自己

```cpp
int Factorial(int n) {
    if (n <= 1) return 1;  // 终止条件
    return n * Factorial(n - 1);
}
```

**适用场景**：
- 树/图遍历
- 分治算法
- 数学递推公式

---

### 6.5 std::optional（C++17）

**设计目的**：表示"可能有值，可能没有"的状态

```cpp
#include <optional>

std::optional<int> FindValue(int key) {
    if (found) {
        return 42;  // 有值
    }
    return std::nullopt;  // 无值
}

// 使用
auto result = FindValue(10);
if (result.has_value()) {
    std::cout << result.value() << std::endl;
}
```

**UE中的应用**：
```cpp
TOptional<FInventoryItem> FindItemByTag(FGameplayTag Tag) {
    // 找到了返回物品
    // 找不到返回空
}
```

---

### 6.6 函数参数传递

**避免拷贝开销**：
```cpp
// ❌ 值传递（拷贝整个对象）
void Process(std::string str);

// ✅ const引用（不拷贝，不修改）
void Process(const std::string& str);

// ✅ 引用（不拷贝，可修改）
void Modify(std::string& str);
```

---

## 7. 模板编程

### 7.1 函数模板

```cpp
template <typename T>
const T& GetMax(const T& a, const T& b) {
    return (a > b) ? a : b;
}

// 使用
int max_int = GetMax(10, 20);
double max_double = GetMax(3.14, 2.71);
```

---

### 7.2 函数模板特化

```cpp
// 通用模板
template <typename T>
const T& GetMax(const T& a, const T& b) {
    return (a > b) ? a : b;
}

// 特化版本（针对const char*）
template<>
const char* GetMax(const char* a, const char* b) {
    return std::strcmp(a, b) > 0 ? a : b;
}
```

---

### 7.3 decltype(auto) - 精准类型推导

```cpp
template <typename T>
decltype(auto) Test1(T& x) {
    return x;   // 返回值（拷贝）
}

template <typename T>
decltype(auto) Test2(T& x) {
    return (x);  // 返回引用（注意括号）
}
```

**区别**：
- `auto` 会退化（去掉const、引用）
- `decltype(auto)` 保留完整类型

---

### 7.4 非类型模板参数

```cpp
template <typename T, int Size>
class Array {
    T data[Size];  // 编译时确定大小
};

Array<int, 10> arr;  // 创建大小为10的数组
```

---

### 7.5 类型检查（<type_traits>）

```cpp
#include <type_traits>

std::is_integral<int>::value;        // true
std::is_class<std::string>::value;   // true
std::is_floating_point<double>::value;  // true
```

---

### 7.6 requires 约束（C++20）

```cpp
template <typename T>
requires std::is_integral<T>::value
void ProcessInt(T value) {
    // 只接受整数类型
}
```

---

### 7.7 概念（Concepts，C++20）

```cpp
#include <concepts>

// 使用标准概念
template <std::integral T>
void Func(T value) { }

// 自定义概念
template <typename T>
concept MyIntegral = std::is_integral<T>::value;

template <MyIntegral T>
void MyFunc(T value) { }
```

---

## 8. 位运算与进制

### 8.1 进制表示

| 进制 | 前缀 | 示例 | 输出控制 |
|------|------|------|----------|
| 二进制 | `0b` | `0b1111` | `std::bitset<8>(n)` |
| 八进制 | `0` | `0377` | `std::oct` |
| 十进制 | 无 | `255` | `std::dec` |
| 十六进制 | `0x` | `0xFF` | `std::hex` |

**示例**：
```cpp
int a = 0x11;      // 十六进制 → 17
int b = 0b011;     // 二进制   → 3
int c = 011;       // 八进制   → 9
```

---

### 8.2 位运算符

| 运算符 | 名称 | 示例 |
|--------|------|------|
| `&` | 按位与 | `a & b` |
| `\|` | 按位或 | `a \| b` |
| `~` | 按位非 | `~a` |
| `^` | 按位异或 | `a ^ b` |
| `<<` | 左移 | `a << 2` |
| `>>` | 右移 | `a >> 2` |

---

### 8.3 位运算应用场景

**权限系统**：
```cpp
constexpr unsigned int Perm_Move  = 1 << 0;  // 0x1
constexpr unsigned int Perm_Attack = 1 << 1;  // 0x2
constexpr unsigned int Perm_Use    = 1 << 2;  // 0x4

// 授予权限
permissions |= Perm_Move | Perm_Attack;

// 移除权限
permissions &= ~Perm_Use;

// 检查权限
if (permissions & Perm_Move) {
    // 有移动权限
}
```

**UE中的应用**：
- 碰撞通道设置
- 渲染模式设置
- 颜色通道操作
- 文件打包压缩

---

## 9. UE实战应用

### 9.1 Lyra背包系统（Optional应用）

**结构**：
```
背包 = TArray<FInventoryItemEntry>
条目 = FGameplayTag（物品ID）+ int32（数量）
全局模板 = DataAsset（所有背包共享）
```

**流程**：
```
使用道具
  ↓
FindItemByTag(物品ID)
  ↓
遍历TArray
  ↓
找到 → 返回TOptional(有值)
找不到 → 返回TOptional(nullopt)
  ↓
if (Result.IsSet())
  ↓
检查数量 > 0
  ↓
通过ID找到DataAsset
  ↓
调用Use函数
  ↓
背包数量 -1
```

---

### 9.2 权限系统实现

完整代码见笔记第4天内容，核心思路：

1. 用位运算定义权限标志
2. 用 `|` 授予权限
3. 用 `&~` 移除权限
4. 用 `&` 检查权限

---

## 📌 快速查找索引

### 按关键词查找

- **内存相关**：[2. 内存管理](#2-内存管理)
- **指针问题**：[3.3 指针常见问题](#33-指针常见问题)
- **数组优化**：[4.1 多维数组的问题](#41-多维数组的问题)
- **字符串性能**：[5.2 std::string_view](#52-stdstring_view)
- **函数重载**：[6.1 函数重载规则](#61-函数重载规则)
- **模板约束**：[7.6 requires约束](#76-requires-约束c20)
- **位运算应用**：[8.3 位运算应用场景](#83-位运算应用场景)

---

## 🎯 复习建议

1. **每日复习**：快速浏览目录，回忆关键概念
2. **实践为主**：每个知识点写一个小Demo
3. **对比学习**：指针vs引用、栈vs堆等对比表格
4. **UE结合**：每学一个概念，想想在UE中的应用
5. **定期总结**：每周回顾本周学习内容，补充新理解

---

**最后更新**：2026-04-13
