/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : MemInterface.h
#   Last Modified : 2024-11-02 20:53
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _MEMINTERFACE_H
#define  _MEMINTERFACE_H

#include "FstPageTable.h"
#include "PageSystemGlobals.h"
#include <cstddef>

class PCB_MemInterface
{
	FstPageTable FirstPageTable;
	public:

		AddressPtr Alloc();				  // 假如中途没有deAlloc应该是顺序从小到大返回对应指针
										  //
		bool Alloc(AddressPtr AddrPtr);	  // Alloc指定位置内存
										  // 返回值用于确定该位置所属PageEntry是否被开辟
										  //
		bool deAlloc(AddressPtr AddrPtr); // bool类型，返回要dealloc操作是否合法
										  // 在本程序中仅判断是否在对应位置上开辟过内存
										  // 有两种基本的非法情形
										  // 1. 错误的释放了还没有开辟的内存
										  // 2. 已经释放过的内存块重复释放

		void Read(char* Dst, AddressPtr AddrPtr);
		void Write(char* Src, AddressPtr AddrPtr);

		void Read(char* Dst, AddressPtr AddrPtr, size_t size);
		void Write(char* Src, AddressPtr AddrPtr, size_t size);

		void MoveIntoMem();
		void MoveOutofMem();
		//DEBUG
		//
		void CheckPtrStatus();
		void CheckMemStatus();
};

#endif // _MEMINTERFACE_H
	   //
	   //
