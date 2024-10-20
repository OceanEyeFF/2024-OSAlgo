/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : VirtualSystemMemory.h
#   Last Modified : 2024-10-20 19:52
#   Describe      : 
#
# ====================================================*/

#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#ifndef  _VIRTUALSYSTEMMEMORY_H
#define  _VIRTUALSYSTEMMEMORY_H

namespace VirtualSystemMemory
{
	char* pDefaultMemPool;
	char* pMemory;
	char* pDiskMemory;
	void init();
	void release();

	enum class EPageAlgoType
	{
		eFIFO,
		eLRU,
		eClock,
		eImprovedClock
	};
	EPageAlgoType PageAlgo;
	void SetPageAlgo(int32_t type);

	class MemoryController
	{
		private: 
			void PageReplacementAlgo( std :: function<void(char*)> PRAfunc , char* MemPtr);
			void FIFO(char* MemPtr);
		public:
			char* Allocate(size_t MemSize);
			int32_t DeAllocate(char* MemPtr);
			bool TryVisit(char* MemPtr);
			int32_t Visit(char* MemPtr);
	};
}

#endif // _VIRTUALSYSTEMMEMORY_H
	   //
	   //
