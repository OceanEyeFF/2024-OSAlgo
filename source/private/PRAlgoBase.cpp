/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoBase.cpp
#   Last Modified : 2024-10-31 22:56
#   Describe      : 
#
# ====================================================*/

#include <cstdint>
#include <iostream>
#include "PRAlgoBase.h"
#include "MyAlgo.hpp"
#include "PageEntry.h"
#include "VirtualMemorySystem.h"
#include "easylogging++.h"

//		PRAlgoBase Begin
//
//主要是缺页次数计数器相关的代码

void PRAlgoBase::increasePRCounter()
{
	PageReplacementCounter++;
}

int PRAlgoBase::GetPRCounter()
{
	return PageReplacementCounter;
}

void PRAlgoBase::ResetPRCounter()
{
	PageReplacementCounter = 0;
}

void PRAlgoBase::LOGUsingDefaultFunc()
{
	//CLOG(ERROR, "class PRAlgo") << "PRAlgoBase virtual function called";
}

void PRAlgoBase::SwapPages(PageEntry* PageMoveToMem, PageEntry* PageMoveOutofMem)
{
	VirtualMemorySystem::MemoryController::SwapBclks(PageMoveOutofMem->FrameNumber, PageMoveToMem->FrameNumber);

	//Update PageEntry info
	MyAlgo::BasicFunc::SwapTwoIntegers(PageMoveOutofMem->FrameNumber, PageMoveToMem->FrameNumber);
	PageMoveOutofMem->resetPresent();
	PageMoveToMem->setPresent();

	//Update Page Replacement Unit info
	RemovePagePtr(PageMoveOutofMem);
	AddNewPagePtr(PageMoveToMem);
}

void PRAlgoBase::SwapReplacedPagesAndSpecifiedPages(PageEntry* PageMoveToMem)
{
	PageEntry* PageMoveOutofMem = GetReplacePagePtr();
	VirtualMemorySystem::MemoryController::SwapBclks(PageMoveOutofMem->FrameNumber, PageMoveToMem->FrameNumber);

	//Update PageEntry info
	MyAlgo::BasicFunc::SwapTwoIntegers(PageMoveOutofMem->FrameNumber, PageMoveToMem->FrameNumber);
	PageMoveOutofMem->resetPresent();
	PageMoveToMem->setPresent();

	//Update Page Replacement Unit info
	RemovePagePtr(PageMoveOutofMem);
	AddNewPagePtr(PageMoveToMem);
}

void PRAlgoBase::PutPageInMem(PageEntry* PageIn)
{
	PageIn->FrameNumber = VirtualMemorySystem::MemoryController::MoveToLocalMem(PageIn->FrameNumber);
	PageIn->setPresent();
	AddNewPagePtr(PageIn);
}

void PRAlgoBase::TakePageOutofMem(PageEntry* PageOut)
{
	PageOut->FrameNumber = VirtualMemorySystem::MemoryController::MoveToDiskMem(PageOut->FrameNumber);
	PageOut->resetPresent();
	RemovePagePtr(PageOut);
}

// virtual function
void PRAlgoBase::init()
{
	// Init ReplacementCounter
	// Init Algo Var
	LOGUsingDefaultFunc();
}
void PRAlgoBase::clear()
{
	// Clear Page Entries' PageReplacement Unique Variables
	//
	// Clear Page Entries queue/priorityqueue/etc
	LOGUsingDefaultFunc();
}
int16_t PRAlgoBase::size()
{
	// Temporary PRAlgo Holding Function
	LOGUsingDefaultFunc();
	return 0;
}

int16_t PRAlgoBase::AddNewPagePtr(PageEntry* PagePtr)
{
	LOGUsingDefaultFunc();
	return 0;
}
int16_t PRAlgoBase::CurrentPageUniqueVar()
{
	LOGUsingDefaultFunc();
	return 0;
}
PageEntry* PRAlgoBase::GetReplacePagePtr()
{
	LOGUsingDefaultFunc();
	return nullptr;
}
bool PRAlgoBase::RemoveReplacePagePtr()
{
	LOGUsingDefaultFunc();
	return false;
}
bool PRAlgoBase::RemovePagePtr(PageEntry* PagePtr)
{
	LOGUsingDefaultFunc();
	return false;
}

bool PRAlgoBase::CheckPageFull()
{
	LOGUsingDefaultFunc();
	return false;
}

//DEBUG
bool PRAlgoBase::CheckPagePtrExist(PageEntry *PagePtr)
{
	LOGUsingDefaultFunc();
	return false;
}

void PRAlgoBase::LOGPrintPRCounter()
{
	//std::cout <<  PRAlgoBase::PageReplacementCounter << std::endl;
	//LOGPRINT
}

//		PRAlgoBase End
