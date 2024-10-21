/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : VirtualSystemMemory.cpp
#   Last Modified : 2024-10-21 15:48
#   Describe      : 
#
# ====================================================*/

#include "VirtualSystemMemory.h"

namespace VirtualSystemMemory
{
	char* pDefaultMemPool;
	char* pMemory;
	char* pDiskMemory;
	int32_t MemorySize;
	int32_t DiskMemorySize;
}

// 内存基础管理部分
// If you use default memory settings
// Please Modify defines in "CommonHeaders.h" to Change RAM Settings
// Please use init() to initialize MemoryController
void VirtualSystemMemory::init()
{
	pDefaultMemPool = new char[TOTAL_MEMSIZE];
	pMemory = pDefaultMemPool;
	MemorySize = LOCAL_MEMORYSIZE;
	pDiskMemory = pDefaultMemPool + LOCAL_MEMORYSIZE;
	DiskMemorySize = DISK_MEMORYSIZE;
}

void VirtualSystemMemory::release()
{
	pMemory = nullptr;
	pDiskMemory = nullptr;
	delete[] pDefaultMemPool;
}

// MemController
// 内存控制器代码实现

void VirtualSystemMemory::MemoryController::Read(char* MemPtr_to, char* MemPtr_Local, size_t Memsize)
{
}

void VirtualSystemMemory::MemoryController::Write(char* MemPtr_from, char* MemPtr_Local, size_t Memsize)
{
}

void VirtualSystemMemory::MemoryController::SwapBclks(char* MemPtr_Local, char* MemPtr_Disk)
{
}
