/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoIMPROVEDCLOCK.cpp
#   Last Modified : 2024-11-30 18:09
#   Describe      : 
#
# ====================================================*/

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iterator>
#include <vector>
#include <algorithm>
#include "PRAlgoIMPROVEDCLOCK.h"
#include "MyAlgo.hpp"
#include "PRAlgoBase.h"
#include "MessageBus.hpp"
#include "PageEntry.h"

// private
//

void IMPROVEDCLOCK_PageSelector::CalculateNewTemperature(uint8_t &Temperature)
{
	uint8_t ReHeatMarker = 1;
	int8_t shiftValue = 0;

	switch(Temperature>>6) // Recent Visit is at higher position
	{
		case 3:
			shiftValue +=2;
			break;
		case 2:
			shiftValue +=1;
			break;
	}
	switch((Temperature>>4) & 3) // Recent Visit is at higher position
	{
		case 3:
			shiftValue +=1;
			break;
	}
	switch(MyAlgo::BasicFunc::CountOnes((~Temperature)>>4))
	{
		case 3:
			shiftValue -=2;
			break;
		case 2:
			--shiftValue;
			break;
	}

	if(shiftValue>=0)
	{
		ReHeatMarker <<= shiftValue;
	}
	else
	{
		ReHeatMarker = 0;
	}
	Temperature=Temperature>>2 | ReHeatMarker<<4;
}

void IMPROVEDCLOCK_PageSelector::CalculatingNode()
{
	//CalculateNewTemperature((CurrentNode)->data->PageUniqueVariable);
	(CurrentNode)->data->PageUniqueVariable>>=1;
}

void IMPROVEDCLOCK_PageSelector::SteppingNode()
{
	CurrentNode=CurrentNode->next;
	if(CurrentNode == nullptr)
	{
		CurrentNode = PageList.getHead();
	}
}

int16_t IMPROVEDCLOCK_PageSelector::AddNewPagePtr(PageEntry* PagePtr)
{
	if(PageList.getSize()==0)
	{
		PageList.push_front(PagePtr);
		CurrentNode = PageList.getHead();
		PageListMap[PagePtr->FrameNumber] = CurrentNode;
	}
	else
	{
		PageList.insert(CurrentNode,PagePtr);
		PageListMap[PagePtr->FrameNumber] = CurrentNode->prev;
	}
	return 0;
}

PageEntry* IMPROVEDCLOCK_PageSelector::GetReplacePagePtr()		// 我觉得这一部分还可以改的更优美
{
	assert(PageList.getSize()>0 && "Page Replacement Algo is running without Page");

	// 初始化
	if(CurrentNode==nullptr)
	{
		CurrentNode = PageList.getHead();
	}
	// 对第一块扫描
	CalculatingNode();
	PageEntry* ret=CurrentNode->data;
	SteppingNode(); // node++
	//for(int i=0;i<floor(sqrt(BLCK_CNT));++i)
	for(int i=1;i<16;++i) // Scan A block
	{
		CalculatingNode();

		if( (CurrentNode->data)->PageUniqueVariable == ret->PageUniqueVariable )
		{
			if((CurrentNode->data)->isDirty())
			{
				ret = CurrentNode->data;
			}
		}

		if( (CurrentNode->data)->PageUniqueVariable < ret->PageUniqueVariable )
		{
			ret = CurrentNode->data;
		}

		SteppingNode(); // node++
	}

	if(ret->PageUniqueVariable>>4) // 如果是高温块扫描第二块内存
	{
		CalculatingNode();
		PageEntry* ret2=CurrentNode->data;
		SteppingNode(); // node++
		for(int i=1;i<16;++i) // Scan
		{
			CalculatingNode();

			if( (CurrentNode->data)->PageUniqueVariable == ret2->PageUniqueVariable )
			{
				if((CurrentNode->data)->isDirty())
				{
					ret2 = CurrentNode->data;
				}
			}

			if( (CurrentNode->data)->PageUniqueVariable < ret2->PageUniqueVariable )
			{
				ret2 = CurrentNode->data;
			}

			SteppingNode(); // node++
		}

		ret = (ret->PageUniqueVariable<=ret2->PageUniqueVariable)?ret:ret2;
	}
	return ret;
}

PageEntry* IMPROVEDCLOCK_PageSelector::RemoveReplacePagePtr()
{
	assert(PageList.getSize()>0 && "Page Replacement Algo is running without Page");

	PageEntry* ReplacePagePtr = GetReplacePagePtr();
	if(CurrentNode->data == ReplacePagePtr)
	{
		CurrentNode = CurrentNode->next;
		if(!CurrentNode)
		{
			CurrentNode = PageList.getHead();
		}
	}
	PageList.remove(PageListMap[ReplacePagePtr->FrameNumber]);
	PageListMap[ReplacePagePtr->FrameNumber] = nullptr;
	return ReplacePagePtr;

}

void IMPROVEDCLOCK_PageSelector::RemovePagePtr(PageEntry* PagePtr)
{
	assert(PageList.getSize()>0 && "Page Replacement Algo is running without Page");
	assert(CheckPagePtrExist(PagePtr) && "Removing Page not Managing" );

	if(CurrentNode->data == PagePtr)
	{
		CurrentNode = CurrentNode->next;
		if(!CurrentNode)
		{
			CurrentNode = PageList.getHead();
		}
	}
	PageList.remove(PageListMap[PagePtr->FrameNumber]);
	PageListMap[PagePtr->FrameNumber] = nullptr;
}

// public
//
void IMPROVEDCLOCK_PageSelector::init()
{
	PRAlgoBase::ResetPRCounter();
	PageList.clear();
	CurrentNode = PageList.getHead();
	for(auto it:PageListMap)
	{
		it = nullptr;
	}
	MessageBus::Attach("NotifyVisitingPages",&IMPROVEDCLOCK_PageSelector::NotifyVisitingPages,this);
}

void IMPROVEDCLOCK_PageSelector::clear()
{
	PRAlgoBase::ResetPRCounter();
	PageList.clear();
	CurrentNode = PageList.getHead();
	for(auto it:PageListMap)
	{
		it = nullptr;
	}
}

int16_t IMPROVEDCLOCK_PageSelector::size()
{
	return PageList.getSize();
}

void IMPROVEDCLOCK_PageSelector::NotifyVisitingPages(PageEntry* PagePtr)
{
	if(PagePtr->PageUniqueVariable&1)
	{
		PagePtr->PageUniqueVariable <<= 1;
	}
	PagePtr->PageUniqueVariable |= 1;
	++UpdateCounter;
	if(PageList.getSize()==1)
	{
		return;
	}

	DoublyLinkedList<PageEntry*>::Node* NodePtr;
	NodePtr = PageListMap[PagePtr->FrameNumber];
	if(CurrentNode==NodePtr)
	{
		CurrentNode = CurrentNode->next;
		if(CurrentNode==nullptr)
		{
			CurrentNode = PageList.getHead();
		}
	}
	PageList.remove(NodePtr);
//	NodePtr = nullptr;
//	PageListMap[PagePtr->FrameNumber] = nullptr;

	PageList.insert(CurrentNode,PagePtr);
	PageListMap[PagePtr->FrameNumber] = CurrentNode->prev;

}

int16_t IMPROVEDCLOCK_PageSelector::CurrentPageUniqueVar()
{
	return 0;
}

bool IMPROVEDCLOCK_PageSelector::CheckPageFull()
{
	return  PageList.getSize()==BLCK_CNT;
}

bool IMPROVEDCLOCK_PageSelector::CheckPagePtrExist(PageEntry *PagePtr)
{
	return PageListMap[PagePtr->FrameNumber]!=nullptr;//非严谨查询
	return false;
}
