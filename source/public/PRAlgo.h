/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgo.h
#   Last Modified : 2024-10-25 22:32
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _PRALGO_H
#define  _PRALGO_H

#include <queue>
#include <cstdint>
#include "Page.h"

struct PageEntry;

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
		virtual int16_t CurrentPageUniqueVar();
		virtual PageEntry* GetReplacePagePtr();
		virtual bool RemoveReplacePagePtr();
		virtual bool RemovePagePtr(PageEntry* PagePtr);

		//DEBUG
		virtual bool CheckPagePtrExist(PageEntry *PagePtr);
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
		int16_t CurrentPageUniqueVar();
		PageEntry* GetReplacePagePtr();
		bool RemoveReplacePagePtr();
		bool RemovePagePtr(PageEntry* PagePtr);

		//DEBUG
		virtual bool CheckPagePtrExist(PageEntry *PagePtr);
};

#endif // _PRALGO_H
	   //
	   //
