/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : VirtualSystemMemory.cpp
#   Last Modified : 2024-10-20 19:52
#   Describe      : 
#
# ====================================================*/

#include "VirtualSystemMemory.h"
#include <cstdint>

// 内存基础管理部分
void VirtualSystemMemory::init()
{
}

void VirtualSystemMemory::release()
{
}

void VirtualSystemMemory::SetPageAlgo(int32_t type)
{}
// MemController
// 内存控制器代码实现
void PageReplacementAlgo( std :: function<void(char*)> PRAfunc , char* MemPtr)
{
}

void FIFO(char* MemPtr)
{}

char* VirtualSystemMemory::MemoryController::Allocate()
{}

int32_t VirtualSystemMemory::MemoryController::DeAllocate(char* MemPtr)
{}

bool VirtualSystemMemory::MemoryController::TryVisit(char* MemPtr)
{}

int32_t VirtualSystemMemory::MemoryController::Visit(char* MemPtr)
{}
