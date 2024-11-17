/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoLRU.cpp
#   Last Modified : 2024-11-16 11:55
#   Describe      : 
#
# ====================================================*/

#include "PRAlgoLRU.h"
#include "PageEntry.h"
#include "PageSystemGlobals.h"
#include <iterator>

// private
int16_t LRU_PageSelector::AddNewPagePtr(PageEntry* PagePtr)
{
	PagePtr->PageUniqueVariable = CurrentPageUniqueVar();
	PageList.push_back(PagePtr);
	PageListMap[PagePtr->FrameNumber] = std::prev(PageList.end());
	return 0;
}

PageEntry* LRU_PageSelector::GetReplacePagePtr()
{
	return PageList.front();
}

bool LRU_PageSelector::RemoveReplacePagePtr()
{
	bool ret=false;
	if(!PageList.empty())
	{
		ret = true;
		PageEntry* PagePtr = PageList.front();
		PageList.pop_front();
		PageListMap[PagePtr->FrameNumber] = PageList.end();
	}
	else
	{
	}

	return ret;
}

bool LRU_PageSelector::RemovePagePtr(PageEntry* PagePtr)
{
	bool ret = false;
	if(CheckPagePtrExist(PagePtr))
	{
		ret = true;
		PageList.erase(PageListMap[PagePtr->FrameNumber]);
		PageListMap[PagePtr->FrameNumber] = PageList.end();
	}
	else
	{
	}
	return  ret;
}

// public
void LRU_PageSelector::init()
{
	ResetPRCounter();
	PageList = std::list<PageEntry*>{};
	for(auto it:PageListMap)
	{
		it = PageList.end();
	}
}

void LRU_PageSelector::clear()
{
	ResetPRCounter();
	PageList = std::list<PageEntry*>{};
	for(auto it:PageListMap)
	{
		it = PageList.end();
	}
}

int16_t LRU_PageSelector::size()
{
	return PageList.size();
}

void LRU_PageSelector::NotifyVisitingPages(PageEntry *PagePtr)
{
	if(!CheckPagePtrExist(PagePtr)) return;
	std :: list<PageEntry*> :: iterator it;
	it = PageListMap[PagePtr->FrameNumber];
	if(it == PageList.end())
	{
	}
	else
	{
		PageList.erase(it);
	}

	PageList.push_back(PagePtr);
	PageListMap[PagePtr->PageUniqueVariable] = std::prev(PageList.end());
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
	return PageList.size() == BLCK_CNT;
}

// DEBUG
bool LRU_PageSelector::CheckPagePtrExist(PageEntry *PagePtr)
{
//	for(auto it:PageList) // 全遍历
//	{
//		if(it==PagePtr) return true;
//	}

	return PageListMap[PagePtr->FrameNumber]!=PageList.end();//算法查询
	return false;
}
