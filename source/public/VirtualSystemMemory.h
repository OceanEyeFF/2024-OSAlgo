/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : VirtualSystemMemory.h
#   Last Modified : 2024-10-21 15:48
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _VIRTUALSYSTEMMEMORY_H
#define  _VIRTUALSYSTEMMEMORY_H

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <bitset>
#include <functional>

#include "CommonHeaders.h"
#include "Page.h"

namespace VirtualSystemMemory
{
	extern char* pDefaultMemPool;
	extern char* pMemory;
	extern char* pDiskMemory;
	extern int32_t MemorySize;
	extern int32_t DiskMemorySize;
	void init();
	void release();

	class MemoryController
	{
		private:
			std::bitset<(LOCAL_MEMORYSIZE>>8) > LocalMemoryUsage;
			std::bitset<(DISK_MEMORYSIZE>>8) > DiskMemoryUsage;
		public:
			void Read(char* MemPtr_to, char* MemPtr_Local, size_t MemSize);
			void Write(char* MemPtr_from, char* MemPtr_Local, size_t MemSize);
			void SwapBclks(char* MemPtr_Local, char* MemPtr_Disk);
	};

	class MemoryAddressConverter
	{
		public:
			static char* ToPhysicalAddress();
			static AddressPtr ToAddressPtr();
	};
}


#endif // _VIRTUALSYSTEMMEMORY_H
	   //
	   //
