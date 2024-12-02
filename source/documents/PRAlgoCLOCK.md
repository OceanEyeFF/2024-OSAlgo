<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : PRAlgoCLOCK.md
   Last Modified : 2024-12-03 00:05
   Describe      : 

--->



# PRAlgoCLOCK.h

## 文件信息

- **版权**: (C) 2024 All rights reserved.
- **作者**: OceanEyeFF
- **邮箱**: fdch00@163.com
- **最后修改日期**: 2024-11-30 16:08

## 描述

该头文件定义了 `CLOCK_PageSelector` 类，继承自 `PRAlgoBase`，实现了时钟页面替换算法的功能。

## 类 `CLOCK_PageSelector`

### 私有成员

- `PageEntry* PageQueue[BLCK_CNT]`:
  - 页面队列，用于存储已加载的页面。

- `int16_t CurrentNode`:
  - 当前节点索引，指向页面队列中的当前位置。

- `int16_t Size`:
  - 页面队列的当前大小。

### 重写的虚拟成员函数

- `int16_t AddNewPagePtr(PageEntry* PagePtr) override`:
  - 向页面队列中添加新的页面指针。

- `PageEntry* GetReplacePagePtr() override`:
  - 获取将被替换的页面指针。

- `PageEntry* RemoveReplacePagePtr() override`:
  - 移除将被替换的页面指针。

- `void RemovePagePtr(PageEntry* PagePtr) override`:
  - 移除指定的页面指针。

### 公共成员函数

- `void init() override`:
  - 初始化时钟页面选择器。

- `void clear() override`:
  - 清空页面选择器的状态。

- `int16_t size() override`:
  - 返回当前页面队列的大小。

- `void NotifyVisitingPages(PageEntry *PagePtr) override`:
  - 通知访问的页面，使用时钟算法更新访问状态。

- `int16_t CurrentPageUniqueVar() override`:
  - 返回当前页面的唯一变量。

- `bool CheckPageFull() override`:
  - 检查页面队列是否已满。

- `bool CheckPagePtrExist(PageEntry *PagePtr) override`:
  - 检查指定页面指针是否存在。

## 注意事项

- 此类实现了时钟页面替换算法，确保在使用时遵循定义的接口。
- 需要与其他页面替换算法的实现进行配合，以实现完整的页面管理功能。
