/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PageSystemGlobals.cpp
#   Last Modified : 2024-10-31 20:17
#   Describe      : 
#
# ====================================================*/

#include "PageSystemGlobals.h"
#include "PageContainer.h"

// AddressPtr and AddressConj
// 虚拟地址结构体访问

AddressConj::AddressConj()
{
	innerAddress = PageID = PageContainerID = 0;
}

AddressConj::AddressConj(AddressPtr ptr)
{
	innerAddress = ptr.__ptr__>> (SECPAGE_BITS + FSTPAGE_BITS);
	PageID = (ptr.__ptr__& ((~(int16_t)0)>>(16-SECPAGE_BITS-FSTPAGE_BITS)))>>2;
	PageContainerID = ptr.__ptr__ &  ((~(int16_t)0)>>(16-SECPAGE_BITS-FSTPAGE_BITS));
}

AddressConj::AddressConj(int8_t __PageContainerID, int8_t __PageID, int8_t __innerAddress):
	PageContainerID(__PageContainerID),PageID(__PageID),innerAddress(__innerAddress)
{
}

AddressPtr AddressConj::ToPtr()
{
	AddressPtr ret;
	ret.__ptr__= innerAddress << (SECPAGE_BITS + FSTPAGE_BITS) || PageID << (FSTPAGE_BITS)  || PageContainerID;
	return ret;
}

EPageAlgoType EPageAlgo;

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

