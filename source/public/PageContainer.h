/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PageContainer.h
#   Last Modified : 2024-11-03 11:07
#   Describe      : 
#
# ====================================================*/

#pragma once

#include "PRAlgoBase.h"
#ifndef  _PAGECONTAINER_H
#define  _PAGECONTAINER_H

#include <bitset>
#include <cstdint>
#include <string_view>
#include "VirtualMemorySystem.h"
#include "PageSystemGlobals.h"
#include "PageEntry.h"
#include "PRAlgo.h"
		// Not Ready : LRU
		// Not Ready : Clock
		// Not Ready : Improved Clock
// void PageReplacementAlgo( std :: function<void(char*)> PRAfunc , char* MemPtr);
// void FIFO(char* MemPtr);

extern PRAlgoBase* PageReplacementAlgoGlobals::RuntimePageAlgo;

class PageContainer// 一级页表
				   // 144 Bytes
				   //
{
	std :: bitset<64> PagesUsage;		// 8Byte
										// 表示页面是否已经开辟
										// 如果已经开辟则可以进行操作（从磁盘移入内存等）
	PageEntry Pages[64];				// 128Byte
//	PRAlgoBase* PageReplacementUnit;	// 8Byte Deprecated
										// Replaced By Global Variable
										// 实际指向全局PageReplacemenUnit
										// 这一个字段在实际操作系统中是固定空间
										// PageAlgo 的实现和空间占用在对应头文件和
										// 代码注释文件中

	private:
		void HandlePageContainerMissingPage(int8_t PageID);
		void HandlePageContainerIllegalAccess(int8_t PageID, std::string_view IllegalMessage); // ToDo
		bool GetPageStatus();
	public:
		// ToDo
		PageContainer();

		int8_t AllocNewPage();
		bool AllocNewPage(AddressConj AddrConj);
		bool deAllocPage(AddressConj AddrConj);

		void Read(AddressConj AddrConj, char* Dst);
		void Write(AddressConj AddrConj, char* Src);

		void Read(AddressConj AddrConj, char* Dst, size_t size);
		void Write(AddressConj AddrConj, char* Src, size_t size);

		char* GetPhysicalPtr(AddressConj AddrConj);

		// DEBUG
		// ToDo
		void CheckPageEntryStatus(AddressConj AddrConj);

};

#endif // _PAGECONTAINER_H
	   //
	   //
