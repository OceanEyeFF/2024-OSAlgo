<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : PageContainer.md
   Last Modified : 2024-12-03 00:03
   Describe      : 

--->



# PageContainer.h

## 文件信息

- **版权**: (C) 2024 All rights reserved.
- **作者**: OceanEyeFF
- **邮箱**: fdch00@163.com
- **最后修改日期**: 2024-11-28 21:25

## 描述

该头文件定义了 `PageContainer` 类，表示一级页表，负责管理页面的分配、读取和写入操作。它还涉及页面替换算法的全局变量。

## 类 `PageContainer`

### 数据成员

- `std::bitset<64> PagesUsage`:
  - 用于表示页面是否已经开辟，长度为8字节。

- `PageEntry Pages[64]`:
  - 存储页面条目，长度为128字节。

### 私有方法

- `void HandlePageContainerMissingPage(int8_t PageID)`:
  - 处理缺失页面的情况。

- `void HandlePageContainerIllegalAccess(int8_t PageID, std::string_view IllegalMessage)`:
  - 处理非法访问的情况（待实现）。

- `bool GetPageStatus()`:
  - 获取页面状态。

### 公共方法

- `PageContainer()`:
  - 构造函数，初始化 `PageContainer` 实例。

- `int8_t AllocNewPage()`:
  - 分配新的页面并返回页面ID。

- `bool AllocNewPage(AddressConj AddrConj)`:
  - 根据地址组合分配新的页面。

- `bool deAllocPage(AddressConj AddrConj)`:
  - 根据地址组合释放页面。

- `bool Read(AddressConj AddrConj, char* Dst)`:
  - 从指定地址读取数据到目标缓冲区。

- `bool Write(AddressConj AddrConj, char* Src)`:
  - 从源缓冲区写入数据到指定地址。

- `bool Read(AddressConj AddrConj, char* Dst, size_t size)`:
  - 从指定地址读取指定大小的数据到目标缓冲区。

- `bool Write(AddressConj AddrConj, char* Src, size_t size)`:
  - 从源缓冲区写入指定大小的数据到指定地址。

- `char* GetPhysicalPtr(AddressConj AddrConj)`:
  - 获取指定地址的物理指针。

- `void CheckPageEntryStatus(AddressConj AddrConj)`:
  - 检查页面条目的状态（调试用，待实现）。

## 注意事项

- 该类依赖于外部定义的 `AddressConj` 类型和其他头文件中的结构。
- 部分功能（如页面替换算法）尚未实现，后续需要补充。
