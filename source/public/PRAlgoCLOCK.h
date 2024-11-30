/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoCLOCK.h
#   Last Modified : 2024-11-30 16:08
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _PRALGOCLOCK_H
#define  _PRALGOCLOCK_H

#include <vector>
#include <cstdint>
#include "PageEntry.h"
#include "PRAlgoBase.h"
#include "PageSystemGlobals.h"

class CLOCK_PageSelector: virtual public PRAlgoBase
{
	private:
		PageEntry* PageQueue[BLCK_CNT];
		int16_t CurrentNode;
		int16_t Size;

		int16_t AddNewPagePtr(PageEntry* PagePtr) override;
		PageEntry* GetReplacePagePtr() override;
		PageEntry* RemoveReplacePagePtr() override;
		void RemovePagePtr(PageEntry* PagePtr) override;

	public:
		void init() override;
		void clear() override;
		int16_t size() override;

		void NotifyVisitingPages(PageEntry *PagePtr) override;

		int16_t CurrentPageUniqueVar() override;

		bool CheckPageFull() override;

		//DEBUG
		bool CheckPagePtrExist(PageEntry *PagePtr) override;
};

#endif // _PRALGOCLOCK_H
	   //
	   //
