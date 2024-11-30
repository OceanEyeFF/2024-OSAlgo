<!---
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : Page.md
#   Last Modified : 2024-10-23 20:55
#   Describe      : 
#
--->

Page.h
====

作为中间件这一段代码只在与内存VMS沟通时使用char*
同时作为中间件在后续为MemInterface设计接口的时候尽量使用AddressPtr
内部的信息复杂地址信息传递使用AddressConj

### struct AddressConj

#### 结构体代码

```c++
struct AddressConj
{
	int8_t innerAddress;
	int8_t PageID;
	int8_t PageContainerID;

	AddressConj();
	~AddressConj();
	AddressConj(AddressPtr ptr);
	AddressPtr ToPtr();
};
```

#### 用途

在内存管理系统内传递地址的结构体
封装了对AddressPtr的解析和生成
占用空间3Byte

#### 函数接口

默认构造和析构函数：
* AddressConj();
* ~AddressConj();

使用AddressPtr的构造函数：
* AddressConj(AddressPtr ptr)

从AddressConj生成AddressPtr的函数
* AddressPtr ToPtr()

------

### Class PageEntry

页信息

#### 类代码

```C++
struct PageEntry
{
	int16_t FrameNumber;
	int16_t PageUniqueVariable; // Algo

	std::bitset<8> STATUSBITS; // 0	Present bits
						  // Below Temporary Unused
						  // 1	Dirty bits
						  // 2	Referenced bit
						  // 3	Protected bit
						  // 4	Read Permision
						  // 5	Write Permision
						  // 6	Execute Permision
						  // 7	Check Bit

	PageEntry(){}
	PageEntry(int FrameNo,int PageVar,bool ispresent):FrameNumber(FrameNo),PageUniqueVariable(PageVar)
	{
		STATUSBITS[0]=ispresent?1:0;
	}

	bool isPresent();
	void setPresent();
	void resetPresent();

	void Alloc();
	void deAlloc();

	char* GetPhysicalPtr();
	// To DO
	//
	void Read(char* Dst);
	void Write(char* Src);
	void Read(char* Dst, size_t size);
	void Write(char* Src, size_t size);
};
```

#### 用途

页面信息类
用做一级页表的子项
在这个类中保存了
1. 状态信息（参考代码注释0-7位分别表示的内容）
2. 对应的内存块编号 FrameNumber
3. 待使用：PageUniqueVariable 提供给页面置换算法使用的变量

#### 类接口

常规构造函数
* PageEntry(){}
* PageEntry(int FrameNo,int PageVar,bool ispresent)

*针对第二条说明函数参数*
|-|-|-|
-----
| FrameNo | PageVar | ispresent |
| 内存块编号 | 页面置换算法变量 | 现在是否在内存中 |


查看、页面对应存储块是否在内存中（将废弃，过度封装）

* bool isPresent();
* void setPresent();
* void resetPresent();


从内存管理器中请求分配内存块（从磁盘分配）
* void Alloc();
默认分配到磁盘中，如需执行读写操作再调入内存


从内存管理器中请求移除内存块的分配（内存、磁盘都可以执行此操作）
* void deAlloc();


获取该内存块可以直接读写的char*
1. 存储块在内存中时返回具体地址，存储块在磁盘中返回nullptr
2. 可能过度封装，需要思考

* char* GetPhysicalPtr();


内存页面的读写函数
* void Read(char* Dst);
* void Write(char* Src);
* void Read(char* Dst, size_t size);
* void Write(char* Src, size_t size);

单参数读写函数：读取默认内存块大小的容量
双参数读写函数：第二个参数size限制读写字节数

----

### Class PageContainer

#### 类代码

```c++
class PageContainer// 一级页表
{
	std :: bitset<32> PagesUsage;
	PageEntry Pages[32];

	private:
		// To Do
		void ExecPageReplacementFunc(int8_t PageID);
	public:
		PageContainer();

		int8_t AllocNewPage();
		void deAllocPage(int8_t Page);

		// To Do
		bool TryVisitPage(int8_t PageID);
		void ForcePresentPage(int8_t PageID);

		char* GetPhysicalPtr(AddressConj AddrConj);
		void Read(AddressConj AddrConj, char* Dst);
		void Write(AddressConj AddrConj, char* Src);

		void Read(AddressConj AddrConj, char* Dst, size_t size);
		void Write(AddressConj AddrConj, char* Src, size_t size);
};

```

#### 用途

一级页表：
在本内存管理器中管理64个页面，一级页表中能够最多同时有十六个存储块在内存中
页表对二级页表开放以下基础接口：
* Alloc|DeAlloc
* Read|Write
同时页表有处理缺页冲突的职责，所以需要增加页面置换算法的接口方法

#### 接口 //由于类还未完全完成所以在完成后补这块工作
