/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : VirtualMemorySystem.cpp
#   Last Modified : 2024-10-23 20:38
#   Describe      : 
#
# ====================================================*/

#include "VirtualMemorySystem.h"
#include <cstdint>

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
// Please Modify defines in "CommonHeaders.h" to Change RAM Settings
// Please use init() to initialize MemoryController
void VirtualMemorySystem::init()
{
	pDefaultMemPool = new char[TOTAL_MEMSIZE];
	pMemory = pDefaultMemPool;
	MemorySize = LOCAL_MEMORYSIZE;
	pDiskMemory = pDefaultMemPool + LOCAL_MEMORYSIZE;
	DiskMemorySize = DISK_MEMORYSIZE;

	pSwapBuffer = new char[BCLK_SIZE << 1];

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

void VirtualMemorySystem::MemoryController::InitMC()
{
}

void VirtualMemorySystem::MemoryController::Read(char* pMemPtr_to, char* pMemPtr_Local, size_t Memsize)
	// Local -- Memory In LocalMem
{
	std::memcpy(pMemPtr_to, pMemPtr_Local, Memsize);
}

void VirtualMemorySystem::MemoryController::Write(char* pMemPtr_from, char* pMemPtr_Local, size_t Memsize)
	// Local -- Memory In LocalMem
{
	std::memcpy(pMemPtr_Local, pMemPtr_from, Memsize);
}

void VirtualMemorySystem::MemoryController::SwapBclks(char* pMemPtr_Local, char* pMemPtr_Disk)
{
	int16_t MemID_Local = (pMemPtr_Local-pMemory)>>8;
	int16_t MemID_Disk = (pMemPtr_Disk-pDiskMemory)>>8;
	
	//swap Local and Disk status
	int BitLocal = LocalMemoryUsage[MemID_Local], BitDisk = DiskMemoryUsage[MemID_Disk];
	BitLocal ^= BitDisk;
	BitDisk ^= BitLocal;
	BitLocal ^= BitDisk;
	LocalMemoryUsage[MemID_Local] = BitLocal;
	DiskMemoryUsage[MemID_Disk] = BitDisk;

	//swap LocalMemory and DiskMemory
	for(int i=0;i<BCLK_SIZE;++i)
	{
		*(i+pMemPtr_Local )^=*(i+pMemPtr_Disk);
		*(i+pMemPtr_Disk )^=*(i+pMemPtr_Local);
		*(i+pMemPtr_Local )^=*(i+pMemPtr_Disk);
	}
}

void VirtualMemorySystem::MemoryController::SwapBclks(int16_t MemID_Local, int16_t MemID_Disk)
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

	//swap LocalMemory and DiskMemory
	for(int i=0;i<BCLK_SIZE;++i)
	{
		*(i+pMemPtr_Local )^=*(i+pMemPtr_Disk);
		*(i+pMemPtr_Disk )^=*(i+pMemPtr_Local);
		*(i+pMemPtr_Local )^=*(i+pMemPtr_Disk);
	}
}

int16_t VirtualMemorySystem::MemoryController::AllocDisk()
{
	std :: bitset<(DISK_MEMORYSIZE >> 8)> ReverseBitset = ~ VirtualMemorySystem::DiskMemoryUsage;
	int16_t first_zero;

#if defined(PLATFORM_LINUX)
	first_zero = ReverseBitset._Find_first(); // O(Size/32)
#elif defined(PLATFORM_WIN)
	for(first_zero = 0; !ReverseBitset[first_zero]; ++first_zero); // O(size)
#endif

	return -1;
}

void VirtualMemorySystem::MemoryController::deAllocDiskMem(int16_t MemID_Disk)
{
	if(! VirtualMemorySystem::DiskMemoryUsage[MemID_Disk])
	{
		return; // Not Occupied
	}

	VirtualMemorySystem::DiskMemoryUsage.reset(MemID_Disk);
	std :: memset(VirtualMemorySystem::pDiskMemory+(MemID_Disk<<8),0,256);
}

void VirtualMemorySystem::MemoryController::deAllocLocalMem(int16_t MemID_Local)
{
	if(! VirtualMemorySystem::LocalMemoryUsage[MemID_Local])
	{
		return; // Not Occupied
	}

	VirtualMemorySystem::LocalMemoryUsage.reset(MemID_Local);
	std :: memset(VirtualMemorySystem::pMemory+(MemID_Local<<8),0,256);
}

char* VirtualMemorySystem::MemoryController::GetLocalPhysicalPtr(int16_t MemID_Local)
{
	return pMemory + (MemID_Local << 8);
}

char* VirtualMemorySystem::MemoryController::GetDiskPhysicalPtr(int16_t MemID_Disk)
{
	return pMemory + (MemID_Disk << 8);
}

