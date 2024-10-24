/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgo.cpp
#   Last Modified : 2024-10-24 12:40
#   Describe      : 
#
# ====================================================*/

#include "PRAlgo.h"

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
}

void FIFO_Maintainer::clear()
{
	PageQueue = std::queue<PageEntry*>{};
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

int8_t	FIFO_Maintainer::GetReplacePageID(PageEntry* PagePtrBegin)
{
	PageEntry *ret;
	ret = PageQueue.front();
	return ret-PagePtrBegin;
}
//		FIFO_Maintainer End
