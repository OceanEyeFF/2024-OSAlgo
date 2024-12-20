/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : FstPageTable.h
#   Last Modified : 2024-11-28 23:36
#   Describe      : 
#
# ====================================================*/

#ifndef  _FSTPAGETABLE_H
#define  _FSTPAGETABLE_H

#include "PageSystemGlobals.h"
#include "PageContainer.h"

class FstPageTable
{
	private:
		PageContainer Table[4];

		void HandleMissingPage();
	public:

		FstPageTable();

		// ToDo: 一次一个内存块
		AddressConj AllocNewPage();
		bool AllocNewPage(AddressConj AddrConj);
		bool deAllocPage(AddressConj AddrConj);

		// ToDo: 一次开辟多个内存块（大数组）
		// 需要解决： 如何在不影响程序段代码的指针正确性的前提下确保内存块连续
		// 1. 暂停进程
		// 2. 记录旧地址
		// 3. 整理内存（扫描内存，移动内存）
		// 4. 更新指针
		// 5. 恢复进程
		// AddressConj AllocNewPages(uint16_t AllocBclkCnt);
		// bool deAllocPages(uint16_t);

		bool Read(AddressConj AddrConj, char* Dst);
		bool Write(AddressConj AddrConj, char* Src);

		bool Read(AddressConj AddrConj, char* Dst, size_t size);
		bool Write(AddressConj AddrConj, char* Src, size_t size);

		char* GetPhysicalPtr(AddressConj AddrConj);
		// DEBUG
		// ToDo: 获取
		void CheckPageEntryStatus(AddressConj AddrConj);
};

#endif // _FSTPAGETABLE_H
	   //
	   //
