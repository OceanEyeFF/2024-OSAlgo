/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoBase.cpp
#   Last Modified : 2024-11-16 11:54
#   Describe      : 
#
# ====================================================*/

#include "PRAlgoBase.h"
#include <cstdint>
#include <iostream>
#include "PRAlgo.h"
#include "MyAlgo.hpp"
#include "PRAlgoLRU.h"
#include "PageEntry.h"
#include "VirtualMemorySystem.h"
#include "easylogging++.h"

//		PRAlgoBase Begin
//
//主要是缺页次数计数器相关的代码

// Private
void PRAlgoBase::increasePRCounter()
{
	PageReplacementCounter++;
}

void PRAlgoBase::LOGUsingDefaultFunc()
{
	CLOG(ERROR, "class PRAlgo") << "PRAlgoBase virtual function called";
}

//Public
int PRAlgoBase::GetPRCounter()
{
	return PageReplacementCounter;
}
void PRAlgoBase::ResetPRCounter()
{
	PageReplacementCounter = 0;
}

void PRAlgoBase::SwapPages(PageEntry* PageMoveToMem, PageEntry* PageMoveOutofMem)
{
	VirtualMemorySystem::MemoryController::SwapBclks(PageMoveOutofMem->FrameNumber, PageMoveToMem->FrameNumber);

	// Update Page Replacement Unit
	// Page Replacement Algo Only Manage PageEntry pointers
	RemovePagePtr(PageMoveOutofMem);
	AddNewPagePtr(PageMoveToMem);

	//Update PageEntry info
	MyAlgo::BasicFunc::SwapTwoIntegers(PageMoveOutofMem->FrameNumber, PageMoveToMem->FrameNumber);
	PageMoveOutofMem->resetPresent();
	PageMoveToMem->setPresent();

}

void PRAlgoBase::SwapReplacedPagesAndSpecifiedPages(PageEntry* PageMoveToMem)
{
	increasePRCounter();
	PageEntry* PageMoveOutofMem = GetReplacePagePtr();
	VirtualMemorySystem::MemoryController::SwapBclks(PageMoveOutofMem->FrameNumber, PageMoveToMem->FrameNumber);

	//Update Page Replacement Unit info
	// Page Replacement Algo Only Manage PageEntry pointers
	RemovePagePtr(PageMoveOutofMem);
	AddNewPagePtr(PageMoveToMem);

	//Update PageEntry info
	MyAlgo::BasicFunc::SwapTwoIntegers(PageMoveOutofMem->FrameNumber, PageMoveToMem->FrameNumber);
	PageMoveOutofMem->resetPresent();
	PageMoveToMem->setPresent();
}

void PRAlgoBase::PutPageInMem(PageEntry* PageIn)
{
	increasePRCounter();
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

void PRAlgoBase::HandleFuncDeAllocMem(PageEntry* deAllocPage)
{
	RemovePagePtr(deAllocPage);
}

// virtual function
// Private Virtual
int16_t PRAlgoBase::AddNewPagePtr(PageEntry* PagePtr)
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

// Describer:
// int16_t AddNewPagePtr()
// 往管理器中放入一个页面指针，私有接口隔离
// 返回值是{当前未定义，未来大概率不需要返回值}
// PageEntry* GetReplacePagePtr()
// 获取当前状态下要拿出内存的内存块指针
// RemoveReplacePagePtr()
// RemovePagePtr(PageEntry* )
// 移除当前状态下要移出内存的指针
// 移除某一指定指针（用于deAlloc）

// Public Virtual
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


void PRAlgoBase::NotifyVisitingPages(PageEntry* PagePtr)
{
	LOGUsingDefaultFunc();
	// if no need to do Action just Leave empty
}

int16_t PRAlgoBase::CurrentPageUniqueVar()
{
	LOGUsingDefaultFunc();
	return 0;
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
//
//		PRAlgoGlobals Begin

namespace PageReplacementAlgoGlobals
{
// PageAlgo Ptr
// Initialize When Begin
	PRAlgoBase* RuntimePageAlgo = nullptr;
// PageAlgo Flag
	EPageAlgoType EPageAlgo;

	void SetPageAlgo(EPageAlgoType EType)
	{
		EPageAlgo = EType;
		switch(EPageAlgo)
		{
			case EPageAlgoType::eFIFO :
				RuntimePageAlgo = new FIFO_PageSelector;
				break;
			case EPageAlgoType::eLRU :
				RuntimePageAlgo = new LRU_PageSelector;
				break;
			case EPageAlgoType::eClock :
	//			RuntimePageAlgo = new FIFO_PageSelector;
				break;
			case EPageAlgoType::eImprovedClock :
	//			RuntimePageAlgo = new FIFO_PageSelector;
				break;
		}
		RuntimePageAlgo->init();
	}
}

