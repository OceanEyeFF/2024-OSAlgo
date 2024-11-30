/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoFIFO.cpp
#   Last Modified : 2024-11-30 16:08
#   Describe      : 
#
# ====================================================*/

#include <iterator>
#include <algorithm>
#include <iostream>
#include <queue>
#include "PRAlgoBase.h"
#include "PageEntry.h"
#include "PRAlgoFIFO.h"
#include "MessageBus.hpp"


//		FIFO_PageSelector Begin
// private
int16_t FIFO_PageSelector::AddNewPagePtr(PageEntry *PagePtr)
{
	PagePtr->PageUniqueVariable = CurrentPageUniqueVar();
	PageQueue.push(PagePtr);
	return 0;// Temporary Undefined
			 // To Do OE
			 // 可能是当前管理的页面数量
}

PageEntry* FIFO_PageSelector::GetReplacePagePtr()
{
	return PageQueue.front();
}

PageEntry* FIFO_PageSelector::RemoveReplacePagePtr()
{
	assert(!PageQueue.empty() && "Page Replacement Algo is running without Page");
	PageEntry* ret = PageQueue.front();
	PageQueue.pop();
	return ret;
}

void FIFO_PageSelector::RemovePagePtr(PageEntry* PagePtr) //可能对性能产生较大影响
														  //不建议在代码中调用
														  //如果queue的实现从std变成lazytag+无锁循环队列
														  //可以更简单的实现这个代码
{
	assert(!PageQueue.empty() && "Page Replacement Algo is running without Page");
	bool find = false;
	std :: queue<PageEntry*> TemporaryQueue;
	for(PageEntry* Value;!PageQueue.empty();)
	{
		Value = PageQueue.front();
		PageQueue.pop();
		if(Value == PagePtr)
		{
			find = true;
			continue;
		}
		TemporaryQueue.push(Value);
	}
	PageQueue = TemporaryQueue;
	assert(find && "Removing Page not Managing" );
}

// public
void FIFO_PageSelector::init()
{
	PageQueue = std::queue<PageEntry*>{};
	ResetPRCounter();
	MessageBus::Attach("NotifyVisitingPages",&FIFO_PageSelector::NotifyVisitingPages,this);
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

void FIFO_PageSelector::NotifyVisitingPages(PageEntry* PagePtr)
{
	// no need to do Action
	// Might Call Log
}

int16_t FIFO_PageSelector::CurrentPageUniqueVar()
{
	return 0;
}

bool FIFO_PageSelector::CheckPageFull()
{
	return PageQueue.size() == BLCK_CNT;
}

//DEBUG
bool FIFO_PageSelector::CheckPagePtrExist(PageEntry *PagePtr)
	//全遍历类代码都会在lazytag无锁循环队列中得到优化解决
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
