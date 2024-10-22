/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgo.h
#   Last Modified : 2024-10-23 02:06
#   Describe      : 
#
# ====================================================*/

#pragma once

#include "Page.h"
#ifndef  _PRALGO_H
#define  _PRALGO_H

#include <cstdint>
#include <algorithm>
#include <queue>

class AlgoBase
{
	private:
		int PageReplacementCounter;
		void increasePRCounter();
		void PrintPRCounter();
		int GetPRCounter();
		void ResetPRCounter();

	public:
		virtual int16_t AddNewPagePtr(PageEntry* PagePtr);
		virtual int16_t AddNewPage(int8_t PageID);
		virtual int16_t CurrentPageUniqueVar();
		virtual int8_t	GetReplacePageID();
		virtual void init();
};

class FIFO_Maintainer : virtual public AlgoBase
{
	private:
		std :: queue<PageEntry*> PageQueue;
	public:
		int16_t CurrentPageUniqueVar();
		int8_t GetReplacePageID();
};

#endif // _PRALGO_H
	   //
	   //
