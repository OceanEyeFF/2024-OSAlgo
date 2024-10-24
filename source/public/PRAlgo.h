/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgo.h
#   Last Modified : 2024-10-24 09:24
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _PRALGO_H
#define  _PRALGO_H

#include "Page.h"
#include <cstdint>
#include <algorithm>
#include <queue>
#include <iostream>

class PRAlgoBase
{
	private:
		int PageReplacementCounter;
		void increasePRCounter();

		//DEBUG
		void LOGPrintPRCounter();

	public:
		void PrintPRCounter();
		int GetPRCounter();
		void ResetPRCounter();

		virtual void init();
		virtual void clear();
		virtual int16_t size();

		virtual int16_t AddNewPagePtr(PageEntry* PagePtr);
		virtual int16_t AddNewPageID(int8_t PageID);
		virtual int16_t CurrentPageUniqueVar();
		virtual PageEntry * GetReplacePagePtr();
		virtual int8_t	GetReplacePageID(PageEntry* PagePtrBegin);
		virtual bool RemoveReplacePagePtr();
		virtual bool RemovePagePtr(PageEntry* PagePtr);

		//DEBUG
		virtual PageEntry* CheckReplacePagePtr();
		virtual void PrintReplacePageInfo();
		virtual int8_t CheckReplacePageID();
		virtual bool CheckPagePtrExist(PageEntry *PagePtr);

		virtual void AlgoLOGPrint();
};

class FIFO_Maintainer : virtual public PRAlgoBase // To DO
												  //
{
	private:
		std :: queue<PageEntry*> PageQueue;
	public:
		void init();
		void clear();
		int16_t size();

		int16_t AddNewPagePtr(PageEntry* PagePtr);
		int16_t AddNewPageID(int8_t PageID);
		int16_t CurrentPageUniqueVar();
		PageEntry* GetReplacePagePtr();
		int8_t	GetReplacePageID(PageEntry* PagePtrBegin);
		bool RemovePagePtr(PageEntry* PagePtr);
};

#endif // _PRALGO_H
	   //
	   //
