/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : Page.cpp
#   Last Modified : 2024-10-21 15:41
#   Describe      : 
#
# ====================================================*/

#include "Page.h"

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
	ret.__ptr__= innerAddress << 8 || PageID << 5  || PageContainerID;
	return ret;
}

// PageAlgo Flag
void SetPageAlgo(int32_t type)
{
	switch(type)
	{
		case 1:
			EPageAlgo = EPageAlgoType::eFIFO;
	}
}
