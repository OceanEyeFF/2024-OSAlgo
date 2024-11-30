/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : MemInterface.cpp
#   Last Modified : 2024-11-29 23:37
#   Describe      : 
#
# ====================================================*/

#include "MemInterface.h"
#include "FstPageTable.h"
#include "PageSystemGlobals.h"

PCB_MemInterface::PCB_MemInterface()
{
	IsNull.reset();
}

AddressPtr PCB_MemInterface::Alloc()
{
	SystemTracker::CallLog("MemInterface","Alloc");
	AddressConj MiddleValue = FirstPageTable.AllocNewPage();
	return MiddleValue.ToPtr();
}

bool PCB_MemInterface::Alloc(AddressPtr AddrPtr)
{
	SystemTracker::CallLog("MemInterface","Alloc");
	bool ret = FirstPageTable.AllocNewPage(AddressConj(AddrPtr));
	SystemTracker::FlushTracker();
	SystemTracker::RemoveAllLog();
	return ret;
}

bool PCB_MemInterface::deAlloc(AddressPtr AddrPtr)
{
	SystemTracker::CallLog("MemInterface","deAlloc");
	bool ret = FirstPageTable.deAllocPage(AddressConj(AddrPtr));
	SystemTracker::FlushTracker();
	SystemTracker::RemoveAllLog();
	return ret;
}

bool PCB_MemInterface::Read(char* Dst, AddressPtr AddrPtr)
{
	SystemTracker::CallLog("MemInterface","Read");
	bool ret=FirstPageTable.Read(AddressConj(AddrPtr),Dst);
	SystemTracker::FlushTracker();
	SystemTracker::RemoveAllLog();
	return ret;
}

bool PCB_MemInterface::Write(char* Src, AddressPtr AddrPtr)
{
	SystemTracker::CallLog("MemInterface","Write");
	bool ret=FirstPageTable.Write(AddressConj(AddrPtr),Src);
	SystemTracker::FlushTracker();
	SystemTracker::RemoveAllLog();
	return ret;
}

bool PCB_MemInterface::Read(char* Dst, AddressPtr AddrPtr, size_t size)
{
	SystemTracker::CallLog("MemInterface","Read");
	bool ret=FirstPageTable.Read(AddressConj(AddrPtr), Dst, size);
	SystemTracker::FlushTracker();
	SystemTracker::RemoveAllLog();
	return ret;
}

bool PCB_MemInterface::Write(char* Src, AddressPtr AddrPtr, size_t size)
{
	SystemTracker::CallLog("MemInterface","Write");
	bool ret=FirstPageTable.Write(AddressConj(AddrPtr), Src, size);
	SystemTracker::FlushTracker();
	SystemTracker::RemoveAllLog();
	return ret;
}

bool PCB_MemInterface::Alloc(int Poolid)			  // Alloc某一个指定的内存块
{
	if(IsNull[Poolid])
	{
		return false;
	}
	PtrPool[Poolid]=Alloc();
	IsNull.set(Poolid);
	return true;
}

bool PCB_MemInterface::deAlloc(int Poolid)		  // deAlloc某一个指定的内存块
{
	if(!IsNull[Poolid])
	{
		return false;
	}
	bool ret=deAlloc(PtrPool[Poolid]);
	PtrPool[Poolid]=AddressPtr();
	IsNull.reset(Poolid);
	return ret;
}

bool PCB_MemInterface::Read(char* Dst, int Poolid) // 读取某一个指定的内存块
{
	if(!IsNull[Poolid])
	{
		return false;
	}
	return Read(Dst,PtrPool[Poolid]);
}

bool PCB_MemInterface::Write(char* Src, int Poolid)// 写入某一个指定的内存块
{
	if(!IsNull[Poolid])
	{
		return false;
	}
	return Write(Src,PtrPool[Poolid]);
}

char* PCB_MemInterface::GetPhysicalPtr(AddressPtr AddrPtr)
{
	return FirstPageTable.GetPhysicalPtr(AddressConj(AddrPtr));
}
