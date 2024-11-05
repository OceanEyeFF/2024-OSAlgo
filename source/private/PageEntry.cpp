/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PageEntry.cpp
#   Last Modified : 2024-11-03 12:07
#   Describe      : 
#
# ====================================================*/

#include "PageEntry.h"
#include "PageSystemGlobals.h"

// PageEntry
//

void PageEntry::resetAll() // ToDo
{
	if(isPresent())
	{
		// remove PageEntry from PRAlgo
	}
	FrameNumber = 0;
	PageUniqueVariable = 0;
	STATUS = 0;
}

bool PageEntry::isPresent()
{
	return STATUS&PRESENTBITS;
}

void PageEntry::setPresent()
{
	STATUS|=PRESENTBITS;
}

void PageEntry::resetPresent()
{
	STATUS^=(STATUS&PRESENTBITS)?PRESENTBITS:0;
}

// Not Finished : Algo
void PageEntry::Alloc()
{
	// Alloc from VMS
	FrameNumber = VirtualMemorySystem::MemoryController::AllocDiskMem();

	STATUS = 0;
}

void PageEntry::deAlloc()
{
	if(isPresent())
	{
		VirtualMemorySystem::MemoryController::deAllocLocalMem(FrameNumber);
	}
	else
	{
		VirtualMemorySystem::MemoryController::deAllocDiskMem(FrameNumber);
	}
	resetAll();
}

void PageEntry::Read(char* Dst) // Read()函数只能访问内存，不能访问磁盘缓存
{
	if(!isPresent())
	{
		// LOG: LOG FROM PageEntry::Read()
		// LOG: Reading from a BLCK which not loaded in Memory
		// LOG: Reading Failed
		return;
	}
	VirtualMemorySystem::MemoryController::Read(Dst, FrameNumber, BLCK_SIZE);
}

void PageEntry::Write(char* Src)// Read()函数只能访问内存，不能访问磁盘缓存
{
	if(!isPresent())
	{
		// LOG: LOG FROM PageEntry::Write(char*)
		// LOG: Writing to a BLCK whici not loaded in Memory
		// LOG: Writing Failed
		return;
	}
	VirtualMemorySystem::MemoryController::Write(Src, FrameNumber, BLCK_SIZE);
}

void PageEntry::Read(AddressConj AddrConj, char* Dst, size_t size) // 同上
{
	if(AddrConj.innerAddress + size - 1 > BLCK_SIZE)
	{
		// LOG: LOG FROM PageEntry::Read(char* , size_t)
		// LOG: Reading from a BLCK with exceeded Memory Size
		// LOG: Expected Memory size below BLCK_SIZE
		// LOG: Print(size)
		// LOG: Reading Failed
		return;
	}
	if(!isPresent())
	{
		// LOG: LOG FROM PageEntry::Read(char* , size_t )
		// LOG: Reading to a BLCK whici not loaded in Memory
		// LOG: Reading Failed
		return;
	}
	VirtualMemorySystem::MemoryController::Read(Dst, FrameNumber, AddrConj.innerAddress, size);
}

void PageEntry::Write(AddressConj AddrConj, char* Src, size_t size)// 同上
{
	if(AddrConj.innerAddress + size - 1 > BLCK_SIZE)
	{
		// LOG: LOG FROM PageEntry::Read(char* , size_t)
		// LOG: Reading from a BLCK with exceeded Memory Size
		// LOG: Expected Memory size below BLCK_SIZE
		// LOG: Print(size)
		// LOG: Reading Failed
		return;
	}
	if(!isPresent())
	{
		// LOG: LOG FROM PageEntry::Read(char* , size_t )
		// LOG: Reading to a BLCK whici not loaded in Memory
		// LOG: Reading Failed
		return;
	}
	VirtualMemorySystem::MemoryController::Write(Src, FrameNumber, AddrConj.innerAddress,  size);
}

// DEBUG
char* PageEntry::GetPhysicalPtr()
{
	if(isPresent())
	{
		return VirtualMemorySystem::MemoryController::GetLocalPhysicalPtr(FrameNumber);
	}
	else
	{
		return VirtualMemorySystem::MemoryController::GetDiskPhysicalPtr(FrameNumber);
	}
}
