/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : main.cpp
#   Last Modified : 2024-12-01 00:20
#   Describe      : 
#
# ====================================================*/

#include <chrono>
#include <cstdint>
#include <iostream>
#include <filesystem>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <random>
#include "config.h"
#include "../public/MyAlgo.hpp"
#include "libgo/coroutine.h"

GoSchedHost WriteHost(1);
std::mutex MU;
std :: vector<FileHandler> Operations;
std :: vector<FileHandler> Answers;


const int &TestCases=CASE_COUNT;
const int &myThreadCount=THREAD_COUNT;
const int &myThreadMemoryLimit=MEMLIMIT;
const int &oprCount=OPR_COUNT;

std::string inpath = "./in";
std::string anspath = "./ans";

static void Generator(std :: string export_file_number)
{
	Timer timer;
	timer.start();
	// 设置当前样例路径和答案路径
	std::unique_lock<std::mutex> lock(MU);
	Operations.emplace_back(inpath+"/"+export_file_number + ".in", WriteHost.getSched());
	Answers.emplace_back(anspath+"/"+export_file_number + ".ans", WriteHost.getSched());
	int id=Operations.size()-1;
	std::cout << export_file_number << std::endl;
	std::cout << Operations.size() << std::endl;
	std::cout << Answers.size() << std::endl;
	Operations[id].ReadFile();
	Answers[id].ReadFile();
	lock.unlock();
#define Operation  Operations[id]
#define Answer Answers[id]
	// 初始化数值记录数组
	int rec[256][256];
	std:: memset(rec,-1,sizeof(rec));

    // 创建随机数生成器
    std::random_device rd;  // 获取随机数种子
    std::mt19937 gen(rd());  // 初始化 Mersenne Twister 生成器
    std::uniform_int_distribution<int32_t> dis(1, 10000000);		// 设定范围减少以减少空间
																// -1设定为未开辟
																// 0设定为开辟了未赋值
																// 正数为赋值

	// 配置随机数变量
	int32_t random_number;			// 内存写入内容（如果为写入操作
	int32_t ThreadID,Position;		// 线程ID，写入块
	int32_t OperationType;			// 操作类型（alloc, dealloc, read, write)
	int32_t IsFrequent;				// 判定是否为Frequent，如果是则块取模为另一个数
	std::string OperationString;	// 生成的指令字符串，用于写入文件
	std::string AnsString;			// 生成的指令字符串，用于写入文件

	for(int i=0;i<oprCount;++i)
	{
		ThreadID = dis(gen);
		ThreadID%=myThreadCount;
		Position = dis(gen);

		// 根据是否落在常用块区间来决定Position的范围
		IsFrequent = dis(gen);
		IsFrequent &= 255;
		Position%=(IsFrequent<FREQUENTAGE)?FREQUENTUSE:myThreadMemoryLimit;

		random_number = dis(gen);

		OperationType= dis(gen);
		OperationType&=3;

		random_number = dis(gen);
		OperationString.clear();
		// 操作序列须保证50%为合法操作
		// 所以在真实生成前对本轮生成的操作进行检测
		// 如果为非法操作根据random_number的奇偶性来决定是否修改为指定位上的必定合法操作
		// deAlloc Read Write-> Alloc
		// Alloc -> Write DeAlloc Read三选一
		if(random_number&1||OPRGENSTYLE) // 开始检测
		{
			switch(OperationType)
			{
				case 0:		// Alloc
					if(~rec[ThreadID][Position])
					{
						OperationType = OPRGENSTYLE?(dis(gen)%2+2):(dis(gen)%3+1);
					}
					else
					{
					}
					break;
				case 1:		// deAlloc
					if(~rec[ThreadID][Position])
					{
						if(OPRGENSTYLE)
						{
							OperationType=(dis(gen)%3+1);
						}
					}
					else
					{
						OperationType = 0;
					}
					break;
				case 2:		// Read
					if(~rec[ThreadID][Position])
					{
					}
					else
					{
						OperationType = 0;
					}
					break;
				case 3:		// Write
					if(~rec[ThreadID][Position])
					{
					}
					else
					{
						OperationType = 0;
					}
					break;
			}
		}
		// 生成操作序列
		switch(OperationType)
		{
			case 0:		// Alloc
				//OperationString=std::string("Alloc");
				OperationString = std::string("A");
				OperationString = OperationString + " " + std::to_string(ThreadID)
												  + " " + std::to_string(Position);
				Operation.AddLineSimpleMerge(OperationString);
				break;
			case 1:		// deAlloc
				//OperationString=std::string("deAlloc");
				OperationString = std::string("d");
				OperationString = OperationString + " " + std::to_string(ThreadID)
												  + " " + std::to_string(Position);
				Operation.AddLineSimpleMerge(OperationString);
				break;
			case 2:		// Read
				//OperationString=std::string("Read");
				OperationString = std::string("R");
				OperationString = OperationString + " " + std::to_string(ThreadID)
												  + " " + std::to_string(Position);
				Operation.AddLineSimpleMerge(OperationString);
				break;
			case 3:		// Write
				//OperationString=std::string("Write");
				OperationString = std::string("W");
				OperationString = OperationString + " " + std::to_string(ThreadID)
												  + " " + std::to_string(Position);
				OperationString +=					" " + std::to_string(random_number);
				Operation.AddLineSimpleMerge(OperationString);
				break;
		}

		// 生成答案序列
		// 答案序列规则：
		// 1. 操作是否合法，合法输出1 非法输出0
		// 2. 操作合法如果为读，输出读取到的内容
		switch(OperationType)
		{
			case 0:		// Alloc
				if(~rec[ThreadID][Position])
				{
					Answer.AddLineSimpleMerge(std::string("0"));
				}
				else
				{
					rec[ThreadID][Position]=0;
					Answer.AddLineSimpleMerge(std::string("1"));
				}
				break;
			case 1:		// deAlloc
				if(~rec[ThreadID][Position])
				{
					rec[ThreadID][Position]=-1;
					Answer.AddLineSimpleMerge(std::string("1"));
				}
				else
				{
					Answer.AddLineSimpleMerge(std::string("0"));
				}
				break;
			case 2:		// Read
				AnsString.clear();
				if(~rec[ThreadID][Position])
				{
					AnsString=std::string("1");
					if(rec[ThreadID][Position])	//如果之前写入过文件，则把读取到的值附在后面
					{
						AnsString+= " "+std::to_string(rec[ThreadID][Position]);
					}
				}
				else
				{
					AnsString=std::string("0");
				}
				Answer.AddLineSimpleMerge(AnsString);
				break;
			case 3:		// Write
				AnsString.clear();
				if(~rec[ThreadID][Position])
				{
					AnsString=std::string("1");
					rec[ThreadID][Position] =random_number;
				}
				else
				{
					AnsString=std::string("0");
				}
				Answer.AddLineSimpleMerge(AnsString);

				break;
		}
	}
	Operation.WriteToFileOnlyFlush();
	Answer.WriteToFileOnlyFlush();
#undef Operation
#undef Answer
	timer.stop();
	std::cout << "Elapsed time: " << timer.elapsedMilliseconds() << " ms" << std::endl;
}

int main()
{

	// 判断路径是否存在
	if (!std::filesystem::exists(inpath)) {
		// 创建文件夹
		if (std::filesystem::create_directory(inpath)) {
			std::cout << "文件夹创建成功: " << inpath << std::endl;
		}
		else {
			std::cerr << "创建文件夹失败: " << inpath << std::endl;
		}
	}
	else {
		std::cout << "文件夹已存在: " << inpath << std::endl;
	}

	// 判断路径是否存在
	if (!std::filesystem::exists(anspath)) {
		// 创建文件夹
		if (std::filesystem::create_directory(anspath)) {
			std::cout << "文件夹创建成功: " << anspath << std::endl;
		}
		else {
			std::cerr << "创建文件夹失败: " << anspath << std::endl;
		}
	}
	else {
		std::cout << "文件夹已存在: " << anspath << std::endl;
	}

	Operations.reserve(CASE_COUNT+10);
	Answers.reserve(CASE_COUNT+10);
	std::string export_file_number;
	std::vector<std::thread> threads;
	for(int i=0;i<CASE_COUNT;++i)
	{
		export_file_number = std::string("CASE")+std::to_string(0+i);
		threads.emplace_back(Generator,export_file_number);
	}

//	co_sleep((OPR_COUNT)*(CASE_COUNT)>>10);
//	std::this_thread::sleep_for(std::chrono::milliseconds(OPR_COUNT*CASE_COUNT));
	for(auto& t: threads)
	{
		t.join();
	}
//	std::this_thread::sleep_for(std::chrono::milliseconds(OPR_COUNT*CASE_COUNT>>15));
	while(WriteHost.isRunning())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	WriteHost.endHost();
	return 0;
}
