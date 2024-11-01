/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PageContainer.cpp
#   Last Modified : 2024-10-31 23:03
#   Describe      : 
#
# ====================================================*/

#include <cstring>
#include <cstddef>
#include <cstdint>
#include "PageSystemGlobals.h"
#include "PageEntry.h"
#include "MyAlgo.hpp"
#include "PageContainer.h"

// PageContainer
// private
void PageContainer::HandlePageContainerMissingPage(int8_t PageID)
	// Handled situation:
	// Pages not in memory
	// Solution:
	// 1. Memory is full : Swap Pages between Mem And DiskMem
	// 2. Memory has space : Copy Pages into Memory
{
	// PCB* currentProcess = GetProcess();
	// SaveCurrentProcessState();
	if(PageReplacementUnit->CheckPageFull())
	{
		PageReplacementUnit->SwapReplacedPagesAndSpecifiedPages(&Pages[PageID]);
	}
	else
	{
		PageReplacementUnit->PutPageInMem(&Pages[PageID]);
	}
	// RestoreCurrentProcessState();
	// ContinueProcess();
}

// ToDo
// Illegal Access Needs Report
void PageContainer::HandlePageContainerIllegalAccess(int8_t PageID)
{
}

// public
// ToDo: PageReplacementUnit
PageContainer::PageContainer()
{
	std::memset(Pages,0,sizeof(Pages));
//	PageReplacementUnit = new FIFO_PageSelector;
	PagesUsage.reset();
/*
	switch(EPageAlgo)
	{
		case EPageAlgoType::eFIFO :
			PageReplacementUnit = new FIFO_PageSelector;
			break;
		case EPageAlgoType::eLRU :
//			PageReplacementUnit = new FIFO_PageSelector;
			break;
		case EPageAlgoType::eClock :
//			PageReplacementUnit = new FIFO_PageSelector;
			break;
		case EPageAlgoType::eImprovedClock :
//			PageReplacementUnit = new FIFO_PageSelector;
			break;
	}
*/
//To Do
//Set PageAlgo
}

int8_t PageContainer::AllocNewPage()
{
	if(PagesUsage.count()==64) return -1; // No Pages Slot
	unsigned long tmp = PagesUsage.to_ulong();
	unsigned int id = 0;
	tmp = ~tmp;
	
	for(;!(tmp&1);tmp>>=1) ++id;

	Pages[id].Alloc();
	PagesUsage.set(id);

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

void PageContainer::Read(AddressConj AddrConj, char* Dst)
{
	if(!PagesUsage[AddrConj.PageID])
	{
		HandlePageContainerIllegalAccess(AddrConj.PageID);
	}
	if(!Pages[AddrConj.PageID].isPresent())
	{
		HandlePageContainerMissingPage(AddrConj.PageID);
	}
	Pages[AddrConj.PageID].Read(Dst);
}

void PageContainer::Write(AddressConj AddrConj, char* Dst)
{
	if(!PagesUsage[AddrConj.PageID])
	{
		HandlePageContainerIllegalAccess(AddrConj.PageID);
	}
	if(!Pages[AddrConj.PageID].isPresent())
	{
		HandlePageContainerMissingPage(AddrConj.PageID);
	}
	Pages[AddrConj.PageID].Write(Dst);
}

void PageContainer::Read(AddressConj AddrConj, char* Dst, size_t size)
{
	if(!PagesUsage[AddrConj.PageID])
	{
		HandlePageContainerIllegalAccess(AddrConj.PageID);
	}
	if(!Pages[AddrConj.PageID].isPresent())
	{
		HandlePageContainerMissingPage(AddrConj.PageID);
	}
	Pages[AddrConj.PageID].Read(AddrConj, Dst, size);
}

void PageContainer::Write(AddressConj AddrConj, char* Dst, size_t size)
{
	if(!PagesUsage[AddrConj.PageID])
	{
		HandlePageContainerIllegalAccess(AddrConj.PageID);
	}
	if(!Pages[AddrConj.PageID].isPresent())
	{
		HandlePageContainerMissingPage(AddrConj.PageID);
	}
	Pages[AddrConj.PageID].Write(AddrConj, Dst, size);
}

char* PageContainer::GetPhysicalPtr(AddressConj AddrConj)
{
	return Pages[AddrConj.PageID].GetPhysicalPtr();
}

// DEBUG
void PageContainer::CheckPageEntryStatus(int8_t PageID) // Ranges(0,63) // ToDo
{
	bool PageUsage = PageContainer::PagesUsage[PageID];
	bool PageInMem = Pages[PageID].isPresent();
	bool PRAlgoStatus = PageReplacementUnit->CheckPagePtrExist(&Pages[PageID]);
	// log print
}
