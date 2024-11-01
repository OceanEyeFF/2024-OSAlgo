/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : VirtualMemorySystem.cpp
#   Last Modified : 2024-10-31 23:14
#   Describe      : 
#
# ====================================================*/

#include <cstring>
#include <cstdint>
#include "VirtualMemorySystem.h"
#include "MyAlgo.hpp"

namespace VirtualMemorySystem
{
	char* pDefaultMemPool;
	char* pMemory;
	char* pDiskMemory;
	char* pSwapBuffer;
	int32_t MemorySize;
	int32_t DiskMemorySize;
	std::bitset<(LOCAL_MEMORYSIZE>>8) > LocalMemoryUsage;
	std::bitset<(DISK_MEMORYSIZE>>8) > DiskMemoryUsage;

	// temporary unused
	std::mutex MemMutex;
	std::mutex DiskMutex;
}

// 内存基础管理部分
// If you use default memory settings
// Please Modify defines in "PageSystemGlobals.h" to Change RAM Settings
// Please use init() to initialize MemoryController
void VirtualMemorySystem::init()
{
	pDefaultMemPool = new char[TOTAL_MEMSIZE];
	pMemory = pDefaultMemPool;
	MemorySize = LOCAL_MEMORYSIZE;
	pDiskMemory = pDefaultMemPool + LOCAL_MEMORYSIZE;
	DiskMemorySize = DISK_MEMORYSIZE;

	pSwapBuffer = new char[BLCK_SIZE << 1];

	LocalMemoryUsage.reset();
	DiskMemoryUsage.reset();
}

void VirtualMemorySystem::release()
{
	pMemory = nullptr;
	pDiskMemory = nullptr;
	delete[] pDefaultMemPool;
	delete[] pSwapBuffer;
}

void VirtualMemorySystem::DiskOperationAnalog()
{
#if defined(PLATFORM_LINUX)
	usleep(5000);	// 5ms
#elif defined(PLATFORM_WIN)
	Sleep(5);		// 5ms
#endif
}

// MemController
// 内存控制器代码实现
//
uint16_t VirtualMemorySystem::MemoryController::AllocLocalMem()
{
	uint16_t first_zero;

#if defined(PLATFORM_LINUX)
	std :: bitset<(LOCAL_MEMORYSIZE >> 8)> ReverseBitset = ~ VirtualMemorySystem::LocalMemoryUsage;
	first_zero = ReverseBitset._Find_first(); // O(Size/32)
											  // GNU C++ does not provide a function
											  // to find firsr zero
											  // GNU C++ 的bitset头文件中没有用于
											  // 寻找第一个0位的函数
											  // 其他类似情形同理
#elif defined(PLATFORM_WIN)
	first_zero = MyAlgo::ForBitset::FindFirstZero(VirtualMemorySystem::LocalMemoryUsage); // O(Size/16 + 16)
	//for(first_zero = 0; !ReverseBitset[first_zero]; ++first_zero); // O(size)
#endif

	std :: memset(VirtualMemorySystem::pMemory+(first_zero<<8),0,256);
	return first_zero;
	return -1;
}

uint16_t VirtualMemorySystem::MemoryController::AllocDiskMem()
{
	uint16_t first_zero;

#if defined(PLATFORM_LINUX)
	std :: bitset<(DISK_MEMORYSIZE >> 8)> ReverseBitset = ~ VirtualMemorySystem::DiskMemoryUsage;
	first_zero = ReverseBitset._Find_first(); // O(Size/32)
											  // GNU C++ does not provide a function
											  // to find firsr zero
											  // GNU C++ 的bitset头文件中没有用于
											  // 寻找第一个0位的函数
											  // 其他类似情形同理
#elif defined(PLATFORM_WIN)
	first_zero = MyAlgo::ForBitset::FindFirstZero(VirtualMemorySystem::DiskMemoryUsage); // O(Size/16 + 16)
	//for(first_zero = 0; !ReverseBitset[first_zero]; ++first_zero); // O(size)
#endif

	std :: memset(VirtualMemorySystem::pDiskMemory+(first_zero<<8),0,256);
	return first_zero;
	return -1;
}

void VirtualMemorySystem::MemoryController::deAllocDiskMem(uint16_t MemID_Disk)
{
	if(! VirtualMemorySystem::DiskMemoryUsage[MemID_Disk])
	{
		return; // Not Occupied
	}

	VirtualMemorySystem::DiskMemoryUsage.reset(MemID_Disk);
	std :: memset(VirtualMemorySystem::pDiskMemory+(MemID_Disk<<8),0,256);
}

void VirtualMemorySystem::MemoryController::deAllocLocalMem(uint16_t MemID_Local)
{
	if(! VirtualMemorySystem::LocalMemoryUsage[MemID_Local])
	{
		return; // Not Occupied
	}

	VirtualMemorySystem::LocalMemoryUsage.reset(MemID_Local);
	std :: memset(VirtualMemorySystem::pMemory+(MemID_Local<<8),0,256);
}

void VirtualMemorySystem::MemoryController::InitMC()
{
}

void VirtualMemorySystem::MemoryController::Read(char* pMemPtr_to, uint16_t MemID_Local, size_t Memsize)
	// Local -- Memory In LocalMem
{
	char* pMemPtr_Local = pMemory + (MemID_Local<<8);
	std::memcpy(pMemPtr_to, pMemPtr_Local, Memsize);
}

void VirtualMemorySystem::MemoryController::Write(char* pMemPtr_from, uint16_t MemID_Local, size_t Memsize)
	// Local -- Memory In LocalMem
{
	char* pMemPtr_Local = pMemory + (MemID_Local<<8);
	std::memcpy(pMemPtr_Local, pMemPtr_from, Memsize);
}

void VirtualMemorySystem::MemoryController::Read(char* pMemPtr_to, uint16_t MemID_Local,size_t shift, size_t Memsize)
	// Local -- Memory In LocalMem
{
	char* pMemPtr_Local = pMemory + (MemID_Local<<8) + shift;
	std::memcpy(pMemPtr_to, pMemPtr_Local, Memsize);
}

void VirtualMemorySystem::MemoryController::Write(char* pMemPtr_from, uint16_t MemID_Local,size_t shift, size_t Memsize)
	// Local -- Memory In LocalMem
{
	char* pMemPtr_Local = pMemory + (MemID_Local<<8) + shift;
	std::memcpy(pMemPtr_Local, pMemPtr_from, Memsize);
}


void VirtualMemorySystem::MemoryController::SwapBclks(uint16_t MemID_Local, uint16_t MemID_Disk)
{
	char* pMemPtr_Local = pMemory + (MemID_Local<<8);
	char* pMemPtr_Disk = pDiskMemory + (MemID_Disk<<8);

	//swap Local and Disk status
	int BitLocal = LocalMemoryUsage[MemID_Local], BitDisk = DiskMemoryUsage[MemID_Disk];
	BitLocal ^= BitDisk;
	BitDisk ^= BitLocal;
	BitLocal ^= BitDisk;
	LocalMemoryUsage[MemID_Local] = BitLocal;
	DiskMemoryUsage[MemID_Disk] = BitDisk;

	// fast swap LocalMemory and DiskMemory
	/*
	for(int i=0;i<BLCK_SIZE;++i)
	{
		*(i+pMemPtr_Local )^=*(i+pMemPtr_Disk);
		*(i+pMemPtr_Disk )^=*(i+pMemPtr_Local);
		*(i+pMemPtr_Local )^=*(i+pMemPtr_Disk);
	}
	*/

	// if simulate hardware operation
	// copy to swapbuffer
	std :: memcpy(VirtualMemorySystem::pSwapBuffer,pMemPtr_Local,BLCK_SIZE);
	std :: memcpy(VirtualMemorySystem::pSwapBuffer+BLCK_SIZE,pMemPtr_Disk,BLCK_SIZE);
	// from swapbuffer copy to Mem and DiskMem
	std :: memcpy(pMemPtr_Disk,VirtualMemorySystem::pSwapBuffer,BLCK_SIZE);
	std :: memcpy(pMemPtr_Local,VirtualMemorySystem::pSwapBuffer+BLCK_SIZE,BLCK_SIZE);
}

uint16_t VirtualMemorySystem::MemoryController::MoveToDiskMem(uint16_t MemID_Local)
{
	if(VirtualMemorySystem::DiskMemoryUsage.count() == (DISK_MEMORYSIZE>>8) )
	{
		return 0xffff;
	}
	uint16_t MemID_Disk=AllocDiskMem();
	char* pMemPtr_Local = pMemory + (MemID_Local<<8);
	char* pMemPtr_Disk = pDiskMemory + (MemID_Disk<<8);

	std :: memcpy(pMemPtr_Disk, pMemPtr_Local, BLCK_SIZE);
	std :: memset(pMemPtr_Local, 0,BLCK_SIZE);
	return MemID_Disk;
}

uint16_t VirtualMemorySystem::MemoryController::MoveToLocalMem(uint16_t MemID_Disk)
{
	if(VirtualMemorySystem::LocalMemoryUsage.count() == (LOCAL_MEMORYSIZE>>8) )
	{
		return 0xffff;
	}
	uint16_t MemID_Local=AllocDiskMem();
	char* pMemPtr_Local = pMemory + (MemID_Local<<8);
	char* pMemPtr_Disk = pDiskMemory + (MemID_Disk<<8);

	std :: memcpy(pMemPtr_Local, pMemPtr_Disk,BLCK_SIZE);
	std :: memset(pMemPtr_Disk, 0,BLCK_SIZE);
	return MemID_Local;
}

char* VirtualMemorySystem::MemoryController::GetLocalPhysicalPtr(uint16_t MemID_Local)
{
	return pMemory + (MemID_Local << 8);
}

char* VirtualMemorySystem::MemoryController::GetDiskPhysicalPtr(uint16_t MemID_Disk)
{
	return pMemory + (MemID_Disk << 8);
}
