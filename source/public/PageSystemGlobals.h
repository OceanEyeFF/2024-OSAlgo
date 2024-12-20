/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PageSystemGlobals.h
#   Last Modified : 2024-11-28 23:39
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _PAGESYSTEMGLOBALS_H
#define  _PAGESYSTEMGLOBALS_H

#include <cstdint>
#include "StatusTracker.h"

#define TOTAL_MEMSIZE		327680
#define LOCAL_MEMORYSIZE	65536
#define DISK_MEMORYSIZE		262144
#define BLCK_SIZE			256
#define BLCK_CNT			256
#define	PAGE_PER_CONTAINER	64
#define CONTAINER_SIZE		4

#define FSTPAGE_BITS		2
#define SECPAGE_BITS		6
#define BLCK_BITS			8
#define THIRDLEVEL_BITS		8

#define FIRST_LEVEL_MASK	3
#define SECOND_LEVEL_MASK	63
#define THIRD_LEVEL_MASK	255

#define FIRST_LEVEL_SHIFT	14
#define SECOND_LEVEL_SHIFT	8
#define THIRD_LEVEL_SHIFT	0

/* Address has 16bits
 * 0000000000000000
 * 1122222233333333
 * 1 : FstPage FirstPage
 * 2 : PageContainer SecondPage
 * 3 : innerBlockID
 */

struct AddressPtr
{
	uint16_t __ptr__;
};

// AddressConj
// Act as MemoryAddressConverter
//
struct AddressConj
{
	int8_t innerAddress;
	int8_t PageID;
	int8_t PageContainerID;

#define FIRSTLEVELID		PageContainerID
#define SECONDLEVELID		PageID
#define THIRDLEVELID		innerAddress

	AddressConj();
	AddressConj(AddressPtr ptr);
	AddressConj(int8_t __PageContainerID, int8_t __PageID, int8_t __innerAddress);
	AddressPtr ToPtr();
};

// Tracker declairation
namespace SystemTracker
{
	extern StatusTracker Tracker;
	void RegistMessageBus();
	void CallLog(std::string CLASSNAME, std::string LOG="");
	void RemoveAllLog();
	void RemoveLog();
	void FlushTracker();
}

#endif // _PAGESYSTEMGLOBALS_H
	   //
	   //
