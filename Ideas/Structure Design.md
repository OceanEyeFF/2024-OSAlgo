<!--
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : Structure Design.md
   Last Modified : 2024-12-02 21:35
   Describe      : 

-->

实验软件架构设计
====

实验内存系统架构我们根据需求进行模块化：
1. 内存管理器端，用于实现不同类型的页面替换算法
2. PCB中间层，存储实际指针数据，提前过滤无效操作
3. 主函数

------

### 内存管理器端架构

#### 架构图

![](https://markdown-document-1253470282.cos.ap-guangzhou.myqcloud.com/2024OS内存管理器端.jpg)

#### 内存与虚拟内存管理器

使用char*模拟内存块
默认内存大小为65536B
默认磁盘大小为262144B
默认存储单元大小为8位256B

*通常现代操作系统中的存储单元大小为12位4096B*

```C++
namespace VirtualSystemMemoryController
{
	char* pMemory;
	char* pDiskMemory;
}
```

同时编写一个内存管理器，能够做到
1. 读写内存(Alloc DeAlloc/Free)
2. 交换指定的内存和虚拟内存
3. *Extend:支持内存区块的有保护的多线程读写、内存的区间读写*

```C++
namespace VirtualSystemMemoryAllocator
{
	class MemoryController
	{
		private:
		public:
			Alloc();
			DeAlloc();
			Swap();
        	Read();
        	Write();
	};
}
```

#### 页面管理逻辑

内存地址编码如下：
16位地址 =  块内地址8位 + 二级页表6位 + 一级页表2位

**设置内存大小为16384B，缓存大小为16384B*3 = 49152B **
1. 每一个页(Page)有其对应的存储块结构(MemBclk)，一个存储块结构存储256B的数据
2. 一级页表(PageContainer)中最多有64个一级页表
3. 由4个一级页表组成二级页表
4. 存储空间中平均能够给每个一级页表16个可用MemBclk

***
块：256B
二级页表块数量：64
二级页表内存内块数量；16
一级页表数量：4
***

##### ePageAlgo

```C++
enum class EPageAlgoType
{
	eFIFO,
	eLRU,
	eClock,
	eImprovedClock
};
```

##### PageEntry 页

考虑设计一个多算法泛用的Page，并且支持在Page基类上进行派生
他的基础结构应该要具有最基本的内存地址指针和页换出算法所使用的标识

```C++
Class PageUnitBase
{
	AddressPtr pMemBclkPtr;
	unsigned short int PageUniqueVariable;
	bool present;
	
	PageUnitBase();
	~PageUnitBase();
};
```

##### PageContainer 二级页表

页面算法的容器，需要支持的基本功能有
1. 容器的基本功能（增删改查）
2. 在PageContainer初始化阶段可以选择缺页换页算法
3. 维护在内存和在磁盘中的页面信息

为了使架构简单易懂，考虑使用函数指针来实现PageContainer的缺页算法
*进一步如果需要优化算法可能考虑页表的内存区域容量拓展算法*

##### 页面替换算法设计

页面处理算法文档：ToDo OE

##### AddressPtr和AddressConj

地址指针和地址联合体
地址指针类型全局可用
地址联合体是用于解析地址指针到每一个层级的变量

* 总内存大小是32768B，虚拟内存大小是98304B
* 地址指针有16位，8位页内地址，5位页码，3位二级页码
* AddressConj是页面操作的主要载体

```C++

struct AddressPtr
{
	int16_t __ptr__;
};

struct AddressConj
{
	int8_t innerAddress;
	int8_t PageID;
	int8_t PageContainerID;
};

```

#### 一级页表 TO DO OE

实现的方法
* std :: vector<PageContainer>
* class Page[a-z]*
*``` <template typename T> class Container<T>```

*考虑多线程设计*

### 虚拟内存环境对外接口

虚拟内存环境需要设计以下的基础接口：

```C++
	TReport();
	TAllocate();
	TDeAllocate();
	TUsage();
	TFreeSize();
	TSetPrivilege
```

