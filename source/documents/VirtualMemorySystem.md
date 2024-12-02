<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : VirtualMemorySystem.md
   Last Modified : 2024-12-03 00:08
   Describe      : 

--->



# VirtualMemorySystem.h

## 文件信息

- **版权**: (C) 2024 All rights reserved.
- **作者**: OceanEyeFF
- **邮箱**: fdch00@163.com
- **最后修改日期**: 2024-11-30 02:20

## 描述

该头文件定义了虚拟内存系统的相关功能，包括内存和磁盘操作的管理。

## 命名空间 `VirtualMemorySystem`

### 外部变量

- `int DiskOperationCounter`:
  - 记录磁盘操作次数的计数器。

- `char* pDefaultMemPool`:
  - 默认内存池指针。

- `char* pMemory`:
  - 当前使用的内存指针。

- `char* pDiskMemory`:
  - 磁盘内存的指针。

- `char* pSwapBuffer`:
  - 交换缓冲区指针。

- `int32_t MemorySize`:
  - 内存的总大小。

- `int32_t DiskMemorySize`:
  - 磁盘内存的总大小。

- `std::bitset<(LOCAL_MEMORYSIZE>>8)> LocalMemoryUsage`:
  - 本地内存使用情况的位集。

- `std::bitset<(DISK_MEMORYSIZE>>8)> DiskMemoryUsage`:
  - 磁盘内存使用情况的位集。

- `std::mutex MemMutex`:
  - 内存互斥锁（未使用）。

- `std::mutex DiskMutex`:
  - 磁盘互斥锁（未使用）。

### 函数

- `void init()`:
  - 初始化虚拟内存系统。

- `void release()`:
  - 释放虚拟内存系统的资源。

- `void DiskOperationCounterAdd()`:
  - 记录一次内存的移动操作。

### 类 `MemoryController`

该类负责内存的分配和管理。

#### 公共静态成员函数

- `uint16_t AllocDiskMem()`:
  - 分配磁盘内存并返回内存 ID。

- `uint16_t AllocLocalMem()`:
  - 分配本地内存并返回内存 ID。

- `void deAllocDiskMem(uint16_t MemID_Disk)`:
  - 释放指定的磁盘内存。

- `void deAllocLocalMem(uint16_t MemID_Local)`:
  - 释放指定的本地内存。

- `void InitMC()`:
  - 初始化内存控制器（临时未使用）。

- `void Read(char* pMemPtr_to, uint16_t MemID_Local, size_t MemSize)`:
  - 从本地内存读取数据。

- `void Write(char* pMemPtr_from, uint16_t MemID_Local, size_t MemSize)`:
  - 向本地内存写入数据。

- `void SwapBclks(char* pMemPtr_Local, char* pMemPtr_Disk)`:
  - 交换本地和磁盘的内存块（待弃用）。

- `void SwapBclks(uint16_t MemID_Local, uint16_t MemID_Disk)`:
  - 交换指定的本地和磁盘内存块。

- `uint16_t MoveToDiskMem(uint16_t MemID_Local)`:
  - 将本地内存移动到磁盘并返回磁盘内存 ID。

- `uint16_t MoveToLocalMem(uint16_t MemID_Disk)`:
  - 将磁盘内存移动到本地并返回本地内存 ID。

- `char* GetLocalPhysicalPtr(uint16_t MemID_Local)`:
  - 获取本地物理内存指针。

- `char* GetDiskPhysicalPtr(uint16_t MemID_Disk)`:
  - 获取磁盘物理内存指针。

- `uint16_t DiskMemCounter()`:
  - 返回当前磁盘内存的使用计数。

- `uint16_t LocalMemCounter()`:
  - 返回当前本地内存的使用计数。

- `bool DiskMemIsFull()`:
  - 检查磁盘内存是否已满。

- `bool LocalMemIsFull()`:
  - 检查本地内存是否已满。

## 注意事项

- 确保在使用过程中正确管理内存，避免内存泄漏。
- 代码中的注释和未使用的成员需要根据项目需求进行整理和清理。
