/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : VirtualMemorySystem.h
#   Last Modified : 2024-10-23 20:49
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

#include "CommonHeaders.h"

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
			static void InitMC(); // Temporary Unused
			static void Read(char* MemPtr_to, char* MemPtr_Local, size_t MemSize);
			static void Write(char* MemPtr_from, char* MemPtr_Local, size_t MemSize);
			static void SwapBclks(char* MemPtr_Local, char* MemPtr_Disk);
			static void SwapBclks(int16_t MemID_Local, int16_t MemID_Disk);

			static int16_t AllocDisk();
			static void deAllocDiskMem(int16_t MemID_Disk);
			static void deAllocLocalMem(int16_t MemID_Local);

			static char* GetLocalPhysicalPtr(int16_t MemID_Local);
			static char* GetDiskPhysicalPtr(int16_t MemID_Disk);
			// To Do
			// 代码说明文件
	};
}

#endif // _VIRTUALMEMORYSYSTEM_H
	   //
	   //