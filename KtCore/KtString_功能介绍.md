# KtString 功能介绍

## 一、设计背景与目的

### 1.1 问题背景

在 C++ 跨动态库（DLL/SO）开发中，使用标准库的 `std::string` 会遇到严重的内存管理问题：

**核心问题**：
- **内存分配与释放不匹配**：在一个动态库中分配的内存，如果在另一个动态库中释放，会导致程序崩溃
- **ABI 兼容性问题**：不同编译器版本、编译选项或运行时库版本可能导致 `std::string` 的内部实现不同
- **模板实例化问题**：模板类在不同编译单元中可能被实例化为不同的类型，导致类型不匹配
- **堆管理不一致**：不同动态库可能链接到不同的堆管理器，导致内存操作失败

### 1.2 解决方案

`KtString` 通过以下核心设计原则解决了这些问题：

1. **统一的内存管理**：所有内存分配和释放都在同一个动态库（KtCore）中完成
2. **显式的导出符号**：使用 `ExportedByKtCore` 宏确保类在动态库中正确导出
3. **自定义内存布局**：使用自定义结构体管理字符串元数据，避免依赖标准库实现
4. **单一内存块分配**：元数据和字符串数据在同一个内存块中，简化内存管理

## 二、核心架构设计

### 2.1 内存布局设计

`KtString` 采用了一种巧妙的内存布局设计：

```
内存布局：
[KtStringStruct] [字符串数据] [\0]
     ↓                ↓
  (元数据)         (实际内容)
  - space          - 字符数组
  - size           - 以 '\0' 结尾
```

**关键设计点**：
- `KtStringStruct` 结构体包含两个 `unsigned int` 字段：
  - `space`：字符串缓冲区的容量（不包括 '\0'）
  - `size`：当前字符串的实际长度
- 字符串数据通过 `data()` 方法访问，位于结构体后一个位置（`this + 1`）
- 整个内存块通过单次 `new char[]` 分配，包括结构体和字符串数据
- 字符串数据末尾始终有 '\0' 作为结束符

**优势**：
- 内存局部性好，提高缓存命中率
- 单次分配减少内存碎片
- 简化内存管理逻辑

### 2.2 空字符串优化机制

为了避免频繁的内存分配，`KtString` 使用静态 dummy 对象来优化空字符串：

**实现方式**：
- 定义静态全局数组 `g_KtString_Array`，包含三个 `unsigned int`（两个 0 作为 space 和 size，一个 0 作为字符串结束符）
- 将数组强制转换为 `KtStringStruct*` 作为 dummy 结构体
- 所有空字符串都指向这个静态 dummy 对象

**优势**：
- 空字符串不需要分配内存，提高性能
- 简化空字符串的判断逻辑（只需比较指针）
- 减少内存分配次数，降低内存碎片

### 2.3 内存管理策略

**分配策略**：
- `allocate_buffer(count)` 方法负责分配内存
- 分配大小为 `sizeof(KtStringStruct) + count + 1`（结构体 + 字符串 + 结束符）
- 使用 `try-catch` 捕获内存分配异常
- 初始化时设置 `space = count`，`size = 0`，并在首尾设置 '\0'

**释放策略**：
- `safe_delete()` 方法负责安全释放内存
- 释放前检查是否为 dummy 对象，避免误释放静态对象
- 析构函数中检查 `_pText != g_KtString_DummyText` 再释放

**扩容策略**：
- `reserve(count)` 方法实现动态扩容
- 当前采用重新分配策略：分配新内存 → 复制数据 → 释放旧内存
- 如果新容量小于等于当前容量，直接返回当前容量

## 三、主要功能模块

### 3.1 构造与析构

**构造函数**：
- `KtString(unsigned int space = 0)`：创建指定容量的空字符串
- `KtString(int space)`：同上，接受 int 类型
- `KtString(const char* str, unsigned int count = UINT_MAX)`：从 C 字符串构造
- `KtString(const KtString& iOriginal)`：拷贝构造

**析构函数**：
- 检查是否为 dummy 对象，只有非 dummy 对象才释放内存
- 使用 `delete[] (char*)_pData` 释放整个内存块

### 3.2 赋值操作

**赋值运算符**：
- `operator=(const KtString& other)`：拷贝赋值，支持自赋值检查
- `operator=(const char* str)`：从 C 字符串赋值

### 3.3 比较操作

**比较运算符**：
- `operator==(const KtString& other)`：相等比较
- `operator==(const char* str)`：与 C 字符串比较
- `operator<(const KtString& other)`：小于比较（用于排序）
- `compare(const char* other)`：返回比较结果（-1/0/1）
- `operator!()`：判断字符串是否为空

**实现方式**：
- 使用标准库 `strcmp()` 函数进行比较

### 3.4 连接操作

**连接运算符**：
- `operator+(const KtString& other)`：返回新字符串
- `operator+(const char* str)`：与 C 字符串连接

**流式追加操作符**（`operator<<`）：
- `operator<<(char ch)`：追加单个字符
- `operator<<(int value)`：追加整数（使用 `snprintf` 转换）
- `operator<<(unsigned int value)`：追加无符号整数
- `operator<<(float value)`：追加浮点数（通过 `set_num` 转换）
- `operator<<(const char* str)`：追加 C 字符串
- `operator<<(const KtString& other)`：追加另一个 KtString
- `operator<<(void* ptr)`：追加指针地址（格式化为十六进制）

**特点**：
- `+` 运算符返回新对象，不修改原对象
- `<<` 运算符修改原对象并返回引用，支持链式调用

### 3.5 字符串修改操作

**追加操作**：
- `append(const char* str, unsigned int len = UINT_MAX)`：追加指定长度的字符串
  - 如果 `len` 大于实际字符串长度，会用空格填充
  - 支持自动计算长度

**插入操作**：
- `insert(unsigned int position, const char* after, unsigned int len = -1)`：在指定位置插入字符串
  - 如果位置超出范围，则追加到末尾
  - 使用 `memmove` 安全地移动内存

**替换操作**：
- `replace(unsigned int position, unsigned int n, const char* after, unsigned int len = -1)`：替换指定位置的字符
  - 支持替换长度与原始长度不同的情况
  - 自动处理内存移动和调整

**删除操作**：
- `remove(unsigned int position, unsigned int count)`：删除指定位置的字符
  - 内部调用 `replace` 实现

**清空操作**：
- `clear()`：清空内容但保留内存（设置 `size = 0`，首字符设为 '\0'）
- `release()`：释放内存，重置为 dummy 对象

**调整操作**：
- `reserve(unsigned int count)`：改变容量
- `resize(unsigned int count)`：改变大小
- `resize(unsigned int count, const char fillChar)`：改变大小并填充

### 3.6 字符串查询操作

**长度查询**：
- `size()`：获取当前字符串长度
- `capacity()`：获取字符串容量
- `is_empty()`：检查是否为空

**字符访问**：
- `operator[](unsigned int index)`：访问指定位置的字符（无边界检查）
- `front()`：获取首字符
- `back()`：获取尾字符
- `data()`：获取可修改的数据指针
- `str()`：获取只读的 C 字符串指针

**子串提取**：
- `left(unsigned int count)`：提取左侧指定长度的子串
- `right(unsigned int count)`：提取右侧指定长度的子串
- `sliced(unsigned int pos, unsigned int count = -1)`：提取指定位置和长度的子串

### 3.7 字符串转换操作

**数字转字符串**：
- `set_num(int value)`：整数转字符串
- `set_num(unsigned int value)`：无符号整数转字符串
- `set_num(float value, unsigned int n = 6)`：浮点数转字符串（n 为小数位数，最大 8）
- `set_num(double value, unsigned int n = 6)`：双精度浮点数转字符串（n 为小数位数，最大 16）
- `set_numWidth(int value, unsigned int minWidth, const char fillChar = ' ')`：数字转字符串并格式化宽度
- `set_numWidth(double value, unsigned int minWidth, const char fillChar = ' ')`：双精度数字转字符串并格式化宽度

**字符串转数字**：
- `to_int()`：转换为整数（使用 `atoi`）
- `to_double()`：转换为双精度浮点数（使用 `atof`）

**大小写转换**：
- `to_upper()`：转换为大写（原地修改）
- `to_upper_copy()`：转换为大写（返回新对象）
- `to_lower()`：转换为小写（原地修改）
- `to_lower_copy()`：转换为小写（返回新对象）

**实现特点**：
- 大小写转换只处理 ASCII 字符（A-Z 和 a-z）
- 数字转换使用标准库函数

### 3.8 字符串处理操作

**填充操作**：
- `fill(int width, const char fillChar = ' ')`：用指定字符填充字符串
  - 正数：右填充（从末尾开始）
  - 负数：左填充（从开头开始）
  - 宽度大于字符串长度时，填充整个字符串
- `fill_width(unsigned int minWidth, const char fillChar = ' ')`：调整字符串到指定宽度
  - 如果当前长度小于目标宽度，用指定字符填充
  - 支持左对齐和右对齐

**移位操作**：
- `shift(int dis, const char fillChar = ' ')`：字符串左右移位
  - 正数：右移（前面填充指定字符）
  - 负数：左移（删除左侧字符）
  - 移位距离超过字符串长度时，清空字符串

**修剪操作**：
- `trim()`：去除首尾空白字符（空格、制表符、换行符、回车符）
- `trim_left(unsigned int count)`：从左侧截断指定长度

**修正操作**：
- `correct()`：根据字符串中的第一个 '\0' 修正 `size` 值
  - 用于处理字符串被外部修改的情况

### 3.9 特殊功能

**文件名操作**：
- `append_filename(const KtString& fileName)`：智能拼接文件路径
  - 自动在路径和文件名之间添加 '/' 或 '\' 分隔符
  - 如果当前字符串末尾已有分隔符，则不添加

**流输出支持**：
- `operator<<(std::ostream& os, const KtString& str)`：支持标准输出流
  - 可以直接使用 `std::cout << str` 输出

**调试支持**：
- `dump()`：输出字符串内容到标准输出（用于调试）

## 四、设计优势

### 4.1 跨动态库安全性

**核心优势**：
- 所有内存操作（分配、释放、访问）都在 KtCore 动态库中完成
- 确保内存分配器和释放器来自同一个模块
- 避免了跨库内存管理的崩溃问题

**适用场景**：
- 主程序调用动态库函数，函数返回 KtString
- 动态库 A 创建 KtString，传递给动态库 B 使用
- 多个动态库共享 KtString 对象

### 4.2 性能优化

**优化点**：
1. **空字符串优化**：使用静态对象，零内存分配
2. **单次内存分配**：结构体和数据一起分配，减少内存碎片
3. **内联函数**：常用操作（如 `size()`、`str()`）使用内联，减少函数调用开销
4. **内存局部性**：元数据和数据在同一内存块，提高缓存命中率

### 4.3 API 设计

**设计特点**：
- 提供丰富的字符串操作方法，类似 Qt 的 QString
- 支持链式调用，使用方便（如 `str.append("a").append("b")`）
- 提供多种构造和转换方式，灵活性高
- 同时提供原地修改和返回新对象的版本（如 `to_upper()` 和 `to_upper_copy()`）

**易用性**：
- 支持流式操作符 `<<`，可以像流一样追加内容
- 支持标准输出流，可以直接输出
- 提供类似 Qt 风格的 API，对 Qt 开发者友好

## 五、使用场景

### 5.1 适用场景

**跨动态库字符串传递**：
- 主程序与多个动态库之间传递字符串
- 动态库之间相互传递字符串
- 需要确保内存安全性的场景

**遗留系统维护**：
- 已有系统使用 KtString，需要保持兼容性
- 从其他字符串类迁移到 KtString
- 需要避免 std::string 跨库问题的项目

**特定性能要求**：
- 需要控制内存分配的场景
- 需要减少内存碎片的场景
- 对空字符串操作频繁的场景

### 5.2 不适用场景

**纯头文件库项目**：
- 如果项目不需要动态库，直接使用 `std::string` 更简单
- KtString 的设计目标是解决跨库问题，单库项目不需要

**高性能要求场景**：
- 如果对性能要求极高，可能需要考虑其他方案
- `std::string` 在某些场景下可能更优化（如小字符串优化）

**国际化项目**：
- 当前版本只支持 ASCII，不支持 Unicode
- 需要 UTF-8/UTF-16 支持的项目需要扩展或使用其他方案

**现代 C++ 项目**：
- 如果项目可以使用 C++17 及以上版本，可以考虑使用 `std::string_view`
- 如果不需要跨库，`std::string` 可能更合适

## 六、兼容性说明

### 6.1 C++ 标准兼容性

- **头文件**：兼容 C++98 标准，可在 VS 2005 等旧编译器上编译
- **实现文件**：可使用 C++17 等新标准特性（如 `noexcept`、移动语义等）

### 6.2 平台兼容性

- 支持 Windows（DLL）和 Linux（SO）平台
- 使用标准 C++ 特性，不依赖平台特定 API

## 七、总结

`KtString` 是一个专门为解决跨动态库字符串问题而设计的字符串类。它通过统一的内存管理、自定义的内存布局和空字符串优化，有效解决了 `std::string` 在跨库使用时的崩溃问题。

**核心价值**：
- 解决了跨动态库内存管理的根本问题
- 提供了丰富的字符串操作 API
- 在特定场景下提供了良好的性能和安全性

**设计特点**：
- 统一的内存管理确保跨库安全性
- 自定义内存布局提高性能
- 丰富的 API 提供良好的易用性
- 兼容旧版编译器，同时支持新标准特性
