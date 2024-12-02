<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : MyAlgo.md
   Last Modified : 2024-12-03 00:02
   Describe      : 

--->



# MyAlgo.hpp

## 文件信息

- **版权**: (C) 2024 All rights reserved.
- **作者**: OceanEyeFF
- **邮箱**: fdch00@163.com
- **最后修改日期**: 2024-11-30 00:40

## 描述

该头文件定义了一系列算法和数据结构，包括基础功能、位集操作、双向链表、文件处理、协程调度和计时器等。

## 命名空间 `MyAlgo`

### 子命名空间 `BasicFunc`

- `template <class T> void SwapTwoIntegers(T &a, T &b)`:
  - 交换两个整数的值，仅适用于整型。

- `template <class T> int CountOnes(T n)`:
  - 计算给定整数中1的位数。

- `template <class T> T read_int(char* c)`:
  - 从字符数组中读取整数。

- `template <class T> void write_int(char* c, T x)`:
  - 将整数写入字符数组。

### 子命名空间 `ForBitset`

- `template <size_t MAX_SIZE> size_t FindFirstZero(const std::bitset<MAX_SIZE>& b)`:
  - 查找位集中的第一个0的位置。

- `template <size_t MAX_SIZE> size_t FindFirstOne(const std::bitset<MAX_SIZE>& b)`:
  - 查找位集中的第一个1的位置。

## 类 `DoublyLinkedList`

实现一个双向链表，支持基本的插入、删除和遍历操作。

### 方法

- `void push_back(const T& value)`:
  - 在链表末尾添加新节点。

- `void push_front(const T& value)`:
  - 在链表开头添加新节点。

- `void insert(size_t index, const T& value)`:
  - 在指定位置插入节点。

- `void remove(size_t index)`:
  - 删除指定位置的节点。

- `void clear()`:
  - 清空链表。

- `void print() const`:
  - 正向遍历链表并打印。

- `void printReverse() const`:
  - 反向遍历链表并打印。

## 类 `FileHandler`

实现文件的读写操作，支持多线程和协程。

### 方法

- `void ReadFile()`:
  - 多线程读取文件。

- `void WriteToFile()`:
  - 将读取的数据写入文件。

- `const std::vector<std::string>& GetData() const`:
  - 获取读取的数据。

## 类 `GoSchedHost`

管理协程调度器的主机类，支持创建和停止协程。

### 方法

- `co::Scheduler* getSched()`:
  - 获取调度器实例。

- `void endHost()`:
  - 停止协程调度。

## 类 `Timer`

简单的计时器类，支持启动、停止和获取经过的时间。

### 方法

- `void start()`:
  - 启动计时器。

- `void stop()`:
  - 停止计时器。

- `double elapsedMilliseconds()`:
  - 获取经过的毫秒数。

## 类 `ArgConverter`

用于将字符串转换为命令行参数格式的类。

### 方法

- `int getArgc() const`:
  - 获取参数数量。

- `char** getArgv() const`:
  - 获取参数数组。

## 注意事项

- 确保在使用多线程和协程时正确处理共享数据的同步问题，以避免数据竞争和不一致性。
