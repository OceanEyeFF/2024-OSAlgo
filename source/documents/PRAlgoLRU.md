<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : PRAlgoLRU.md
   Last Modified : 2024-12-03 00:06
   Describe      : 

--->


# PRAlgoLRU.h

## 文件信息

- **版权**: (C) 2024 All rights reserved.
- **作者**: OceanEyeFF
- **邮箱**: fdch00@163.com
- **最后修改日期**: 2024-11-30 16:09

## 描述

该头文件定义了 `LRU_PageSelector` 类，继承自 `PRAlgoBase`，实现了最近最少使用（LRU）页面替换算法。

## 类 `LRU_PageSelector`

### 私有成员

- `DoublyLinkedList<PageEntry*> PageList`:
  - 存储页面指针的双向链表，用于管理页面的访问顺序。

- `DoublyLinkedList<PageEntry*>::Node* PageListMap[BLCK_CNT]`:
  - 页面列表的映射，提供对每个内存块的快速访问。

### 重写的虚拟成员函数

- `int16_t AddNewPagePtr(PageEntry* PagePtr) override`:
  - 向页面列表中添加新的页面指针。

- `PageEntry* GetReplacePagePtr() override`:
  - 获取当前状态下要替换的页面指针。

- `PageEntry* RemoveReplacePagePtr() override`:
  - 移除当前状态下要替换的页面指针。

- `void RemovePagePtr(PageEntry* PagePtr) override`:
  - 移除指定的页面指针。

### 公共成员函数

- `void init() override`:
  - 初始化 LRU 页面选择器。

- `void clear() override`:
  - 清空页面选择器的状态。

- `int16_t size() override`:
  - 返回当前页面列表的大小。

- `void NotifyVisitingPages(PageEntry *PagePtr) override`:
  - 通知访问的页面，以更新访问状态，并维护访问顺序。

- `int16_t CurrentPageUniqueVar() override`:
  - 返回当前页面的唯一变量。

- `bool CheckPageFull() override`:
  - 检查页面列表是否已满。

- `bool CheckPagePtrExist(PageEntry *PagePtr) override`:
  - 检查指定页面指针是否存在。

## 注意事项

- 此类实现了 LRU 页面替换算法，确保在使用时遵循定义的接口。
- 该实现依赖于 `DoublyLinkedList` 和 `PageEntry` 类型，确保在使用时正确管理页面指针的生命周期。
