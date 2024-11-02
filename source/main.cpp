/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : main.cpp
#   Last Modified : 2024-11-02 21:16
#   Describe      : 
#
# ====================================================*/

#include <cstring>
#include <iostream>
#include <thread>
#include <mutex>
#include <coroutine>
#include "PRAlgo.h"
#include "PRAlgoBase.h"
#include "PageSystemGlobals.h"
#include "MemInterface.h"
#include "VirtualMemorySystem.h"

void RunTest()
	// 测试标准：
	// 创造A B两个PCB
	// 1. 检查普通操作 Alloc Write Read deAlloc deAlloc
	// A 执行所有操作
	// 2. 检查Alloc顺序
	// A Alloc 128次
	// A （deAlloc+Alloc） 128次
	// 3. 检查后半段顺序Alloc和deAlloc
	// A Alloc 128次
	// A deAlloc 后（0-256）128次
	// A Alloc 128次
	// 4. Write检查
	// 5. Read检查
{
	// 创建一个PCB_MemInterface
	PCB_MemInterface TestPCB_A;
	// 1. 检查普通操作 Alloc Write Read deAlloc deAlloc
	AddressPtr Ptr1 = TestPCB_A.Alloc();
	char Source[256];
	char Buffer[256];
	std::memset(Source,0,sizeof(Source));
	std::memset(Buffer,0,sizeof(Buffer));
	std::strcpy(Source,"RunTest()");
	TestPCB_A.Write(Source,Ptr1);
	TestPCB_A.Read(Buffer,Ptr1);
	std :: cout << Buffer << std::endl;
	// 2. 检查Alloc顺序
}

int main()
{
	std::cout << "Hello World" << std::endl;

	// Easy Logging plusplus Settings

	// MemorySystem Settings
	VirtualMemorySystem::init();
	PageReplacementAlgoGlobals::SetPageAlgo(EPageAlgoType::eFIFO);

	// RunTest

	RunTest();
	// TestResult

	// RunTask
	
	// TaskResults

	return 0;
}
