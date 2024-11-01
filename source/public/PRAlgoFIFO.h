/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoFIFO.h
#   Last Modified : 2024-10-29 22:16
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _PRALGOFIFO_H
#define  _PRALGOFIFO_H

#include <queue>
#include <cstdint>
#include "PageEntry.h"
#include "PRAlgoBase.h"

class FIFO_PageSelector: virtual public PRAlgoBase
{
	private:
		std :: queue<PageEntry*> PageQueue;
	public:
		void init() override;
		void clear() override;
		int16_t size() override;

		int16_t AddNewPagePtr(PageEntry* PagePtr) override;
		int16_t CurrentPageUniqueVar() override;
		PageEntry* GetReplacePagePtr() override;
		bool RemoveReplacePagePtr() override;
		bool RemovePagePtr(PageEntry* PagePtr) override;

		bool CheckPageFull() override;

		//DEBUG
		bool CheckPagePtrExist(PageEntry *PagePtr) override;
};

#endif // _PRALGOFIFO_H
	   //
	   //
