<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : main.md
   Last Modified : 2024-12-03 01:02
   Describe      : 

--->



# main.cpp

## 文件信息

- **版权**: (C) 2024 All rights reserved.
- **作者**: OceanEyeFF
- **邮箱**: fdch00@163.com
- **最后修改日期**: 2024-11-30 02:22

## 描述

该文件是程序的主入口，负责初始化虚拟内存系统、处理命令行参数、运行测试和任务。

## 函数

### `RunTest()`

测试功能，主要包括以下几个部分：
1. 创建两个进程控制块（PCB），分别为 `TestPCB_A` 和 `TestPCB_B`。
2. 进行内存分配、读取和写入的标准操作测试。
3. 验证多 PCB 下的内存页面置换。
4. 检查内存页面置换后缓存页面的有效性。
5. 获取物理内存地址并验证物理内存的块排布是否正确。

### `SubTask(const std::string& instructionstr)`

处理每个输入指令，执行相应的内存操作（分配、读取、写入、释放），并返回结果。

### `RunTask()`

负责读取输入文件、执行指令并将结果写入输出文件，同时计算执行时间和触发的缺页中断次数。

### `main(int argc, char* argv[])`

程序入口函数：
- 解析命令行参数以确定页面算法类型（FIFO、LRU、CLOCK、IMPROVEDCLOCK）。
- 初始化日志记录和虚拟内存系统。
- 根据调试模式选择运行测试或任务。

## 全局变量

- `bool cmp`:
  - 用于检查是否已设置算法类型。

- `EPageAlgoType EAlgoType`:
  - 当前使用的页面替换算法类型。

- `char* AlgoTypeStr`:
  - 存储算法类型的字符串。

- `PCB_MemInterface PCBpool[256]`:
  - 存储 PCB 内存接口的数组。

## 注意事项

- 代码中包含调试和日志记录功能，根据编译选项启用或禁用。
- 确保在生产环境中使用适当的配置文件。
- 在 `RunTest()` 中的测试用例可以帮助验证系统的基本功能和稳定性。
