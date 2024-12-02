<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : README.md
   Last Modified : 2024-12-01 23:53
   Describe      : 

--->

# 2024-OSAlgo
2024 华南理工操作系统实验 杨班作业

## 简要任务说明

0. 系统环境 LINUX
1. 搭建一个能够模拟内存缓存的框架系统
	* 基础四项操作（开辟删除、读写）
	* PRAlgo的接口实现基础要求
	* 支持内存块操作
	* 系统：固定分配局部替换策略
2. 实现FIFO，LRU，CLOCK，IMPROVEDCLOCK算法
3. 设计多组实验数据，进行多次测试，统计分析和比较算法的性能

## 本项目实现功能

1. 搭建一个能够模拟内存缓存的框架系统
	- [x] 基础四项操作（开辟删除、读写）
	- [x] PRAlgo的接口实现基础要求
	- [ ] 支持内存块操作
	- [x] 系统：固定分配局部替换策略
2. 实现FIFO，LRU，CLOCK，IMPROVEDCLOCK算法
	- [x] FIFO
	- [x] LRU
	- [x] CLOCK
	- [x] IMPROVEDCLOCK
3. 设计多组实验数据，进行多次测试，统计分析和比较算法的性能
	- [x] 随机化内存操作序列生成器
	- [x] 方便快捷的统计分析文件

## 如何使用本项目

### 克隆本项目

```bash
git clone https://github.com/OceanEyeFF/2024-OSAlgo.git
```
或者
```bash
git clone git@github.com:OceanEyeFF/2024-OSAlgo.git
```

### 生成makefile文件/sln项目

#### Linux

1. 确保已经有了一个最基本的C++编译环境
```bash
sudo apt install cmake gcc g++ make
```
2. 在项目的根目录打开命令行
```bash
mkdir ./bin
cd ./bin
cmake ..

make
```
3. 可执行文件在 ./bin/source 路径下

#### Windows

1. 确保已经安装了Visual Studio和CMake
2. 生成.sln项目文件
```powershell
mkdir ./bin
cd ./bin
cmake .. -D DISABLE_HOOK=ON

./2024-OS.sln
```
也可以使用图形化CMake打开，记得打开DISABLE_HOOK开关

## 文件夹

* Ideas 存放思路和资料文档
* source 存放代码文件
	* /public			头文件
	* /private			代码文件
	* /main .cpp		主函数入口代码文件
	* /thirdparty		第三方库文件
	* /documents		注释文档文件
	* /Test				库测试代码
	* /TestGenerator	样例生成器代码
* Task 存放任务书
* ToolKit 存放项目相关小工具
	* /RunAndGrade		提供的运行测试脚本
	* /ConfigFile		配套easylog++的日志生成配置
