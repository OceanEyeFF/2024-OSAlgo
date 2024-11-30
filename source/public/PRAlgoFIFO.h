/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PRAlgoFIFO.h
#   Last Modified : 2024-11-30 16:08
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

		int16_t AddNewPagePtr(PageEntry* PagePtr) override;
		PageEntry* GetReplacePagePtr() override;
		PageEntry* RemoveReplacePagePtr() override;
		void RemovePagePtr(PageEntry* PagePtr) override;
// Describer:
// int16_t AddNewPagePtr()
// 往管理器中放入一个页面指针，私有接口隔离
// 返回值是{当前未定义，未来大概率不需要返回值}
// PageEntry* GetReplacePagePtr()
// 获取当前状态下要拿出内存的内存块指针
// RemoveReplacePagePtr()
// RemovePagePtr(PageEntry* )
// 移除当前状态下要移出内存的指针
// 移除某一指定指针（用于deAlloc）

	public:
		void init() override;
		void clear() override;
		int16_t size() override;

		void NotifyVisitingPages(PageEntry* PagePtr) override;

		int16_t CurrentPageUniqueVar() override;

		bool CheckPageFull() override;

		//DEBUG
		bool CheckPagePtrExist(PageEntry *PagePtr) override;
};

#endif // _PRALGOFIFO_H
	   //
	   //
