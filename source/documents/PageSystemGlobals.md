<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : PageSystemGlobals.md
   Last Modified : 2024-12-03 00:03
   Describe      : 

--->



# PageSystemGlobals.h

## 文件信息

- **版权**: (C) 2024 All rights reserved.
- **作者**: OceanEyeFF
- **邮箱**: fdch00@163.com
- **最后修改日期**: 2024-11-28 23:39

## 描述

该头文件定义了与页面系统相关的全局常量、结构体和状态跟踪器接口，主要用于内存管理和地址转换。

## 常量定义

- `TOTAL_MEMSIZE`: 总内存大小，327680字节。
- `LOCAL_MEMORYSIZE`: 本地内存大小，65536字节。
- `DISK_MEMORYSIZE`: 磁盘内存大小，262144字节。
- `BLCK_SIZE`: 块大小，256字节。
- `BLCK_CNT`: 块数量，256个。
- `PAGE_PER_CONTAINER`: 每个容器的页面数，64页。
- `CONTAINER_SIZE`: 容器的大小，4。

- `FSTPAGE_BITS`: 一级页面位数，2位。
- `SECPAGE_BITS`: 二级页面位数，6位。
- `BLCK_BITS`: 块位数，8位。
- `THIRDLEVEL_BITS`: 第三级位数，8位。

- `FIRST_LEVEL_MASK`: 一级掩码，3。
- `SECOND_LEVEL_MASK`: 二级掩码，63。
- `THIRD_LEVEL_MASK`: 三级掩码，255。

- `FIRST_LEVEL_SHIFT`: 一级偏移量，14。
- `SECOND_LEVEL_SHIFT`: 二级偏移量，8。
- `THIRD_LEVEL_SHIFT`: 三级偏移量，0。

## 结构体

### `AddressPtr`

- `uint16_t __ptr__`:
  - 16位地址指针，表示内存地址。

### `AddressConj`

表示内存地址转换的结构体。

- `int8_t innerAddress`:
  - 内部块ID。

- `int8_t PageID`:
  - 页面ID。

- `int8_t PageContainerID`:
  - 页面容器ID。

#### 方法

- `AddressConj()`:
  - 默认构造函数。

- `AddressConj(AddressPtr ptr)`:
  - 从 `AddressPtr` 构造。

- `AddressConj(int8_t __PageContainerID, int8_t __PageID, int8_t __innerAddress)`:
  - 根据页面容器ID、页面ID和内部地址构造。

- `AddressPtr ToPtr()`:
  - 将 `AddressConj` 转换为 `AddressPtr`。

## 命名空间 `SystemTracker`

包含状态跟踪器的相关功能。

- `extern StatusTracker Tracker`:
  - 状态跟踪器实例。

- `void RegistMessageBus()`:
  - 注册消息总线。

- `void CallLog(std::string CLASSNAME, std::string LOG="")`:
  - 记录日志。

- `void RemoveAllLog()`:
  - 移除所有日志。

- `void RemoveLog()`:
  - 移除当前日志。

- `void FlushTracker()`:
  - 刷新跟踪器。

## 注意事项

- 此文件定义的结构体和常量用于页面管理和地址转换，确保在使用时遵循定义的数据结构。
