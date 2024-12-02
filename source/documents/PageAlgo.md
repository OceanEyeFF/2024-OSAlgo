<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : PageAlgo.md
   Last Modified : 2024-12-03 00:04
   Describe      : 

--->



# PRAlgo.h

## 文件信息

- **版权**: (C) 2024 All rights reserved.
- **作者**: OceanEyeFF
- **邮箱**: fdch00@163.com
- **最后修改日期**: 2024-11-20 23:05

## 描述

该头文件包含了页面替换算法相关的类和接口定义，提供了不同的页面替换策略的基础。

## 包含的头文件

- `PRAlgoBase.h`:
  - 页面替换算法的基类，定义了基本接口和功能。

- `PRAlgoFIFO.h`:
  - 先进先出（FIFO）页面替换算法的实现。

- `PRAlgoLRU.h`:
  - 最近最少使用（LRU）页面替换算法的实现。

- `PRAlgoCLOCK.h`:
  - 时钟页面替换算法的实现。

- `PRAlgoIMPROVEDCLOCK.h`:
  - 改进的时钟页面替换算法的实现。

## 注意事项

- 此文件作为页面替换算法的集合，确保在实现和使用时遵循相关算法的特性和要求。
