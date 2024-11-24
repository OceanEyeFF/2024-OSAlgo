/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoCLOCK.cpp
#   Last Modified : 2024-11-22 21:57
#   Describe      : 
#
# ====================================================*/

#include <cstdint>
#include <cstring>
#include <vector>
#include <algorithm>
#include "PRAlgoCLOCK.h"
#include "PRAlgoBase.h"
#include "MessageBus.hpp"
#include "PageEntry.h"

// private
//
int16_t CLOCK_PageSelector::AddNewPagePtr(PageEntry* PagePtr)
{
	for(int i=0;i<BLCK_CNT;++i)
	{
		int I = (i+CurrentNode)%BLCK_CNT;
		if(PageQueue[I]==nullptr)
		{
			PageQueue[I] = PagePtr;
			++Size;
			return 0;
		}
	}
	return -1;
}

PageEntry* CLOCK_PageSelector::GetReplacePagePtr()
{
	if(Size==0)
	{
		return nullptr;
	}
	while(PageQueue[CurrentNode]==nullptr||PageQueue[CurrentNode]->PageUniqueVariable)
	{
		if(PageQueue[CurrentNode])
		{
			PageQueue[CurrentNode]->PageUniqueVariable = 0;
		}
		++CurrentNode;
		CurrentNode-=(CurrentNode>=BLCK_CNT)?BLCK_CNT:0;
	}
	return PageQueue[CurrentNode];
}

PageEntry* CLOCK_PageSelector::RemoveReplacePagePtr()
{
	assert(Size >0 && "Page Replacement Algo is running without Page");
	GetReplacePagePtr();
	PageEntry* ret = PageQueue[CurrentNode];
	PageQueue[CurrentNode]=nullptr;
	--Size;
	return ret;
}

void CLOCK_PageSelector::RemovePagePtr(PageEntry* PagePtr)
{
	assert(Size>0 && "Page Replacement Algo is running without Page");
	bool find = false;
	for(int i=0;i<BLCK_CNT;++i)
	{
		int I = (i+CurrentNode)%BLCK_CNT;
		if(PageQueue[I]==PagePtr)
		{
			PageQueue[I]=nullptr;
			--Size;
			find = true;
			break;
		}
	}
	assert(find && "Removing Page not Managing" );
	return;
}

// public
//
void CLOCK_PageSelector::init()
{
	PRAlgoBase::ResetPRCounter();
	std::fill(PageQueue,PageQueue+BLCK_CNT,nullptr);
	CurrentNode = 0;
	Size = 0;
	MessageBus::Attach("NotifyVisitingPages",&CLOCK_PageSelector::NotifyVisitingPages,this);
}

void CLOCK_PageSelector::clear()
{
	PRAlgoBase::ResetPRCounter();
	std::fill(PageQueue,PageQueue+BLCK_CNT,nullptr);
	CurrentNode = 0;
	Size = 0;
}

int16_t CLOCK_PageSelector::size()
{
	return Size;
}

void CLOCK_PageSelector::NotifyVisitingPages(PageEntry* PagePtr)
{
	PagePtr->PageUniqueVariable = 1;
}

int16_t CLOCK_PageSelector::CurrentPageUniqueVar()
{
	return 0;
}

bool CLOCK_PageSelector::CheckPageFull()
{
	return  Size==BLCK_CNT;
}

bool CLOCK_PageSelector::CheckPagePtrExist(PageEntry *PagePtr)
{
	for(auto page:PageQueue)
	{
		if(PagePtr == page) return true;
	}
	return false;
}
