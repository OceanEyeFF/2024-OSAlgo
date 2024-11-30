/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PageContainer.cpp
#   Last Modified : 2024-11-28 23:34
#   Describe      : 
#
# ====================================================*/

#include <cstring>
#include <cstddef>
#include <cstdint>
#include <string_view>
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

#ifdef _DEBUG
	// std :: cout << "Missing Page Happend:" << std::endl;
	// std :: cout << "* PageID\t, Try PeplacedPage " << std::endl;
	// std :: cout << "* " << (int)PageID << "\t\t, " << std :: endl;
	LOG(DEBUG) << "Missing Page Happend:";
	LOG(DEBUG) << "* PageID\t, Try PeplacedPage ";
	LOG(DEBUG) << "* " << (int)PageID;
#endif
	if(PageReplacementAlgoGlobals::RuntimePageAlgo->CheckPageFull())
	{
		PageReplacementAlgoGlobals::RuntimePageAlgo->SwapReplacedPagesAndSpecifiedPages(&Pages[PageID]);
	}
	else
	{
		PageReplacementAlgoGlobals::RuntimePageAlgo->PutPageInMem(&Pages[PageID]);
	}
	// RestoreCurrentProcessState();
	// ContinueProcess();
}

// ToDo
// Illegal Access Needs Report
void PageContainer::HandlePageContainerIllegalAccess(int8_t PageID, std::string_view IllegalMessage)
{
//	SystemTracker::FlushTracker();
#ifdef _DEBUG
//	std :: cout << "IllegalAccess Happend:" << std::endl;
//	std :: cout << "* PageID\t, IllegalMessage" << std::endl;
//	std :: cout << "* " << (int)PageID << "\t\t, " << IllegalMessage << std :: endl;
	LOG(DEBUG) << "IllegalAccess Happend:";
	LOG(DEBUG) << "* PageID\t, IllegalAccess Reported";
	LOG(DEBUG) << "* " << (int)PageID;
#endif
}

// public
// ToDo: PageReplacementAlgoGlobals::RuntimePageAlgo
PageContainer::PageContainer()
{
	std::memset(Pages,0,sizeof(Pages));
	PagesUsage.reset();
}

int8_t PageContainer::AllocNewPage()
{
	SystemTracker::CallLog("PageContainer","AllocNewPage");
	if(PagesUsage.count()==64)
	{
		return -1; // No Pages Slot
	}

	int8_t EmptyPosition = MyAlgo::ForBitset::FindFirstZero(PagesUsage);
	PagesUsage.set(EmptyPosition);
	Pages[EmptyPosition].Alloc();

	return EmptyPosition;
}

bool PageContainer::AllocNewPage(AddressConj AddrConj)
{
	SystemTracker::CallLog("PageContainer","AllocNewPage");
	int8_t PageID = AddrConj.PageID;
	if(PagesUsage[PageID])
	{
		HandlePageContainerIllegalAccess(PageID, "Alloc Illegal");
		return false;		// PageAlreadyInUse
	}

	PagesUsage.set(PageID);
	Pages[PageID].Alloc();

	return true;
}

bool PageContainer::deAllocPage(AddressConj AddrConj)
{
	SystemTracker::CallLog("PageContainer","deAllocNewPage");
	int8_t PageID = AddrConj.PageID;
	if(!PagesUsage[PageID])
	{
		HandlePageContainerIllegalAccess(PageID, "deAlloc Illegal");
		return false;		// PageNotInUse
	}

	if(Pages[PageID].isPresent())
	{
		PageReplacementAlgoGlobals::RuntimePageAlgo->HandleFuncDeAllocMem(&Pages[PageID]);
	}

	Pages[PageID].deAlloc();
	PagesUsage.reset(PageID);
	return true;
}

bool PageContainer::Read(AddressConj AddrConj, char* Dst)
{
	SystemTracker::CallLog("PageContainer","Read");
	if(!PagesUsage[AddrConj.PageID])
	{
		HandlePageContainerIllegalAccess(AddrConj.PageID, "Read");
		return false;
	}
	if(!Pages[AddrConj.PageID].isPresent())
	{
		HandlePageContainerMissingPage(AddrConj.PageID);
	}
	Pages[AddrConj.PageID].Read(Dst);
	return true;
}

bool PageContainer::Write(AddressConj AddrConj, char* Dst)
{
	SystemTracker::CallLog("PageContainer","Write");
	if(!PagesUsage[AddrConj.PageID])
	{
		HandlePageContainerIllegalAccess(AddrConj.PageID, "Write");
		return false;
	}
	if(!Pages[AddrConj.PageID].isPresent())
	{
		HandlePageContainerMissingPage(AddrConj.PageID);
	}
	Pages[AddrConj.PageID].Write(Dst);
	return true;
}

bool PageContainer::Read(AddressConj AddrConj, char* Dst, size_t size)
{
	SystemTracker::CallLog("PageContainer","Read");
	if(!PagesUsage[AddrConj.PageID])
	{
		HandlePageContainerIllegalAccess(AddrConj.PageID, "Read");
		return false;
	}
	if(!Pages[AddrConj.PageID].isPresent())
	{
		HandlePageContainerMissingPage(AddrConj.PageID);
	}
	Pages[AddrConj.PageID].Read(AddrConj, Dst, size);
	return true;
}

bool PageContainer::Write(AddressConj AddrConj, char* Dst, size_t size)
{
	SystemTracker::CallLog("PageContainer","Write");
	if(!PagesUsage[AddrConj.PageID])
	{
		HandlePageContainerIllegalAccess(AddrConj.PageID, "Write");
		return false;
	}
	if(!Pages[AddrConj.PageID].isPresent())
	{
		HandlePageContainerMissingPage(AddrConj.PageID);
	}
	Pages[AddrConj.PageID].Write(AddrConj, Dst, size);
	return true;
}

char* PageContainer::GetPhysicalPtr(AddressConj AddrConj)
{
	return Pages[AddrConj.PageID].GetPhysicalPtr();
}

// DEBUG
void PageContainer::CheckPageEntryStatus(AddressConj AddrConj) // Ranges(0,63) // ToDo
{
	int8_t PageID = AddrConj.PageID;
	bool PageUsage = PageContainer::PagesUsage[PageID];
	bool PageInMem = Pages[PageID].isPresent();
	bool PRAlgoStatus = PageReplacementAlgoGlobals::RuntimePageAlgo->CheckPagePtrExist(&Pages[PageID]);
	// log print
}
