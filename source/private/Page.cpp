/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : Page.cpp
#   Last Modified : 2024-10-23 01:52
#   Describe      : 
#
# ====================================================*/

#include "Page.h"
#include <cstdint>

EPageAlgoType EPageAlgo;

// AddressPtr and AddressConj
// 虚拟地址结构体访问
AddressConj::AddressConj(AddressPtr ptr)
{
	innerAddress = ptr.__ptr__>> 8;
	PageID = (ptr.__ptr__& 511)>>2;
	PageContainerID = ptr.__ptr__& 3;
}

AddressPtr AddressConj::ToPtr()
{
	AddressPtr ret;
	ret.__ptr__= innerAddress << 8 || PageID << 2  || PageContainerID;
	return ret;
}

// PageAlgo Flag
void SetPageAlgo(int32_t Type)
{
	switch(Type)
	{
		case 0:
			EPageAlgo = EPageAlgoType::eFIFO;
			break;
		case 1:
			EPageAlgo = EPageAlgoType::eLRU;
			break;
		case 2:
			EPageAlgo = EPageAlgoType::eClock;
			break;
		case 3:
			EPageAlgo = EPageAlgoType::eImprovedClock;
			break;
	}
}

void SetPageAlgo(EPageAlgoType EType)
{
	EPageAlgo = EType;
}

// Page
bool PageEntry::isPresent()
{
	return STATUSBITS[0]==1;
}

void PageEntry::setPresent()
{
	STATUSBITS.set(0);
}

void PageEntry::resetPresent()
{
	STATUSBITS.reset(0);
}

// To DO
// Not Finished : Algo
void PageEntry::Alloc()
{
	frameNumber = VirtualSystemMemory::MemoryController::AllocDisk();
//	PageUniqueVariable =
//	
//
	STATUSBITS.reset();
	STATUSBITS.set(1);
}

void PageEntry::deAlloc()
{
	if(STATUSBITS[1])
	{
		VirtualSystemMemory::MemoryController::deAllocLocalMem(frameNumber);
	}
	else
	{
		VirtualSystemMemory::MemoryController::deAllocDiskMem(frameNumber);
	}
	STATUSBITS.reset();
}

char* PageEntry::GetPhysicalPtr()
{
	if(STATUSBITS[0])
	{
		return VirtualSystemMemory::MemoryController::GetLocalPhysicalPtr(frameNumber);
	}
	else
	{
		return VirtualSystemMemory::MemoryController::GetDiskPhysicalPtr(frameNumber);
	}

}

void PageEntry::Read(char* Dst)
{
	if(STATUSBITS[0]==0)
	{
		// LOG: LOG FROM PageEntry::Read()
		// LOG: Reading from a BCLK whici not loaded in Memory
		// LOG: Reading Failed
		return;
	}
	VirtualSystemMemory::MemoryController::Read(Dst, GetPhysicalPtr(), BCLK_SIZE);
}

void PageEntry::Write(char* Src)
{
	if(STATUSBITS[0]==0)
	{
		// LOG: LOG FROM PageEntry::Write(char*)
		// LOG: Writing to a BCLK whici not loaded in Memory
		// LOG: Writing Failed
		return;
	}
	VirtualSystemMemory::MemoryController::Write(Src, GetPhysicalPtr(), BCLK_SIZE);
}

void PageEntry::Read(char* Dst, size_t size)
{
	if(size > BCLK_SIZE)
	{
		// LOG: LOG FROM PageEntry::Read(char* , size_t)
		// LOG: Reading from a BCLK with exceeded Memory Size
		// LOG: Expected Memory size below BCLK_SIZE
		// LOG: Print(size)
		// LOG: Reading Failed
		return;
	}
	if(STATUSBITS[0]==0)
	{
		// LOG: LOG FROM PageEntry::Read(char* , size_t )
		// LOG: Reading to a BCLK whici not loaded in Memory
		// LOG: Reading Failed
		return;
	}
	VirtualSystemMemory::MemoryController::Read(Dst, GetPhysicalPtr(), size);
}

void PageEntry::Write(char* Src, size_t size)
{
	if(size > BCLK_SIZE)
	{
		// LOG: LOG FROM PageEntry::Write(char* ,size_t)
		// LOG: Writing to a BCLK with exceeded Memory Size
		// LOG: Expected Memory size below BCLK_SIZE
		// LOG: Print(size)
		// LOG: Reading Failed
		return;
	}
	if(STATUSBITS[0]==0)
	{
		// LOG: LOG FROM PageEntry::Read(char* , size_t )
		// LOG: Reading to a BCLK whici not loaded in Memory
		// LOG: Reading Failed
		return;
	}
	VirtualSystemMemory::MemoryController::Write(Src, GetPhysicalPtr(), size);
}

// PageContainer
// private
// To Do
void PageContainer::ExecPageReplacementFunc(int8_t PageID)
{}

// public
PageContainer::PageContainer()
{
	std::memset(Pages,0,sizeof(Pages));
//To Do
//Set PageAlgo
}

int8_t PageContainer::AllocNewPage()
{
	if(PagesUsage.count()==64) return -1;
	unsigned long tmp = PagesUsage.to_ulong();
	unsigned int id = 0;
	tmp = ~tmp;
	
	for(;!(tmp&1);tmp>>=1) ++id;

	PagesUsage.set(id);
	Pages[id].Alloc();

	return id;
}

void PageContainer::deAllocPage(int8_t PageID)
{
	if(!PagesUsage[PageID])
	{
		return;		// PageNotInUse
	}

	Pages[PageID].deAlloc();
	PagesUsage.reset(PageID);
}

// To DO
//
bool PageContainer::TryVisitPage(int8_t PageID) { return true; }

void PageContainer::ForcePresentPage(int8_t PageID) {}


