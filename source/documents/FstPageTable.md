<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : FstPageTable.md
   Last Modified : 2024-12-02 22:46
   Describe      : 

--->

# FstPageTable.h

## 文件信息

- **版权**: (C) 2024 All rights reserved.
- **作者**: OceanEyeFF
- **邮箱**: fdch00@163.com
- **最后修改日期**: 2024-11-28 23:36

## 描述

该头文件定义了 `FstPageTable` 类，用于管理页面表的内存分配与释放。此类提供了对内存块的分配、读取和写入操作的接口，并包含处理缺失页面的功能。

## 类 `FstPageTable`

### 私有成员

- `PageContainer Table[4]`:
  - 存储页面的容器数组。

- `void HandleMissingPage()`:
  - 处理缺失页面的私有方法。

### 公有方法

- `FstPageTable()`:
  - 构造函数，初始化页面表。

- `AddressConj AllocNewPage()`:
  - 分配一个新的内存页面，返回地址的结合体。

- `bool AllocNewPage(AddressConj AddrConj)`:
  - 根据给定的地址结合体分配新的内存页面。

- `bool deAllocPage(AddressConj AddrConj)`:
  - 释放指定地址结合体的内存页面。

- `bool Read(AddressConj AddrConj, char* Dst)`:
  - 从指定地址读取数据到目标缓冲区。

- `bool Write(AddressConj AddrConj, char* Src)`:
  - 将数据从源缓冲区写入指定地址。

- `bool Read(AddressConj AddrConj, char* Dst, size_t size)`:
  - 从指定地址读取特定大小的数据到目标缓冲区。

- `bool Write(AddressConj AddrConj, char* Src, size_t size)`:
  - 将特定大小的数据从源缓冲区写入指定地址。

- `char* GetPhysicalPtr(AddressConj AddrConj)`:
  - 获取指定地址结合体的物理指针。

- `void CheckPageEntryStatus(AddressConj AddrConj)`:
  - 检查指定地址的页面条目状态（调试用）。

## 待办事项

- 实现一次分配一个或多个内存块的功能。
- 解决在不影响程序指针正确性的情况下确保内存块连续的方法。
