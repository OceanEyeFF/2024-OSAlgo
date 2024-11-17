/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoLRU.h
#   Last Modified : 2024-11-15 23:18
#   Describe      : 
#
# ====================================================*/

#ifndef  _PRALGOLRU_H
#define  _PRALGOLRU_H

#include <list>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cstdint>
#include "PageEntry.h"
#include "PRAlgoBase.h"
#include "PageSystemGlobals.h"

class LRU_PageSelector: virtual public PRAlgoBase
{
	private:
		std :: list<PageEntry*> PageList;
		std :: list<PageEntry*> :: iterator PageListMap[BLCK_CNT];	// 每个内存块下标有对应的回指指针
																	// 在内存读写操作时
																	// 调用NotifyVisitingPages
																	// 删除原有指针
																	// List尾部增加PageEntry指针
																	// 回指指针指向新指针

		int16_t AddNewPagePtr(PageEntry* PagePtr) override;
		PageEntry* GetReplacePagePtr() override;
		bool RemoveReplacePagePtr() override;
		bool RemovePagePtr(PageEntry* PagePtr) override;

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

#endif // _PRALGOLRU_H
	   //
	   //
