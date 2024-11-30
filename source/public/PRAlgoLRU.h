/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoLRU.h
#   Last Modified : 2024-11-30 16:09
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _PRALGOLRU_H
#define  _PRALGOLRU_H

#include <list>
#include <cstdint>
#include "PageEntry.h"
#include "PRAlgoBase.h"
#include "PageSystemGlobals.h"
#include "MyAlgo.hpp"

class LRU_PageSelector: virtual public PRAlgoBase
{
	private:
		DoublyLinkedList<PageEntry*> PageList;
//		std :: list<PageEntry*> PageList;							// Deprecated Due to std list
																	// does not provide
																	// stable iterators
																	// when making list operations
		DoublyLinkedList<PageEntry*>::Node* PageListMap[BLCK_CNT];
//		std :: list<PageEntry*> :: iterator PageListMap[BLCK_CNT];	// 每个内存块下标有对应的回指指针
																	// 在内存读写操作时
																	// 调用NotifyVisitingPages
																	// 删除原有指针
																	// List尾部增加PageEntry指针
																	// 回指指针指向新指针

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

#endif // _PRALGOLRU_H
	   //
	   //
