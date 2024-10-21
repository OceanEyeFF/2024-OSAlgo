/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : CommonHeaders.h
#   Last Modified : 2024-10-21 15:38
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _COMMONHEADERS_H
#define  _COMMONHEADERS_H

#include <cstdint>

#define TOTAL_MEMSIZE		131072
#define LOCAL_MEMORYSIZE	32768
#define DISK_MEMORYSIZE		98034
#define BCLK_SIZE			256
#define	PAGE_PER_CONTAINER	64
#define CONTAINER			4

struct AddressPtr
{
	int16_t __ptr__;
};

enum class EPageAlgoType
{
	eFIFO,
	eLRU,
	eClock,
	eImprovedClock
};

#endif // _COMMONHEADERS_H
	   //
	   //
