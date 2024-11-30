/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : MemInterface.h
#   Last Modified : 2024-11-29 09:00
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _MEMINTERFACE_H
#define  _MEMINTERFACE_H

#include <cstddef>
#include <bitset>
#include "FstPageTable.h"
#include "PageSystemGlobals.h"

class PCB_MemInterface
{
	private:
	FstPageTable FirstPageTable;
	AddressPtr PtrPool[256];
	std::bitset<256> IsNull;


	public:
		PCB_MemInterface();

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
										  // 
		bool Read(char* Dst, AddressPtr AddrPtr);
		bool Write(char* Src, AddressPtr AddrPtr);

		bool Read(char* Dst, AddressPtr AddrPtr, size_t size);
		bool Write(char* Src, AddressPtr AddrPtr, size_t size);

		char* GetPhysicalPtr(AddressPtr AddrPtr);

		bool Alloc(int Poolid);			  // Alloc某一个指定的内存块
		bool deAlloc(int Poolid);		  // deAlloc某一个指定的内存块
		bool Read(char* Dst, int Poolid); // 读取某一个指定的内存块
		bool Write(char* Src, int Poolid);// 写入某一个指定的内存块

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
