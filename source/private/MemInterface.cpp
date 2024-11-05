/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : MemInterface.cpp
#   Last Modified : 2024-11-05 21:26
#   Describe      : 
#
# ====================================================*/

#include "MemInterface.h"
#include "FstPageTable.h"
#include "PageSystemGlobals.h"


AddressPtr PCB_MemInterface::Alloc()
{
	AddressConj MiddleValue = FirstPageTable.AllocNewPage();
	return MiddleValue.ToPtr();
}

bool PCB_MemInterface::Alloc(AddressPtr AddrPtr)
{
	return FirstPageTable.AllocNewPage(AddressConj(AddrPtr));
}

bool PCB_MemInterface::deAlloc(AddressPtr AddrPtr)
{
	return FirstPageTable.deAllocPage(AddressConj(AddrPtr));
}

void PCB_MemInterface::Read(char* Dst, AddressPtr AddrPtr)
{
	FirstPageTable.Read(AddressConj(AddrPtr),Dst);
}

void PCB_MemInterface::Write(char* Src, AddressPtr AddrPtr)
{
	FirstPageTable.Write(AddressConj(AddrPtr),Src);
}

void PCB_MemInterface::Read(char* Dst, AddressPtr AddrPtr, size_t size)
{
	FirstPageTable.Read(AddressConj(AddrPtr), Dst, size);
}

void PCB_MemInterface::Write(char* Src, AddressPtr AddrPtr, size_t size)
{
	FirstPageTable.Write(AddressConj(AddrPtr), Src, size);
}

char* PCB_MemInterface::GetPhysicalPtr(AddressPtr AddrPtr)
{
	return FirstPageTable.GetPhysicalPtr(AddressConj(AddrPtr));
}
