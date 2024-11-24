/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoLRU.cpp
#   Last Modified : 2024-11-23 23:52
#   Describe      : 
#
# ====================================================*/

#include <iterator>
#include "PRAlgoLRU.h"
#include "PageEntry.h"
#include "PageSystemGlobals.h"
#include "MessageBus.hpp"
#include "MyAlgo.hpp"

// private
int16_t LRU_PageSelector::AddNewPagePtr(PageEntry* PagePtr)
{
	PagePtr->PageUniqueVariable = CurrentPageUniqueVar();
	PageList.push_back(PagePtr);
	PageListMap[PagePtr->FrameNumber] = PageList.getTail();
	return 0;
}

PageEntry* LRU_PageSelector::GetReplacePagePtr()
{
	assert(PageList.getSize()>0 && "Page Replacement Algo is running without Page");
	return PageList.getHead()->data;
}

PageEntry* LRU_PageSelector::RemoveReplacePagePtr()
{
	assert(PageList.getSize()>0 && "Page Replacement Algo is running without Page");
	PageEntry* PagePtr = PageList.getHead()->data;
	PageList.pop_front();
	PageListMap[PagePtr->FrameNumber] = nullptr;
	return PagePtr;
}

void LRU_PageSelector::RemovePagePtr(PageEntry* PagePtr)
{
	assert(PageList.getSize()>0 && "Page Replacement Algo is running without Page");
	assert(CheckPagePtrExist(PagePtr) && "Removing Page not Managing" );
	PageList.remove(PageListMap[PagePtr->FrameNumber]);
	PageListMap[PagePtr->FrameNumber] = nullptr;
}

// public
void LRU_PageSelector::init()
{
	ResetPRCounter();
	PageList.clear();
	for(auto it:PageListMap)
	{
		it = nullptr;
	}
	MessageBus::Attach("NotifyVisitingPages",&LRU_PageSelector::NotifyVisitingPages,this);
}

void LRU_PageSelector::clear()
{
	ResetPRCounter();
	PageList.clear();
	for(auto it:PageListMap)
	{
		it = nullptr;
	}
}

int16_t LRU_PageSelector::size()
{
	return PageList.getSize();
}

void LRU_PageSelector::NotifyVisitingPages(PageEntry *PagePtr)
{
	if(!CheckPagePtrExist(PagePtr)) return;
	MyAlgo::DoublyLinkedList<PageEntry*>::Node* it = PageListMap[PagePtr->FrameNumber];
	if(it == nullptr)
	{
	}
	else
	{
		PageList.remove(it);
	}

	AddNewPagePtr(PagePtr);
}

int16_t LRU_PageSelector::CurrentPageUniqueVar()
{
	return 0;
	// LRU 本来应该存储指针地址但是设计上是16位实际是64位的一个大地址所以返回0
	// 这里用了讨巧的设计（参考头文件说明）
	//
}

bool LRU_PageSelector::CheckPageFull()
{
	return PageList.getSize() == BLCK_CNT;
}

// DEBUG
bool LRU_PageSelector::CheckPagePtrExist(PageEntry *PagePtr)
{
	return PageListMap[PagePtr->FrameNumber]!=nullptr;//算法查询
}
