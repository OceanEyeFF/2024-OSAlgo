/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : test.cpp
#   Last Modified : 2024-11-30 21:19
#   Describe      : 
#
# ====================================================*/


#include "../public/MyAlgo.hpp"
#include "libgo/coroutine.h"
#include <chrono>
#include <thread>

int main()
{
	GoSchedHost FileCororoutineHost(1);

	//=======================================================================
	//Cororoutine Combine Write
	//=======================================================================
	FileHandler WriteFile("1.txt",FileCororoutineHost.getSched());
	auto StartTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 500000; ++i)
	{
		WriteFile.AddLine("new Line:\t" + std::to_string(i));
	}
	std::cout << "Writing End" << std::endl;
	while(FileCororoutineHost.isRunning())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	WriteFile.WriteToFileOnlyFlush();
	std::cout << "Really Writing End" << std::endl;
	auto EndTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> Dur = EndTime-StartTime;
	std::cout << "Cororoutine Combine, Write at last. Time:\t" << Dur.count() << "seconds\n";

	//=======================================================================
	//Simple Write
	//=======================================================================
	FileHandler WriteFile2("2.txt",FileCororoutineHost.getSched());
	StartTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 500000; ++i)
	{
		WriteFile2.AddLineSimple("new Line:\t" + std::to_string(i));
	}
	WriteFile2.WriteToFile();
	EndTime = std::chrono::high_resolution_clock::now();
	Dur = EndTime-StartTime;
	std::cout << "Simple Write Time:\t" << Dur.count() << "seconds\n";

	
	//=======================================================================
	//Simple Write Combine at Last then Flush
	//=======================================================================
	FileHandler WriteFile3("3.txt",FileCororoutineHost.getSched());
	StartTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 500000; ++i)
	{
		WriteFile3.AddLineSimple("new Line:\t" + std::to_string(i));
	}
	WriteFile3.WriteToFileMergeAndFlush();
	EndTime = std::chrono::high_resolution_clock::now();
	Dur = EndTime-StartTime;
	std::cout << "Simple Write Combine at last then Flush. Time:\t" << Dur.count() << "seconds\n";

	//=======================================================================
	//Simple Write Combine when push
	//=======================================================================
	FileHandler WriteFile4("4.txt",FileCororoutineHost.getSched());
	StartTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 500000; ++i)
	{
		WriteFile4.AddLineSimpleMerge("new Line:\t" + std::to_string(i));
	}
	WriteFile4.WriteToFileOnlyFlush();
	EndTime = std::chrono::high_resolution_clock::now();
	Dur = EndTime-StartTime;
	std::cout << "Simple Write Combine when Push, Flush at last. Time:\t" << Dur.count() << "seconds\n";

	//=======================================================================
	// MultiThread Read
	//=======================================================================
	FileHandler ReadFile("3.txt", FileCororoutineHost.getSched());
	StartTime = std::chrono::high_resolution_clock::now();
	ReadFile.ReadFile();
	std::cout << ReadFile.GetData().size() << std::endl;
	std::cout << "Reading End" << std::endl;
	EndTime = std::chrono::high_resolution_clock::now();
	Dur = EndTime-StartTime;
	std::cout << "MultiThread Read Time:\t" << Dur.count() << "seconds\n";

	//=======================================================================
	// SingleThread Read
	//=======================================================================
	FileHandler ReadFile2("4.txt", FileCororoutineHost.getSched());
	StartTime = std::chrono::high_resolution_clock::now();
	ReadFile2.ReadFileSimple();
	std::cout << ReadFile2.GetData().size() << std::endl;
	std::cout << "Reading End" << std::endl;
	EndTime = std::chrono::high_resolution_clock::now();
	Dur = EndTime-StartTime;
	std::cout << "SingleThread Read Time:\t" << Dur.count() << "seconds\n";

	return 0;
}
