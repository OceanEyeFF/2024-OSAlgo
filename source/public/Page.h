/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : Page.h
#   Last Modified : 2024-10-21 15:41
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _PAGE_H
#define  _PAGE_H

#include <functional>

#include "CommonHeaders.h"
#include "VirtualSystemMemory.h"

struct AddressConj
{
	int8_t innerAddress;
	int8_t PageID;
	int8_t PageContainerID;

	AddressConj();
	~AddressConj();
	AddressConj(AddressPtr ptr);
	AddressPtr ToPtr();
};

// void PageReplacementAlgo( std :: function<void(char*)> PRAfunc , char* MemPtr);
// void FIFO(char* MemPtr);

extern EPageAlgoType EPageAlgo;
void SetPageAlgo(int32_t type);

class Page
{
	AddressPtr pMemBclkPtr;
	unsigned short int PageUniqueVariable;
	bool present;

	Page();
	~Page();
};

class PageContainer
{
};

#endif // _PAGE_H
	   //
	   //
