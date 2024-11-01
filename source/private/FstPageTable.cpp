/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : FstPageTable.cpp
#   Last Modified : 2024-11-01 20:10
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
	for(uint8_t i=0;i<4;++i)
	{
		uint8_t PageEntryID = Table[i].AllocNewPage();
		if(PageEntryID == -1)
		{
			continue;
		}
		return AddressConj(i,PageEntryID,0);
	}
	return AddressConj(0xff,0xff,0xff);
}

void FstPageTable::deAllocPage(AddressConj AddrConj)
{
	Table[AddrConj.PageContainerID].deAllocPage(AddrConj.PageID);
}

void FstPageTable::Read(AddressConj AddrConj, char* Dst)
{
	Table[AddrConj.PageContainerID].Read(AddrConj,Dst);
}
void FstPageTable::Write(AddressConj AddrConj, char* Src)
{
	Table[AddrConj.PageContainerID].Write(AddrConj,Src);
}

void FstPageTable::Read(AddressConj AddrConj, char* Dst, size_t size)
{
	Table[AddrConj.PageContainerID].Read(AddrConj,Dst,size);
}
void FstPageTable::Write(AddressConj AddrConj, char* Src, size_t size)
{
	Table[AddrConj.PageContainerID].Write(AddrConj,Src,size);
}

char* FstPageTable::GetPhysicalPtr(AddressConj AddrConj)
{
	return Table[AddrConj.PageContainerID].GetPhysicalPtr(AddrConj);
}

//DEBUG
//
void FstPageTable::CheckPageEntryStatus(AddressConj AddrConj)
{
	Table[AddrConj.PageContainerID].CheckPageEntryStatus(AddrConj.PageID);
}
