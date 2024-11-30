<!---
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : VirtualMemorySystem.md
#   Last Modified : 2024-10-23 20:53
#   Describe      : 
#
--->

VirtualMemorySystem.h
==========

### namespace VirtualMemorySystem

设计逻辑上这一块的所有的与内存和缓存读写相关的操作都通过char*来传递
主要的目的是让模拟硬件层和系统内核层变成两个相对独立的体系

#### 代码

```c++

namespace VirtualMemorySystem
{
	extern char* pDefaultMemPool;
	extern char* pMemory;
	extern char* pDiskMemory;
	extern char* pSwapBuffer;

	extern int32_t MemorySize;
	extern int32_t DiskMemorySize;

	extern std::bitset<(LOCAL_MEMORYSIZE>>8) > LocalMemoryUsage;
	extern std::bitset<(DISK_MEMORYSIZE>>8) > DiskMemoryUsage;

	extern std::mutex MemMutex; // unused
	extern std::mutex DiskMutex;// unused

	void init();
	void release();

	void DiskWritingAnalog(); // 模拟延迟

	class MemoryController // 下文中独立描述
	{
	};
}
```

#### 功能
内存管理系统的区域封装（防止非法访问）

#### 接口

模拟内存启动
* void init()

模拟清空内存
* void release()

模拟读写延迟
* void DiskOperationAnalog()


### class MemoryController

#### 代码
```c++
	class MemoryController
	{
		public:
			static void InitMC(); // Temporary Unused
			static void Read(char* MemPtr_to, char* MemPtr_Local, size_t MemSize);
			static void Write(char* MemPtr_from, char* MemPtr_Local, size_t MemSize);
			static void SwapBclks(char* MemPtr_Local, char* MemPtr_Disk);
			static void SwapBclks(int16_t MemID_Local, int16_t MemID_Disk);

			static int16_t AllocDisk();
			static void deAllocDiskMem(int16_t MemID_Disk);
			static void deAllocLocalMem(int16_t MemID_Local);

			// To Do
			static char* GetLocalPhysicalPtr(int16_t MemID_Local);
			static char* GetDiskPhysicalPtr(int16_t MemID_Disk);
			// To Do
			// 代码说明文件
	};
```

#### 功能

封装内存控制器操作代码，提升代码可读性

#### 接口

基础操作：存储块的读写，硬盘缓存和内存的交换（用于页面交换算法）
* static void Read(char* MemPtr_to, char* MemPtr_Local, size_t MemSize);
* static void Write(char* MemPtr_from, char* MemPtr_Local, size_t MemSize);
* static void SwapBclks(char* MemPtr_Local, char* MemPtr_Disk);
* static void SwapBclks(int16_t MemID_Local, int16_t MemID_Disk);

基础操作：标记某一内存块为被占用（Alloc），释放某一内存块（deAlloc）
* static int16_t AllocDisk();
* static void deAllocDiskMem(int16_t MemID_Disk);
* static void deAllocLocalMem(int16_t MemID_Local);

转换函数：将内存块编号转化为对应的char*地址
* static char* GetLocalPhysicalPtr(int16_t MemID_Local);
* static char* GetDiskPhysicalPtr(int16_t MemID_Disk);
