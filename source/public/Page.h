/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : Page.h
#   Last Modified : 2024-10-25 22:41
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _PAGE_H
#define  _PAGE_H

#include <bitset>
#include <cstdint>
#include "CommonHeaders.h"

					// Not Ready : LRU/Clock
					// Not Ready : Improved Clock

// AddressConj
// Act as MemoryAddressConverter
//
struct AddressConj
{
	int8_t innerAddress;
	int8_t PageID;
	int8_t PageContainerID;

	AddressConj();
	~AddressConj();
	AddressConj(AddressPtr ptr);
	AddressPtr ToPtr();
};

// void PageReplacementAlgo( std :: function<void(char*)> PRAfunc , char* MemPtr);
// void FIFO(char* MemPtr);

extern EPageAlgoType EPageAlgo;
void SetPageAlgo(int32_t type);
void SetPageAlgo(EPageAlgoType type);

struct PageEntry
{
	int16_t FrameNumber;
	int16_t PageUniqueVariable; // Algo

	std::bitset<8> STATUSBITS; // 0	Present bits
						  // Below Temporary Unused
						  // 1	Dirty bits
						  // 2	Referenced bit
						  // 3	Protected bit
						  // 4	Read Permision
						  // 5	Write Permision
						  // 6	Execute Permision
						  // 7	Check Bit

	PageEntry(){}
	PageEntry(int FrameNo,int PageVar,bool ispresent):FrameNumber(FrameNo),PageUniqueVariable(PageVar)
	{
		STATUSBITS[0]=ispresent?1:0;
	}

	bool isPresent();
	void setPresent();
	void resetPresent();

	void Alloc();
	void deAlloc();

	char* GetPhysicalPtr();


	void Read(char* Dst);
	void Write(char* Src);
	void Read(char* Dst, size_t size);
	void Write(char* Src, size_t size);
};

class PageContainer// 一级页表
{
	std :: bitset<32> PagesUsage;
	PageEntry Pages[32];
//	PRAlgoBase* PageReplacementUnit;

	private:
		// To Do
		void ExecPageReplacementFunc(int8_t PageID);
	public:
		PageContainer();

		int8_t AllocNewPage();
		void deAllocPage(int8_t Page);

		// To Do
		bool TryVisitPage(int8_t PageID);
		void ForcePresentPage(int8_t PageID);

		char* GetPhysicalPtr(AddressConj AddrConj);
		void Read(AddressConj AddrConj, char* Dst);
		void Write(AddressConj AddrConj, char* Src);

		void Read(AddressConj AddrConj, char* Dst, size_t size);
		void Write(AddressConj AddrConj, char* Src, size_t size);
};

#endif // _PAGE_H
	   //
	   //
