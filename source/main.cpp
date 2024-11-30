/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : main.cpp
#   Last Modified : 2024-11-30 02:22
#   Describe      : 
#
# ====================================================*/
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "MyAlgo.hpp"
#include "PRAlgo.h"
#include "PRAlgoBase.h"
#include "PageSystemGlobals.h"
#include "MemInterface.h"
#include "VirtualMemorySystem.h"
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
	bool res=false;
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
	res=TestPCB_A.Write(Source,Ptr1);
	std :: cout << (res?1:0) << std::endl;
	res=TestPCB_A.Read(Buffer,Ptr1);
	std :: cout << (res?1:0) << " " << Buffer << std::endl;
	res=TestPCB_A.deAlloc(Ptr1);
	std :: cout << (res?1:0) << std::endl;

	// 检查deAlloc后的读取是否触发Illegal Access
	std::memset(Source,0,sizeof(Source));
	std::memset(Buffer,0,sizeof(Buffer));
	std::strcpy(Source,"RunTest1(1st ILLEGAL write to memory)");
	res=TestPCB_A.Write(Source,Ptr1);
	std :: cout << (res?1:0) << std::endl;
	res=TestPCB_A.Read(Buffer,Ptr1);
	std :: cout << (res?1:0) << " " << Buffer << std::endl;

	// 检查是否deAlloc后清零
	std::memset(Source,0,sizeof(Source));
	std::memset(Buffer,0,sizeof(Buffer));
	std::strcpy(Source,"RunTest1(2nd write to memory)");
	res=TestPCB_A.Alloc(Ptr1);
	std :: cout << (res?1:0) << std::endl;
	res=TestPCB_A.Read(Buffer,Ptr1);
	std :: cout << (res?1:0) << " " << Buffer << std::endl;
	res=TestPCB_A.Write(Source,Ptr1);
	std :: cout << (res?1:0) << std::endl;
	res=TestPCB_A.Read(Buffer,Ptr1);
	std :: cout << (res?1:0) << " " << Buffer << std::endl;
	res=TestPCB_A.deAlloc(Ptr1);
	std :: cout << (res?1:0) << std::endl;

	// 2. 检查Alloc顺序
	AddressPtr PtrList[3][260];
	for(int i=0;i<256;++i)
	{
		PtrList[0][i] = TestPCB_A.Alloc();
	}
	std::strcpy(Source,"RunTest2(PCB A Page ---- Write)");
	std :: cout << (res?1:0) << std::endl;
	std::string NUMSTR;

	for(int i=0;i<128;++i)
	{
		NUMSTR = std::to_string(i);
		for(int j=0;j<NUMSTR.size();++j)
		{
			Source[j+20]=NUMSTR[j];
		}
		res=TestPCB_A.Write(Source,PtrList[0][i]);
		std :: cout << (res?1:0) << std::endl;
	}
	for(int i=128;i<256;++i)
	{
		NUMSTR = std::to_string(i);
		for(int j=0;j<NUMSTR.size();++j)
		{
			Source[j+20]=NUMSTR[j];
		}
		res=TestPCB_A.Write(Source,PtrList[0][i]);
		std :: cout << (res?1:0) << std::endl;
	}
	for(int i=0;i<256;++i)
	{
		res=TestPCB_A.Read(Buffer,PtrList[0][i]);
		std :: cout << (res?1:0) << " " << Buffer << std::endl;
	}


	// 3. 验证多PCB下的内存页面置换
	PCB_MemInterface TestPCB_B;
	for(int i=0;i<256;++i)
	{
		PtrList[1][i] = TestPCB_B.Alloc();
		std :: cout << (res?1:0) << std::endl;
	}

	std::strcpy(Source,"RunTest3(PCB B Page ---- Write)");

	for(int i=0;i<256;++i)
	{
		NUMSTR = std::to_string(i);
		for(int j=0;j<NUMSTR.size();++j)
		{
			Source[j+20]=NUMSTR[j];
		}
		res=TestPCB_B.Write(Source,PtrList[1][i],sizeof(Source));
		std :: cout << (res?1:0) << std::endl;
	}

	for(int i=0;i<256;++i)
	{
		res=TestPCB_B.Read(Buffer,PtrList[1][i]);
		std :: cout << (res?1:0) << " " << Buffer << std::endl;
	}

	// 4. 验证内存页面置换后缓存页面的有效性
	for(int i=0;i<256;++i)
	{
		res=TestPCB_A.Read(Buffer,PtrList[0][i]);
		std :: cout << (res?1:0) << " " << Buffer << std::endl;
	}

	for(int i=0;i<256;++i)
	{
		res=TestPCB_B.Read(Buffer,PtrList[1][i]);
		std :: cout << (res?1:0) << " " << Buffer << std::endl;
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
		res=TestPCB_B.deAlloc(PtrList[1][i]);
		std :: cout << (res?1:0) << std::endl;
	}

	for(int i=0;i<256;++i)
	{
		res=TestPCB_B.Read(Buffer,PtrList[1][i]);
		std :: cout << (res?1:0) << " " << Buffer << std::endl;
	}

	for(int i=0;i<256;++i)
	{
		res=TestPCB_A.deAlloc(PtrList[0][i]);
		std :: cout << (res?1:0) << std::endl;
	}

	for(int i=0;i<256;++i)
	{
		res=TestPCB_A.Read(Buffer,PtrList[0][i]);
		std :: cout << (res?1:0) << " " << Buffer << std::endl;
	}
}

// 输出处理全局变量
bool cmp=0;
EPageAlgoType EAlgoType;
char* AlgoTypeStr;
PCB_MemInterface PCBpool[256];

/*
void Result()
{
}
*/

std::string SubTask(const std::string& instructionstr)
{
	ArgConverter Args(instructionstr);
	const int& Argc=Args.getArgc();
	char** Argv=Args.getArgv();
	if(Argc<3)
	{
		return std::string("Wrong Input");
	}

	int PCB_ID=0,Mem_ID=0;
	PCB_ID=MyAlgo::BasicFunc::read_int<int>(Argv[1]);
	Mem_ID=MyAlgo::BasicFunc::read_int<int>(Argv[2]);

	bool result=false;
	std::string ret;
	ret.clear();
	char buffer[256];
	std::memset(buffer,0,sizeof(buffer));

	switch(Argv[0][0]) // Argv[0] =  "Alloc" "deAlloc" "Read" "Write"
	{
		case 'A':
			result=PCBpool[PCB_ID].Alloc(Mem_ID);
			break;
		case 'd':
			result=PCBpool[PCB_ID].deAlloc(Mem_ID);
			break;
		case 'R':
			result=PCBpool[PCB_ID].Read(buffer,Mem_ID);
			break;
		case 'W':
			std::strcpy(buffer,Argv[3]);
			result=PCBpool[PCB_ID].Write(buffer,Mem_ID);
			break;
	}

	ret.append(result?"1":"0");

	if(Argv[0][0]=='R') // Case Read
	{
		if(result&&buffer[0])
		{
			ret.append(" ");
			ret.append(buffer);
		}
	}

	return ret;
}

void RunTask()
{
	Timer timer;
	timer.reset();
	timer.start();
	std::string InputFilename = "CASE.in";
	std::string OutputFilename = "CASE.out";
	std::string PRCounterFilename(AlgoTypeStr);
	PRCounterFilename.append(".txt");

	GoSchedHost SchedHost;
	FileHandler InputFile(InputFilename,SchedHost.getSched());
	FileHandler OutputFile(OutputFilename,SchedHost.getSched());
	FileHandler PRCounterFile(PRCounterFilename,SchedHost.getSched());

	std::thread t1(&FileHandler::ReadFileSimple,&InputFile);
	std::thread t2(&FileHandler::ReadFileSimple,&OutputFile);
	t1.detach();
	t2.detach();
	const std::vector<std::string>& InputLinesRef=InputFile.GetData();
	int id=0;
	
	/*
	while(true)
	{
		for(;id<InputLinesRef.size();++id)
		{
			//std::cout<<InputLinesRef[id]<<std::endl;
			OutputFile.AddLineSimpleMerge(InputLinesRef[id]);
		}
		if(!InputFile.isReading())
		{
			break;
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
	*/

	while(true)
	{
		for(;id<InputLinesRef.size();++id)
		{
			OutputFile.AddLineSimpleMerge(SubTask(InputLinesRef[id]));
		}
		if(!InputFile.isReading())
		{
			break;
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	OutputFile.WriteToFileOnlyFlush();
	timer.stop();

	// 输出时间花销和触发缺页中断次数
	//Elapsed time:				
	//Page Replacement Counter:	
	//Actual Memmove Counter:	
	PRCounterFile.ReadFileSimple();

	// 本轮耗时
	std::string TimeCostLine("Elapsed time:\t\t\t\t");
	TimeCostLine.append(std::to_string(timer.elapsedMilliseconds()));
	TimeCostLine.append("ms");
	PRCounterFile.AddLineSimpleMerge(TimeCostLine);

	// 本轮触发的缺页中断次数
	std::string PageRepCountLine("Page Replacement Count:\t");
	PageRepCountLine.append(std::to_string(PageReplacementAlgoGlobals::RuntimePageAlgo->GetPRCounter()));
	PRCounterFile.AddLineSimpleMerge(PageRepCountLine);

	// 本轮实际的发生的内存和磁盘缓存交换页面的次数
	std::string MemMoveCountLine("Actual Memmove Count:\t");
	MemMoveCountLine.append(std::to_string(VirtualMemorySystem::DiskOperationCounter));
	PRCounterFile.AddLineSimpleMerge(MemMoveCountLine);

	PRCounterFile.WriteToFileOnlyFlush();
}

INITIALIZE_EASYLOGGINGPP
int main(int argc, char* argv[])
{
	std::cout << "Hello World" << std::endl;
	if(argc!=2)
	{
		fprintf(stderr, "Not Standard input, Run Default FIFO\n");
		fprintf(stderr, "Standard input: Main [FIFO/LRU/CLOCK/IMPROVEDCLOCK]\n");
		AlgoTypeStr = new char[5];
		AlgoTypeStr[0]='F';
		AlgoTypeStr[1]='I';
		AlgoTypeStr[2]='F';
		AlgoTypeStr[3]='O';
		AlgoTypeStr[4]=0;
	}
	else
	{
		AlgoTypeStr=argv[1];
	}
	if(strcmp(AlgoTypeStr,"FIFO")==0)
	{
		cmp=1;
		EAlgoType = EPageAlgoType::eFIFO;
	}
	if(!cmp&&strcmp(AlgoTypeStr,"LRU")==0)
	{
		cmp=1;
		EAlgoType = EPageAlgoType::eLRU;
	}
	if(!cmp&&strcmp(AlgoTypeStr,"CLOCK")==0)
	{
		cmp=1;
		EAlgoType = EPageAlgoType::eClock;
	}
	if(!cmp&&strcmp(AlgoTypeStr,"IMPROVEDCLOCK")==0)
	{
		cmp=1;
		EAlgoType = EPageAlgoType::eImprovedClock;
	}
	if(!cmp)
	{
		fprintf(stderr, "Not Standard input, Run Default FIFO\n");
		fprintf(stderr, "Standard input: Main [FIFO/LRU/CLOCK/IMPROVEDCLOCK]\n");
		EAlgoType = EPageAlgoType::eFIFO;
	}

	// Easy Logging plusplus Settings
#ifndef NDEBUG
	el::Configurations conf("./ConfigFile/easyLogging++/debug.conf");
	el::Loggers::reconfigureAllLoggers(conf);
	el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
	el::Loggers::setVerboseLevel(0);
#endif
#ifdef NDEBUG
	el::Configurations conf("./ConfigFile/easyLogging++/release.conf");
	el::Loggers::reconfigureAllLoggers(conf);
	el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
	el::Loggers::setVerboseLevel(0);
#endif
	// LogTest
#ifdef NDEBUG
	VLOG(0) << "This is a verbose message";
	VLOG(0) << "Verbose Message:	Runtime Function Stack, to locate assert code file and function";
	LOG(DEBUG) << "This is a debug message";
	LOG(INFO) << "This is an info message";
	LOG(WARNING) << "This is a warning message";
	LOG(ERROR) << "This is an error message";
	LOG(INFO) << "Debug Message:	Notify debugger some funcions was excuted";
	LOG(INFO) << "					or middle value which is important";
	LOG(INFO) << "Info Message:		Info showing program's general running status.";
	LOG(INFO) << "This is an info message";
#endif

	// MemorySystem Settings
	VirtualMemorySystem::init();
	SystemTracker::RegistMessageBus();
	//PageReplacementAlgoGlobals::SetPageAlgo(EPageAlgoType::eFIFO);
	//PageReplacementAlgoGlobals::SetPageAlgo(EPageAlgoType::eLRU);
	//PageReplacementAlgoGlobals::SetPageAlgo(EPageAlgoType::eClock);
	//PageReplacementAlgoGlobals::SetPageAlgo(EPageAlgoType::eImprovedClock);
	PageReplacementAlgoGlobals::SetPageAlgo(EAlgoType);

#ifndef NDEBUG
	// RunTest
	RunTest();
	// TestResult
#endif

#ifdef NDEBUG
	// RunTask
	RunTask();
	// TaskResults
#endif

	return 0;
}
