<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : PRAlgoFIFO.md
   Last Modified : 2024-12-03 00:06
   Describe      : 

--->


# PRAlgoFIFO.h

## 文件信息

- **版权**: (C) 2024 All rights reserved.
- **作者**: OceanEyeFF
- **邮箱**: fdch00@163.com
- **最后修改日期**: 2024-11-30 16:08

## 描述

该头文件定义了 `FIFO_PageSelector` 类，继承自 `PRAlgoBase`，实现了先进先出（FIFO）页面替换算法的功能。

## 类 `FIFO_PageSelector`

### 私有成员

- `std::queue<PageEntry*> PageQueue`:
  - 页面队列，用于存储已加载的页面指针，采用 FIFO 策略。

### 重写的虚拟成员函数

- `int16_t AddNewPagePtr(PageEntry* PagePtr) override`:
  - 向页面队列中添加新的页面指针。返回值未定义，未来可能不需要返回值。

- `PageEntry* GetReplacePagePtr() override`:
  - 获取当前状态下要移出内存的页面指针。

- `PageEntry* RemoveReplacePagePtr() override`:
  - 移除当前状态下要替换的页面指针。

- `void RemovePagePtr(PageEntry* PagePtr) override`:
  - 移除指定的页面指针，通常用于内存去分配（deAlloc）。

### 公共成员函数

- `void init() override`:
  - 初始化 FIFO 页面选择器。

- `void clear() override`:
  - 清空页面选择器的状态。

- `int16_t size() override`:
  - 返回当前页面队列的大小。

- `void NotifyVisitingPages(PageEntry* PagePtr) override`:
  - 通知访问的页面，以更新访问状态。

- `int16_t CurrentPageUniqueVar() override`:
  - 返回当前页面的唯一变量。

- `bool CheckPageFull() override`:
  - 检查页面队列是否已满。

- `bool CheckPagePtrExist(PageEntry *PagePtr) override`:
  - 检查指定页面指针是否存在。

## 注意事项

- 此类实现了 FIFO 页面替换算法，确保在使用时遵循定义的接口。
- 该实现依赖于 `PageEntry` 类型，确保在使用时正确管理页面指针的生命周期。

