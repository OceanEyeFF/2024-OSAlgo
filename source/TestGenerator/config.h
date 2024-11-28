/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : config.h
#   Last Modified : 2024-11-28 20:23
#   Describe      : 
#
# ====================================================*/

#ifndef  _CONFIG_H
#define  _CONFIG_H

#define CASE_COUNT			2

#define OPRGENSTYLE			0
#define OPR_COUNT			100000000
#define THREAD_COUNT		256
#define MEMLIMIT			256
#define FREQUENTUSE			64
#define FREQUENTAGE			64

// OPRCOUNT:一个测试样例中的输入操作数
// THREADCOUNT:一个测试样例中模拟的线程PCB数量
// MEMLIMIT:测试样例中PCB的内存使用范围从0-MEMLIMIT
// FREQUENTUSE:测试样例中生成的数据会有更多的内存操作集中在0-FREQUENTUSE
// FREQUENTAGE:FREQUENT操作占总操作的百分比，数值除以128
// not use:
// OPRGENSTYLE:操作生成模式

#endif // _CONFIG_H
	   //
	   //
