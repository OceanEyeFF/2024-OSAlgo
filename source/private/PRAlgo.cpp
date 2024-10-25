/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgo.cpp
#   Last Modified : 2024-10-25 22:37
#   Describe      : 
#
# ====================================================*/

#include "PRAlgo.h"
#include <iterator>
#include <algorithm>
#include <iostream>
#include <queue>

//		PRAlgoBase Begin
//
//主要是缺页次数计数器相关的代码

void PRAlgoBase::increasePRCounter()
{
	PageReplacementCounter++;
}

void PRAlgoBase::PrintPRCounter()
{
	std::cout <<  PRAlgoBase::PageReplacementCounter << std::endl;
}

int PRAlgoBase::GetPRCounter()
{
	return PageReplacementCounter;
}

void PRAlgoBase::ResetPRCounter()
{
	PageReplacementCounter = 0;
}

//DEBUG
void PRAlgoBase::LOGPrintPRCounter()
{
	//std::cout <<  PRAlgoBase::PageReplacementCounter << std::endl;
	//LOGPRINT
}

//		PRAlgoBase End

//		FIFO_Maintainer Begin
//		Todo
void FIFO_Maintainer::init()
{
	PageQueue = std::queue<PageEntry*>{};
	ResetPRCounter();
}

void FIFO_Maintainer::clear()
{
	PageQueue = std::queue<PageEntry*>{};
	ResetPRCounter();
}

int16_t FIFO_Maintainer::size()
{
	return PageQueue.size();
}

int16_t FIFO_Maintainer::AddNewPagePtr(PageEntry *PagePtr)
{
	PagePtr->PageUniqueVariable = CurrentPageUniqueVar();
	PageQueue.push(PagePtr);
	return 0;// Temporary Undefined
			 // To Do OE
			 // 可能是当前管理的页面数量
}

int16_t FIFO_Maintainer::CurrentPageUniqueVar()
{
	return 0;
}

PageEntry* FIFO_Maintainer::GetReplacePagePtr()
{
	PageEntry *ret;
	ret = PageQueue.front();
	return ret;
}

bool FIFO_Maintainer::RemoveReplacePagePtr()
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

bool FIFO_Maintainer::RemovePagePtr(PageEntry* PagePtr)
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

bool FIFO_Maintainer::CheckPagePtrExist(PageEntry *PagePtr)
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

//		FIFO_Maintainer End
