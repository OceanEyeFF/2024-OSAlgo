/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : MemInterface.cpp
#   Last Modified : 2024-11-10 22:13
#   Describe      : 
#
# ====================================================*/

#include "MemInterface.h"
#include "FstPageTable.h"
#include "PageSystemGlobals.h"


AddressPtr PCB_MemInterface::Alloc()
{
	SystemTracker::CallLog("MemInterface","Alloc");
	AddressConj MiddleValue = FirstPageTable.AllocNewPage();
	SystemTracker::RemoveLog();
	return MiddleValue.ToPtr();
}

bool PCB_MemInterface::Alloc(AddressPtr AddrPtr)
{
	SystemTracker::CallLog("MemInterface","Alloc");
	bool ret=FirstPageTable.AllocNewPage(AddressConj(AddrPtr));
	SystemTracker::RemoveLog();
	return ret;
}

bool PCB_MemInterface::deAlloc(AddressPtr AddrPtr)
{
	SystemTracker::CallLog("MemInterface","deAlloc");
	bool ret=FirstPageTable.deAllocPage(AddressConj(AddrPtr));
	SystemTracker::RemoveLog();
	return ret;
}

void PCB_MemInterface::Read(char* Dst, AddressPtr AddrPtr)
{
	SystemTracker::CallLog("MemInterface","Read");
	FirstPageTable.Read(AddressConj(AddrPtr),Dst);
	SystemTracker::RemoveLog();
}

void PCB_MemInterface::Write(char* Src, AddressPtr AddrPtr)
{
	SystemTracker::CallLog("MemInterface","Write");
	FirstPageTable.Write(AddressConj(AddrPtr),Src);
	SystemTracker::RemoveLog();
}

void PCB_MemInterface::Read(char* Dst, AddressPtr AddrPtr, size_t size)
{
	SystemTracker::CallLog("MemInterface","Read");
	FirstPageTable.Read(AddressConj(AddrPtr), Dst, size);
	SystemTracker::RemoveLog();
}

void PCB_MemInterface::Write(char* Src, AddressPtr AddrPtr, size_t size)
{
	SystemTracker::CallLog("MemInterface","Write");
	FirstPageTable.Write(AddressConj(AddrPtr), Src, size);
	SystemTracker::RemoveLog();
}

char* PCB_MemInterface::GetPhysicalPtr(AddressPtr AddrPtr)
{
	return FirstPageTable.GetPhysicalPtr(AddressConj(AddrPtr));
}
