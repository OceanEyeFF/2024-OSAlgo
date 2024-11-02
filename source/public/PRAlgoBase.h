/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoBase.h
#   Last Modified : 2024-11-02 21:13
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _PRALGOBASE_H
#define  _PRALGOBASE_H

#include <cstdint>
#include "PageEntry.h"

class PRAlgoBase
{
	private:
		int PageReplacementCounter;
		void increasePRCounter();
		//DEBUG
		void LOGPrintPRCounter();
		void LOGUsingDefaultFunc();

	public:
		int GetPRCounter();
		void ResetPRCounter();
		void SwapPages(PageEntry* PageIn, PageEntry* PageOut);
		void SwapReplacedPagesAndSpecifiedPages(PageEntry* PageMoveToMem);

		void PutPageInMem(PageEntry* PageIn);
		void TakePageOutofMem(PageEntry* PageOut);

		virtual void init();
		virtual void clear();
		virtual int16_t size();

		virtual int16_t AddNewPagePtr(PageEntry* PagePtr);
		virtual int16_t CurrentPageUniqueVar();
		virtual PageEntry* GetReplacePagePtr();
		virtual bool RemoveReplacePagePtr();
		virtual bool RemovePagePtr(PageEntry* PagePtr);

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
