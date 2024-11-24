/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoIMPROVEDCLOCK.h
#   Last Modified : 2024-11-24 02:08
#   Describe      : 使用dirtybit优化读取顺序
#					使用接近LRU的方法来记录额外的若干次访问
#					学习HotCold算法对尝试维护简易的时效性比较方法
#
# ====================================================*/

#pragma once

#ifndef  _PRALGOIMPROVEDCLOCK_H
#define  _PRALGOIMPROVEDCLOCK_H

#include <vector>
#include <list>
#include <cstdint>
#include "PageEntry.h"
#include "PRAlgoBase.h"
#include "PageSystemGlobals.h"
#include "MyAlgo.hpp"

class IMPROVEDCLOCK_PageSelector: virtual public PRAlgoBase
{
	private:
		MyAlgo::DoublyLinkedList<PageEntry*> PageList;
		MyAlgo::DoublyLinkedList<PageEntry*>::Node* CurrentNode;
		MyAlgo::DoublyLinkedList<PageEntry*>::Node* PageListMap[BLCK_CNT];

		int16_t UpdateCounter;

		int8_t CalculateNewTemperature(int8_t Temperature);
		void CaculatingNode();
		void SteppingNode();

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

#endif // _PRALGOIMPROVEDCLOCK_H
	   //
	   //
