/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : FstPageTable.cpp
#   Last Modified : 2024-11-10 22:12
#   Describe      : 
#
# ====================================================*/

#include "FstPageTable.h"
#include "PageSystemGlobals.h"
#include "PageContainer.h"
#include "MyAlgo.hpp"
#include <cstddef>
#include <cstdint>

// FstPageTable Begin
// private
void FstPageTable::HandleMissingPage()
{
}
// public
FstPageTable::FstPageTable()
{
}

AddressConj FstPageTable::AllocNewPage()
{
	SystemTracker::CallLog("FstPageTable","AllocNewPage");
	for(uint8_t i=0;i<4;++i)
	{
		int8_t PageEntryID = Table[i].AllocNewPage();
		if(PageEntryID == -1)
		{
			continue;
		}
		SystemTracker::RemoveLog();
		return AddressConj(i,PageEntryID,0);
	}
	SystemTracker::RemoveLog();
	return AddressConj(0xff,0xff,0xff);
}

bool FstPageTable::AllocNewPage(AddressConj AddrConj)
{
	SystemTracker::CallLog("FstPageTable","AllocNewPage");
	bool ret=Table[AddrConj.PageContainerID].AllocNewPage(AddrConj);
	SystemTracker::RemoveLog();
	return ret;
}

bool FstPageTable::deAllocPage(AddressConj AddrConj)
{
	SystemTracker::CallLog("FstPageTable","deAllocNewPage");
	bool ret=Table[AddrConj.PageContainerID].deAllocPage(AddrConj);
	SystemTracker::RemoveLog();
	return ret;
}

void FstPageTable::Read(AddressConj AddrConj, char* Dst)
{
	SystemTracker::CallLog("FstPageTable","Read");
	Table[AddrConj.PageContainerID].Read(AddrConj,Dst);
	SystemTracker::RemoveLog();
}
void FstPageTable::Write(AddressConj AddrConj, char* Src)
{
	SystemTracker::CallLog("FstPageTable","Write");
	Table[AddrConj.PageContainerID].Write(AddrConj,Src);
	SystemTracker::RemoveLog();
}

void FstPageTable::Read(AddressConj AddrConj, char* Dst, size_t size)
{
	SystemTracker::CallLog("FstPageTable","Read");
	Table[AddrConj.PageContainerID].Read(AddrConj,Dst,size);
	SystemTracker::RemoveLog();
}
void FstPageTable::Write(AddressConj AddrConj, char* Src, size_t size)
{
	SystemTracker::CallLog("FstPageTable","Write");
	Table[AddrConj.PageContainerID].Write(AddrConj,Src,size);
	SystemTracker::RemoveLog();
}

char* FstPageTable::GetPhysicalPtr(AddressConj AddrConj)
{
	return Table[AddrConj.PageContainerID].GetPhysicalPtr(AddrConj);
}

// DEBUG
void FstPageTable::CheckPageEntryStatus(AddressConj AddrConj)
{
	Table[AddrConj.PageContainerID].CheckPageEntryStatus(AddrConj);
}
