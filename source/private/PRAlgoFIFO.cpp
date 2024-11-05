/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoFIFO.cpp
#   Last Modified : 2024-11-05 13:07
#   Describe      : 
#
# ====================================================*/

#include <iterator>
#include <algorithm>
#include <iostream>
#include <queue>
#include "PRAlgoBase.h"
#include "PRAlgoFIFO.h"


//		FIFO_PageSelector Begin
//		Todo
void FIFO_PageSelector::init()
{
	PageQueue = std::queue<PageEntry*>{};
	ResetPRCounter();
}

void FIFO_PageSelector::clear()
{
	PageQueue = std::queue<PageEntry*>{};
	ResetPRCounter();
}

int16_t FIFO_PageSelector::size()
{
	return PageQueue.size();
}

int16_t FIFO_PageSelector::AddNewPagePtr(PageEntry *PagePtr)
{
	PagePtr->PageUniqueVariable = CurrentPageUniqueVar();
	PageQueue.push(PagePtr);
	return 0;// Temporary Undefined
			 // To Do OE
			 // 可能是当前管理的页面数量
}

int16_t FIFO_PageSelector::CurrentPageUniqueVar()
{
	return 0;
}

PageEntry* FIFO_PageSelector::GetReplacePagePtr()
{
	PageEntry *ret;
	ret = PageQueue.front();
	return ret;
}

bool FIFO_PageSelector::RemoveReplacePagePtr()
{
	bool ret = false;
	if(!PageQueue.empty())
	{
		ret = true;
		PageQueue.pop();
	}
	else
	{
	}

	return ret;
}

bool FIFO_PageSelector::RemovePagePtr(PageEntry* PagePtr)
{
	bool ret = false;
	std :: queue<PageEntry*> TemporaryQueue;
	for(PageEntry* Value;!PageQueue.empty();)
	{
		Value = PageQueue.front();
		PageQueue.pop();
		if(Value == PagePtr)
		{
			ret = true;
			continue;
		}
		TemporaryQueue.push(Value);
	}
	PageQueue = TemporaryQueue;
	return ret;

}

bool FIFO_PageSelector::CheckPageFull()
{
	return PageQueue.size() == BLCK_CNT;
}

//DEBUG
bool FIFO_PageSelector::CheckPagePtrExist(PageEntry *PagePtr)
{
	bool ret = false;
	std :: queue<PageEntry*> TemporaryQueue;
	for(PageEntry* Value;!PageQueue.empty();)
	{
		Value = PageQueue.front();
		PageQueue.pop();
		if(Value == PagePtr)
		{
			ret = true;
		}
		TemporaryQueue.push(Value);
	}
	PageQueue = TemporaryQueue;
	return ret;
}

//		FIFO_PageSelector End
