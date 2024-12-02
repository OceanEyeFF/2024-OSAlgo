<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : StatusTracker.md
   Last Modified : 2024-12-03 00:07
   Describe      : 

--->



# StatusTracker.h

## 文件信息

- **版权**: (C) 2024 All rights reserved.
- **作者**: OceanEyeFF
- **邮箱**: fdch00@163.com
- **最后修改日期**: 2024-11-10 21:59

## 描述

该头文件定义了 `StatusTracker` 类，用于跟踪和记录系统状态的日志信息。

## 类 `StatusTracker`

### 私有成员

- `std::deque<std::string> StatusLog`:
  - 存储状态日志的双端队列，允许高效的插入和删除操作。

- `std::string TrackerDescriber`:
  - 描述跟踪器的字符串，用于提供上下文信息。

- `std::mutex mtx`:
  - 互斥锁，确保在多线程环境中对状态日志的安全访问。

### 公共成员函数

- `int size()`:
  - 返回当前状态日志的大小。

- `void PushLog(std::string status)`:
  - 将新的状态信息推入日志。

- `void PopLog()`:
  - 从日志中移除最新的状态信息。

- `void Clear()`:
  - 清空状态日志。

- `void PrintStatus()`:
  - 打印当前状态日志到控制台。

- `void PrintStatusToLog()`:
  - 将当前状态日志打印到日志系统中。

- `void SetDescriber(std::string Describer)`:
  - 设置跟踪器的描述信息。

## 注意事项

- 此类适用于需要记录和跟踪系统状态的场景，确保在多线程环境中安全使用。
- 需要包含相应的日志库以支持 `PrintStatusToLog` 函数的实现。
