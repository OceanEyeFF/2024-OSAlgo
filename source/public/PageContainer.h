/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PageContainer.h
#   Last Modified : 2024-10-31 23:00
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _PAGECONTAINER_H
#define  _PAGECONTAINER_H

#include <bitset>
#include <cstdint>
#include "VirtualMemorySystem.h"
#include "PageSystemGlobals.h"
#include "PageEntry.h"
#include "PRAlgo.h"
		// Not Ready : LRU
		// Not Ready : Clock
		// Not Ready : Improved Clock
// void PageReplacementAlgo( std :: function<void(char*)> PRAfunc , char* MemPtr);
// void FIFO(char* MemPtr);

extern EPageAlgoType EPageAlgo;
extern void SetPageAlgo(int32_t type);
extern void SetPageAlgo(EPageAlgoType type);

class PageContainer// 一级页表
				   // 144 Bytes
				   //
{
	std :: bitset<64> PagesUsage;		// 8Byte
	PageEntry Pages[64];				// 128Byte
	PRAlgoBase* PageReplacementUnit;	// 8Byte
										// 这一个字段在实际操作系统中是固定空间
										// PageAlgo 的实现和空间占用在对应头文件和
										// 代码注释文件中

	private:
		// ToDo
		void HandlePageContainerMissingPage(int8_t PageID);
		void HandlePageContainerIllegalAccess(int8_t PageID); // ToDo
		bool GetPageStatus();
	public:
		// ToDo
		PageContainer();

		int8_t AllocNewPage();
		void deAllocPage(int8_t Page);

		void Read(AddressConj AddrConj, char* Dst);
		void Write(AddressConj AddrConj, char* Src);

		void Read(AddressConj AddrConj, char* Dst, size_t size);
		void Write(AddressConj AddrConj, char* Src, size_t size);

		char* GetPhysicalPtr(AddressConj AddrConj);

		// DEBUG
		// ToDo
		void CheckPageEntryStatus(int8_t PageID);

};

#endif // _PAGECONTAINER_H
	   //
	   //
