/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PageEntry.cpp
#   Last Modified : 2024-11-19 20:24
#   Describe      : 
#
# ====================================================*/

#include "PageEntry.h"
#include "MessageBus.hpp"
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
	STATUS&=(ALLBITS^PRESENTBITS);
}

bool PageEntry::isDirty()
{
	return STATUS&DIRTYBITS;
}

void PageEntry::setDirty()
{
	STATUS|=DIRTYBITS;
}

void PageEntry::resetDirty()
{
	STATUS&=(ALLBITS^DIRTYBITS);
}

// Not Finished : Algo
void PageEntry::Alloc()
{
	SystemTracker::CallLog("PageEntry","Alloc");
	// Alloc from VMS
	FrameNumber = VirtualMemorySystem::MemoryController::AllocDiskMem();

	STATUS = 0;
	SystemTracker::RemoveLog();
}

void PageEntry::deAlloc()
{
	SystemTracker::CallLog("PageEntry","deAlloc");
	if(isPresent())
	{
		VirtualMemorySystem::MemoryController::deAllocLocalMem(FrameNumber);
	}
	else
	{
		VirtualMemorySystem::MemoryController::deAllocDiskMem(FrameNumber);
	}
	resetAll();
	SystemTracker::RemoveLog();
}

void PageEntry::Read(char* Dst) // Read()函数只能访问内存，不能访问磁盘缓存
{
	SystemTracker::CallLog("PageEntry","Read");
	if(!isPresent())
	{
		// LOG: LOG FROM PageEntry::Read()
		// LOG: Reading from a BLCK which not loaded in Memory
		// LOG: Reading Failed
		SystemTracker::RemoveLog();
		return;
	}
	VirtualMemorySystem::MemoryController::Read(Dst, FrameNumber, BLCK_SIZE);
	MessageBus::Notify("NotifyVisitingPages",this);
	SystemTracker::RemoveLog();
}

void PageEntry::Write(char* Src)// Read()函数只能访问内存，不能访问磁盘缓存
{
	SystemTracker::CallLog("PageEntry","Write");
	if(!isPresent())
	{
		// LOG: LOG FROM PageEntry::Write(char*)
		// LOG: Writing to a BLCK whici not loaded in Memory
		// LOG: Writing Failed
		SystemTracker::RemoveLog();
		return;
	}
	VirtualMemorySystem::MemoryController::Write(Src, FrameNumber, BLCK_SIZE);
	MessageBus::Notify("NotifyVisitingPages",this);
	setDirty();
	SystemTracker::RemoveLog();
}

void PageEntry::Read(AddressConj AddrConj, char* Dst, size_t size) // 同上
{
	SystemTracker::CallLog("PageEntry","Read");
	if(AddrConj.innerAddress + size - 1 > BLCK_SIZE)
	{
		// LOG: LOG FROM PageEntry::Read(char* , size_t)
		// LOG: Reading from a BLCK with exceeded Memory Size
		// LOG: Expected Memory size below BLCK_SIZE
		// LOG: Print(size)
		// LOG: Reading Failed
		SystemTracker::RemoveLog();
		return;
	}
	if(!isPresent())
	{
		// LOG: LOG FROM PageEntry::Read(char* , size_t )
		// LOG: Reading to a BLCK whici not loaded in Memory
		// LOG: Reading Failed
		SystemTracker::RemoveLog();
		return;
	}
	VirtualMemorySystem::MemoryController::Read(Dst, FrameNumber, AddrConj.innerAddress, size);
	MessageBus::Notify("NotifyVisitingPages",this);
	SystemTracker::RemoveLog();
}

void PageEntry::Write(AddressConj AddrConj, char* Src, size_t size)// 同上
{
	SystemTracker::CallLog("PageEntry","Write");
	if(AddrConj.innerAddress + size - 1 > BLCK_SIZE)
	{
		// LOG: LOG FROM PageEntry::Read(char* , size_t)
		// LOG: Reading from a BLCK with exceeded Memory Size
		// LOG: Expected Memory size below BLCK_SIZE
		// LOG: Print(size)
		// LOG: Reading Failed
		SystemTracker::RemoveLog();
		return;
	}
	if(!isPresent())
	{
		// LOG: LOG FROM PageEntry::Read(char* , size_t )
		// LOG: Reading to a BLCK whici not loaded in Memory
		// LOG: Reading Failed
		SystemTracker::RemoveLog();
		return;
	}
	VirtualMemorySystem::MemoryController::Write(Src, FrameNumber, AddrConj.innerAddress,  size);
	MessageBus::Notify("NotifyVisitingPages",this);
	setDirty();
	SystemTracker::RemoveLog();
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
