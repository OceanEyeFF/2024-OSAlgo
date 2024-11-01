/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : VirtualMemorySystem.h
#   Last Modified : 2024-10-31 23:11
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _VIRTUALMEMORYSYSTEM_H
#define  _VIRTUALMEMORYSYSTEM_H

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <bitset>
#include <cstring>
#include <mutex>

#include "PageSystemGlobals.h"

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

	void DiskOperationAnalog(); // 模拟延迟

	class MemoryController
	{
		public:
			static uint16_t AllocDiskMem();
			static uint16_t AllocLocalMem();
			static void deAllocDiskMem(uint16_t MemID_Disk);
			static void deAllocLocalMem(uint16_t MemID_Local);

			static void InitMC(); // Temporary Unused
			static void Read(char* pMemPtr_to, uint16_t MemID_Local, size_t MemSize);
			static void Write(char* pMemPtr_from, uint16_t MemID_Local, size_t MemSize);
			static void SwapBclks(char* pMemPtr_Local, char* pMemPtr_Disk); // To be deprecated
			static void SwapBclks(uint16_t MemID_Local, uint16_t MemID_Disk);

			static void Read(char* pMemPtr_to, uint16_t MemID_Local,size_t shift, size_t MemSize);
			static void Write(char* pMemPtr_from, uint16_t MemID_Local,size_t shift,  size_t MemSize);

			static uint16_t MoveToDiskMem(uint16_t MemID_Local);
			static uint16_t MoveToLocalMem(uint16_t MemID_Disk);

			static char* GetLocalPhysicalPtr(uint16_t MemID_Local);
			static char* GetDiskPhysicalPtr(uint16_t MemID_Disk);
			// To Do
			// 代码说明文件
			static uint16_t DiskMemCounter();
			static uint16_t LocalMemCounter();
			static bool DiskMemIsFull();
			static bool LocalMemIsFull();
	};
}

#endif // _VIRTUALMEMORYSYSTEM_H
	   //
	   //
