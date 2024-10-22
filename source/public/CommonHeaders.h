/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : CommonHeaders.h
#   Last Modified : 2024-10-22 20:49
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _COMMONHEADERS_H
#define  _COMMONHEADERS_H

#include <cstdint>

#if defined(PLATFORM_LINUX)
#include <unistd.h>

#elif defined(PLATFORM_WIN)
#include <Windows.h>

#endif

#define TOTAL_MEMSIZE		65536
#define LOCAL_MEMORYSIZE	16384
#define DISK_MEMORYSIZE		49152
#define BCLK_SIZE			256
#define	PAGE_PER_CONTAINER	64
#define CONTAINER_SIZE		4

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
