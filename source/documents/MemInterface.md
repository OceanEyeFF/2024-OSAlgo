<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : MemInterface.md
   Last Modified : 2024-12-02 22:48
   Describe      : 

--->



# MemInterface.h

## 文件信息

- **版权**: (C) 2024 All rights reserved.
- **作者**: OceanEyeFF
- **邮箱**: fdch00@163.com
- **最后修改日期**: 2024-11-29 09:00

## 描述

该头文件定义了 `PCB_MemInterface` 类，负责内存管理接口的实现。该类支持内存的分配、释放、读取和写入操作，并与页面表进行交互以管理内存块。

## 类 `PCB_MemInterface`

### 私有成员

- `FstPageTable FirstPageTable`:
  - 管理内存页面的页表实例。

- `AddressPtr PtrPool[256]`:
  - 存储指针池，最多可容纳256个地址指针。

- `std::bitset<256> IsNull`:
  - 用于跟踪指针池中每个指针是否为空的位集。

### 公有方法

- `PCB_MemInterface()`:
  - 构造函数，初始化内存接口。

- `AddressPtr Alloc()`:
  - 分配一个新的内存块，假如没有释放操作，返回顺序从小到大的指针。

- `bool Alloc(AddressPtr AddrPtr)`:
  - 在指定位置分配内存，并返回该位置的页面条目是否已成功分配。

- `bool deAlloc(AddressPtr AddrPtr)`:
  - 释放指定位置的内存，返回操作是否合法。检查两种非法情况：
    1. 错误释放未分配的内存。
    2. 重复释放已释放的内存块。

- `bool Read(char* Dst, AddressPtr AddrPtr)`:
  - 从指定地址读取数据到目标缓冲区。

- `bool Write(char* Src, AddressPtr AddrPtr)`:
  - 将数据从源缓冲区写入指定地址。

- `bool Read(char* Dst, AddressPtr AddrPtr, size_t size)`:
  - 从指定地址读取特定大小的数据到目标缓冲区。

- `bool Write(char* Src, AddressPtr AddrPtr, size_t size)`:
  - 将特定大小的数据从源缓冲区写入指定地址。

- `char* GetPhysicalPtr(AddressPtr AddrPtr)`:
  - 获取指定地址的物理指针。

- `bool Alloc(int Poolid)`:
  - 在指定的内存池中分配内存块。

- `bool deAlloc(int Poolid)`:
  - 在指定的内存池中释放内存块。

- `bool Read(char* Dst, int Poolid)`:
  - 从指定内存池读取数据到目标缓冲区。

- `bool Write(char* Src, int Poolid)`:
  - 将数据从源缓冲区写入指定内存池。

- `void MoveIntoMem()`:
  - 将数据移动到内存中。

- `void MoveOutofMem()`:
  - 将数据移出内存。

- `void CheckPtrStatus()`:
  - 检查指针状态（调试用）。

- `void CheckMemStatus()`:
  - 检查内存状态（调试用）。

## 注意事项

确保在进行分配和释放操作时遵循内存管理的正确流程，以避免内存泄漏和非法访问。
