/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : MemInterface.h
#   Last Modified : 2024-10-31 19:05
#   Describe      : 
#
# ====================================================*/

#pragma once

#include "PageSystemGlobals.h"
#ifndef  _MEMINTERFACE_H
#define  _MEMINTERFACE_H

#include <cstdint>
#include "CommonHeaders.h"
#include "PageContainer.h"
#include "FstPageTable.h"

extern struct AddressPtr;
extern enum EPageAlgoType;
extern class FstPageTable;

class MemInterface
{
	std :: vector<FstPageTable> PCB_FstPageTable;
};

#endif // _MEMINTERFACE_H
	   //
	   //
