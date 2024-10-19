<!--
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : Structure Design.md
   Last Modified : 2024-10-20 02:17
   Describe      : 

-->

实验软件架构设计
====

实验内存系统架构我们根据需求进行模块化：
1. 内存管理器端，用于实现不同类型的页面替换算法
2. 主函数端，用于处理和样例文件和测试文件的交互

内存管理器端的进一步模块化会在下面进行。
主函数的进一步模块化 **TO DO (OE) **

------

### 内存管理器端架构

#### 架构图

![image-20241020021502638](https://s2.loli.net/2024/10/20/eY2SQ6FqgA41J8n.png)

#### 全局变量

#### 内存与虚拟内存管理器

使用char*模拟内存块

```C++
namespace VirtualSystemMemoryAllocator
{
	char* pMemory;
	char* pDiskMemory;
}
```

同时编写一个内存管理器，能够做到
1. 分配内存，和释放内存(Alloc DeAlloc/Free)
2. 输入一个指针能够区分是内存指针还是虚拟内存指针
3. 能够执行页面交换算法
4. 能够根据Enum EPageAlgo来设置使用的页面交换算法

**To do OE**
```C++
namespace VirtualSystemMemoryAllocator
{
	class MemoryController
	{
		private:
		public:
	};
}
```

#### ePageAlgo

**C++ 11 支持使用enum class **

```C++
enum class EPageAlgoType
{
	eFIFO,
	eLRU,
	eClock,
	eInprovedClock
};
```

#### Page 页

考虑设计一个多算法泛用的Page，并且支持在Page基类上进行派生
他的基础结构应该要具有最基本的内存地址指针和页换出算法所使用的标识

```C++
Class PageUnitBase
{
	char* pMemBclkPtr;
	unsigned short int PageUniqueVariable;
	
	PageUnitBase();
	~PageUnitBase();
};
```

#### PageContainer 页表

页面算法的容器，需要支持的基本功能有
1. 容器的功能
2. 在PageContainer初始化阶段可以选择缺页换页算法
3. 插入页
4. 取消指定  页的占用 

为了使架构简单易懂，考虑使用函数指针来实现PageContainer的
1. 插入页
2. 删除页
3. 寻找符合要求的交换页的函数
4. 针对高频次触发页面交换的页表进行容量拓展

#### 二级页表 TO DO OE

#### 虚拟内存环境对外接口

虚拟内存环境需要设计以下的基础接口：

```C++
	TReport();
	TAllocate();
	TDeAllocate();
	TUsage();
	TFreeSize();
	TSetPrivilege
```

### 页面替换算法设计

