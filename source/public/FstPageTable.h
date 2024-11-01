/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : FstPageTable.h
#   Last Modified : 2024-10-31 20:09
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
		~FstPageTable();

		// ToDo: 一次一个内存块
		AddressConj AllocNewPage();
		void deAllocPage(AddressConj AddrConj);

		// ToDo: 一次开辟多个内存块（大数组）
		// 需要解决： 如何在不影响程序段代码的指针正确性的前提下确保内存块连续
		// 1. 暂停进程
		// 2. 记录旧地址
		// 3. 整理内存（扫描内存，移动内存）
		// 4. 更新指针
		// 5. 恢复进程
		AddressConj AllocNewPages(uint16_t AllocBclkCnt);
		void deAllocPages(uint16_t);

		// ToDo: 读取一个内存块
		void Read(AddressConj AddrConj, char* Dst);
		void Write(AddressConj AddrConj, char* Src);

		// ToDo: 在指定内存块中读取若干位
		void Read(AddressConj AddrConj, char* Dst, size_t size);
		void Write(AddressConj AddrConj, char* Src, size_t size);

		char* GetPhysicalPtr(AddressConj AddrConj);
		// DEBUG
		// ToDo: 获取
		void CheckPageEntryStatus(AddressConj AddrConj);
};

#endif // _FSTPAGETABLE_H
	   //
	   //
