/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : FstPageTable.cpp
#   Last Modified : 2024-11-28 23:37
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
		return AddressConj(i,PageEntryID,0);
	}
	return AddressConj(0xff,0xff,0xff);
}

bool FstPageTable::AllocNewPage(AddressConj AddrConj)
{
	SystemTracker::CallLog("FstPageTable","AllocNewPage");
	return Table[AddrConj.PageContainerID].AllocNewPage(AddrConj);
}

bool FstPageTable::deAllocPage(AddressConj AddrConj)
{
	SystemTracker::CallLog("FstPageTable","deAllocNewPage");
	return Table[AddrConj.PageContainerID].deAllocPage(AddrConj);
}

bool FstPageTable::Read(AddressConj AddrConj, char* Dst)
{
	SystemTracker::CallLog("FstPageTable","Read");
	return Table[AddrConj.PageContainerID].Read(AddrConj,Dst);
}
bool FstPageTable::Write(AddressConj AddrConj, char* Src)
{
	SystemTracker::CallLog("FstPageTable","Write");
	return Table[AddrConj.PageContainerID].Write(AddrConj,Src);
}

bool FstPageTable::Read(AddressConj AddrConj, char* Dst, size_t size)
{
	SystemTracker::CallLog("FstPageTable","Read");
	return Table[AddrConj.PageContainerID].Read(AddrConj,Dst,size);
}
bool FstPageTable::Write(AddressConj AddrConj, char* Src, size_t size)
{
	SystemTracker::CallLog("FstPageTable","Write");
	return Table[AddrConj.PageContainerID].Write(AddrConj,Src,size);
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
