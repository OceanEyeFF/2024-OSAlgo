<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : PRAlgoBase.md
   Last Modified : 2024-12-03 00:04
   Describe      : 

--->


# PRAlgoBase.h

## 文件信息

- **版权**: (C) 2024 All rights reserved.
- **作者**: OceanEyeFF
- **邮箱**: fdch00@163.com
- **最后修改日期**: 2024-11-30 16:06

## 描述

该头文件定义了 `PRAlgoBase` 类，作为页面替换算法的基类，提供了页面替换的基本功能和接口。

## 类 `PRAlgoBase`

### 私有成员

- `int PageReplacementCounter`:
  - 页面替换计数器，用于跟踪页面替换的次数。

- `void increasePRCounter()`:
  - 增加页面替换计数器的值。

- `void LOGPrintPRCounter()`:
  - 打印页面替换计数器的值（调试用）。

- `void LOGUsingDefaultFunc()`:
  - 记录使用默认功能的日志。

### 虚拟成员函数

- `virtual int16_t AddNewPagePtr(PageEntry* PagePtr)`:
  - 向记录容器中添加新的页面指针。

- `virtual PageEntry* GetReplacePagePtr()`:
  - 获取将被替换的页面指针。

- `virtual PageEntry* RemoveReplacePagePtr()`:
  - 移除将被替换的页面指针。

- `virtual void RemovePagePtr(PageEntry* PagePtr)`:
  - 移除指定的页面指针。

- `virtual void init()`:
  - 初始化算法。

- `virtual void clear()`:
  - 清空算法状态。

- `virtual int16_t size()`:
  - 返回当前记录容器的大小。

- `virtual void NotifyVisitingPages(PageEntry* PagePtr)`:
  - 通知访问的页面，使用消息总线进行调用。

- `virtual int16_t CurrentPageUniqueVar()`:
  - 返回当前页面的唯一变量。

- `virtual bool CheckPageFull()`:
  - 检查页面是否已满。

- `virtual bool CheckPagePtrExist(PageEntry *PagePtr)`:
  - 检查指定页面指针是否存在。

### 公共成员函数

- `int GetPRCounter()`:
  - 获取当前的页面替换计数器值。

- `void ResetPRCounter()`:
  - 重置页面替换计数器。

- `void SwapPages(PageEntry* PageIn, PageEntry* PageOut)`:
  - 交换两个页面。

- `void SwapReplacedPagesAndSpecifiedPages(PageEntry* PageMoveToMem)`:
  - 交换被替换的页面和指定页面。

- `void PutPageInMem(PageEntry* PageIn)`:
  - 将页面放入内存。

- `void TakeReplacedPageOutofMem()`:
  - 将被替换的页面从内存中移除。

- `void TakePageOutofMem(PageEntry* PageOut)`:
  - 将指定页面从内存中移除。

- `void HandleFuncDeAllocMem(PageEntry* deAllocPage)`:
  - 处理内存去分配的功能。

## 枚举 `EPageAlgoType`

定义了支持的页面替换算法类型：

- `eFIFO`:
  - 先进先出算法。

- `eLRU`:
  - 最近最少使用算法。

- `eClock`:
  - 时钟算法。

- `eImprovedClock`:
  - 改进的时钟算法。

## 命名空间 `PageReplacementAlgoGlobals`

包含页面替换算法的全局变量和设置函数。

- `extern PRAlgoBase* RuntimePageAlgo`:
  - 当前运行的页面替换算法指针。

- `extern EPageAlgoType EPageAlgo`:
  - 当前使用的页面替换算法标志。

- `void SetPageAlgo(EPageAlgoType EType=EPageAlgoType::eImprovedClock)`:
  - 设置页面替换算法类型，默认为改进的时钟算法。

## 注意事项

- 该类为所有页面替换算法的基类，具体算法应继承并实现其虚拟方法。
- 确保在使用页面替换算法时遵循定义的接口和功能。

