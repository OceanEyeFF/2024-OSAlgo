/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : config.h
#   Last Modified : 2024-12-01 00:18
#   Describe      : 
#
# ====================================================*/

#ifndef  _CONFIG_H
#define  _CONFIG_H

#define CASE_COUNT			20

#define OPRGENSTYLE			1

#define OPR_COUNT			10000000
//Type0 多PCB但是单个PCB的内存占用量少
//Case 4-7
//Case 9
#define THREAD_COUNT		51
#define MEMLIMIT			16
#define FREQUENTUSE			4		// 25%的高频访问数据
#define FREQUENTAGE			96		// 75%的高频读写
//Type1 中等PCB数量但是PCB的内存占用量中等
//Case 4-7
//Case 9
//#define THREAD_COUNT		15
//#define MEMLIMIT			64
//#define FREQUENTUSE			13		// 20%的高频访问数据
//#define FREQUENTAGE			103		// 80%的高频读写
//Type2 少PCB但是单个PCB的内存占用量多
//Case 0-3
//Case 8
//#define THREAD_COUNT		4
//#define MEMLIMIT			256
//#define FREQUENTUSE		51		// 20%高频访问数据
//#define FREQUENTAGE			103		// 80%的高频读写


// OPRGENSTYLE:
// 设置为1的时候会尝试把所有的操作都设置为合法操作，并且尽可能的减少deAlloc操作，保证所有合法操作中有一半以上是读写操作
// Todo
// OPRCOUNT:一个测试样例中的输入操作数
// THREAD*MEMLIMIT在稳定的前提下最大为5*256=1280
// THREADCOUNT:一个测试样例中模拟的线程PCB数量 求稳最大为5
// MEMLIMIT:测试样例中PCB的内存使用范围从0-MEMLIMIT
// FREQUENTUSE:测试样例中生成的数据会有更多的内存操作集中在0-FREQUENTUSE
// FREQUENTAGE:FREQUENT操作占总操作的百分比，数值除以128
// not use:
// OPRGENSTYLE:操作生成模式

#endif // _CONFIG_H
	   //
	   //
