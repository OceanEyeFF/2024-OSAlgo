/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoBase.h
#   Last Modified : 2024-11-30 16:06
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _PRALGOBASE_H
#define  _PRALGOBASE_H

#include <cstdint>
#include "PageEntry.h"
#include "MessageBus.hpp"

class PRAlgoBase
{
	private:
		int PageReplacementCounter;
		void increasePRCounter();
		//DEBUG
		void LOGPrintPRCounter();
		void LOGUsingDefaultFunc();

		// Functions : Operate on Record Container, Limited Access
		virtual int16_t AddNewPagePtr(PageEntry* PagePtr);// Operation Only Apply to Record Container
		virtual PageEntry* GetReplacePagePtr();			// Operation Only Apply to Record Container
		virtual PageEntry* RemoveReplacePagePtr();			// Operation Only Apply to Record Container
		virtual void RemovePagePtr(PageEntry* PagePtr);	// Operation Only Apply to Record Container
														//
	public:
		int GetPRCounter();
		void ResetPRCounter();
		void SwapPages(PageEntry* PageIn, PageEntry* PageOut);
		void SwapReplacedPagesAndSpecifiedPages(PageEntry* PageMoveToMem);

		void PutPageInMem(PageEntry* PageIn);
		void TakeReplacedPageOutofMem();
		void TakePageOutofMem(PageEntry* PageOut);

		void HandleFuncDeAllocMem(PageEntry* deAllocPage);

		virtual void init();
		virtual void clear();
		virtual int16_t size();

		virtual void NotifyVisitingPages(PageEntry* PagePtr);
		// use MessageBus To Call

		virtual int16_t CurrentPageUniqueVar();

		virtual bool CheckPageFull();

		//DEBUG
		virtual bool CheckPagePtrExist(PageEntry *PagePtr);
};

enum class EPageAlgoType
{
	eFIFO,
	eLRU,
	eClock,
	eImprovedClock
};

namespace PageReplacementAlgoGlobals
{
// PageAlgo Ptr
// Initialize When Begin
	extern PRAlgoBase* RuntimePageAlgo;
// PageAlgo Flag
	extern EPageAlgoType EPageAlgo;
	void SetPageAlgo(EPageAlgoType EType=EPageAlgoType::eImprovedClock);
}

#endif // _PRALGOBASE_H
	   //
	   //
