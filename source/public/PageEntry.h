/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PageEntry.h
#   Last Modified : 2024-11-19 20:21
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _PAGEENTRY_H
#define  _PAGEENTRY_H

#include <bitset>
#include <cstdint>
#include "PageSystemGlobals.h"
#include "VirtualMemorySystem.h"

struct PageEntry
{
	uint16_t FrameNumber;
	uint8_t PageUniqueVariable; // Algo Use
							   //
	uint8_t STATUS;		// 0	Present bits 0在缓存 1在内存中
						// Below Temporary Unused
						  // 1	Dirty bits (Edited or not)
						  // 2	Referenced bit
						  // 3	Protected bit
						  // 4	Read Permision
						  // 5	Write Permision
						  // 6	Execute Permision
						  // 7	Check Bit
//	int ReferCounter; 
						  // 系统判断内存是否可以释放是通过内存块的指针数量和需要预留的内存空间来判断的
						  // 可以补充完善
#define PRESENTBITS		1
#define DIRTYBITS		2
#define REFERBITS		4
#define PROTECTBITS		8
#define READPERMBITS	16
#define WRITEPERMBITS	32
#define EXECPERMBITS	64
#define CHECKBITS		128
#define ALLBITS			255

	PageEntry(){}
	PageEntry(int FrameNo,int PageVar,bool ispresent):FrameNumber(FrameNo),PageUniqueVariable(PageVar)
	{
		STATUS = 0;
		STATUS|=(ispresent?PRESENTBITS:0);
	}

	void resetAll();		// 重置所有状态到未开辟


	bool isPresent();		// 查询是否在内存中
							// 以下函数由PRAlgo调用访问
	void setPresent();		// 设置状态为在内存中
	void resetPresent();	// 设置状态为不在内存中

	bool isDirty();		// 查询是否在内存中
							// 以下函数由PRAlgo调用访问
	void setDirty();		// 设置状态为在内存中
	void resetDirty();	// 设置状态为不在内存中

	void Alloc();
	void deAlloc();


	void Read(char* Dst);
	void Write(char* Src);
	void Read(AddressConj AddrConj, char* Dst, size_t size);
	void Write(AddressConj AddrConj, char* Src, size_t size);

// DEBUG
	char* GetPhysicalPtr();
};

#endif // _PAGEENTRY_H
	   //
	   //
