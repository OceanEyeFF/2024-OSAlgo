/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : main.cpp
#   Last Modified : 2024-11-07 16:37
#   Describe      : 
#
# ====================================================*/
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "PRAlgo.h"
#include "PRAlgoBase.h"
#include "PageSystemGlobals.h"
#include "MemInterface.h"
#include "VirtualMemorySystem.h"

#define WIN32_LEAN_AND_MEAN
#include "libgo/coroutine.h"
#include "easylogging++.h"

void RunTest()
	// 测试标准：
	// 创造A B两个PCB
	// Alloc 需要搭配 ReadWrite进行可读写检查
	// 1. 检查普通操作 Alloc Write Read deAlloc deAlloc
	// A 执行所有操作
	// 2. 检查Alloc顺序
	// A Alloc 256次
	// A 执行所有操作
	// 3. 验证多PCB下的内存页面置换
	// B Alloc 256次
	// B 执行所有操作（触发缺页中断
	// 4. 验证内存页面置换后缓存页面的有效性
	// A Read操作调入内存（触发缺页中断
	// B Read操作调入内存（触发缺页中断
	// 5. 获取物理内存地址
	// 验证物理内存的块排布是否正确
{
	// 创建一个PCB_MemInterface
	PCB_MemInterface TestPCB_A;
	// 1. 检查普通操作 Alloc Write Read deAlloc deAlloc
	AddressPtr Ptr1 = TestPCB_A.Alloc();
	int opt = 0;
	char Source[256];
	char Buffer[256];
	std::memset(Source,0,sizeof(Source));
	std::memset(Buffer,0,sizeof(Buffer));
	std::strcpy(Source,"RunTest1(1st write to memory)");
	TestPCB_A.Write(Source,Ptr1);
	TestPCB_A.Read(Buffer,Ptr1);
	std :: cout << opt++ << "\t:\t" << Buffer << std::endl;
	TestPCB_A.deAlloc(Ptr1);

	// 检查deAlloc后的读取是否触发Illegal Access
	std::memset(Source,0,sizeof(Source));
	std::memset(Buffer,0,sizeof(Buffer));
	std::strcpy(Source,"RunTest1(1st ILLEGAL write to memory)");
	TestPCB_A.Write(Source,Ptr1);
	TestPCB_A.Read(Buffer,Ptr1);
	std :: cout << opt++ << "\t:\t"  << Buffer << std::endl;

	// 检查是否deAlloc后清零
	std::memset(Source,0,sizeof(Source));
	std::memset(Buffer,0,sizeof(Buffer));
	std::strcpy(Source,"RunTest1(2nd write to memory)");
	TestPCB_A.Alloc(Ptr1);
	TestPCB_A.Read(Buffer,Ptr1);
	std :: cout << opt++ << "\t:\t"  << Buffer << std::endl;
	TestPCB_A.Write(Source,Ptr1);
	TestPCB_A.Read(Buffer,Ptr1);
	std :: cout << opt++ << "\t:\t"  << Buffer << std::endl;
	TestPCB_A.deAlloc(Ptr1);

	// 2. 检查Alloc顺序
	AddressPtr PtrList[3][260];
	for(int i=0;i<256;++i)
	{
		PtrList[0][i] = TestPCB_A.Alloc();
//		std :: cout << "A Ptr" << i << ":\t" << PtrList[0][i].__ptr__ << std::endl;
	}
	std::strcpy(Source,"RunTest2(PCB A Page ---- Write)");
	std::string NUMSTR;

	for(int i=0;i<256;++i)
	{
		NUMSTR = std::to_string(i);
		std::memcpy(Source+20,NUMSTR.c_str(),sizeof(NUMSTR)-1);
		TestPCB_A.Write(Source,PtrList[0][i]);
	}
	for(int i=0;i<256;++i)
	{
		TestPCB_A.Read(Buffer,PtrList[0][i]);
		std :: cout << Buffer << std::endl;
	}

	std :: cout << PageReplacementAlgoGlobals::RuntimePageAlgo->CheckPageFull() << std::endl;

	// 3. 验证多PCB下的内存页面置换
	PCB_MemInterface TestPCB_B;
	for(int i=0;i<256;++i)
	{
		PtrList[1][i] = TestPCB_B.Alloc();
//		std :: cout << "B Ptr" << i << ":\t" << PtrList[1][i].__ptr__ << std::endl;
	}

	std::strcpy(Source,"RunTest3(PCB B Page ---- Write)");

	for(int i=0;i<256;++i)
	{
		NUMSTR = std::to_string(i);
		std::memcpy(Source+20,NUMSTR.c_str(),sizeof(NUMSTR.c_str())-1);
		TestPCB_B.Write(Source,PtrList[1][i],sizeof(Source));
	}

	for(int i=0;i<256;++i)
	{
		TestPCB_B.Read(Buffer,PtrList[1][i]);
		std :: cout << Buffer << std::endl;
	}

	// 4. 验证内存页面置换后缓存页面的有效性
	for(int i=0;i<256;++i)
	{
		TestPCB_A.Read(Buffer,PtrList[0][i]);
		std :: cout << Buffer << std::endl;
	}

	for(int i=0;i<256;++i)
	{
		TestPCB_B.Read(Buffer,PtrList[1][i]);
		std :: cout << Buffer << std::endl;
	}

	// 5. 获取物理内存地址
	// 验证物理内存的块排布是否正确
	
	// B应该在内存中
	for(int i=0;i<256;++i)
	{
		std :: cout << static_cast<void*>(TestPCB_B.GetPhysicalPtr(PtrList[1][i])) << std::endl;
	}


	// A应该在缓存中
	for(int i=0;i<256;++i)
	{
		std :: cout << static_cast<void*>(TestPCB_A.GetPhysicalPtr(PtrList[0][i])) << std::endl;
	}

	// 6. 内存块deAlloc测试，验证是否正确deAlloc
	std :: memset(Buffer,0,sizeof(Buffer));

	for(int i=0;i<256;++i)
	{
		TestPCB_B.deAlloc(PtrList[1][i]);
	}

	for(int i=0;i<256;++i)
	{
		TestPCB_B.Read(Buffer,PtrList[1][i]);
		std :: cout << Buffer << std::endl;
	}

	for(int i=0;i<256;++i)
	{
		TestPCB_A.deAlloc(PtrList[0][i]);
	}

	for(int i=0;i<256;++i)
	{
		TestPCB_A.Read(Buffer,PtrList[0][i]);
		std :: cout << Buffer << std::endl;
	}
}

INITIALIZE_EASYLOGGINGPP
int main()
{
	std::cout << "Hello World" << std::endl;

	// Easy Logging plusplus Settings
#if defined(DEBUG)
	el::Configurations conf("../ConfigFile/easyLogging++/debug.conf");
	el::Loggers::reconfigureAllLoggers(conf);
#elif defined(RELEASE)
	el::Configurations conf("../ConfigFile/easyLogging++/release.conf");
	el::Loggers::reconfigureAllLoggers(conf);
#endif


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
