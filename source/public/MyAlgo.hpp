/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : MyAlgo.hpp
#   Last Modified : 2024-10-30 19:39
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _MYALGO_H
#define  _MYALGO_H
#include <iostream>
#include <bitset>
#include <cstdint>

namespace MyAlgo
{
	namespace BasicFunc
	{
		template <class T> void SwapTwoIntegers(T &a, T &b) // Only Capable for INTEGER
		{
			a^=b;
			b^=a;
			a^=b;
		}
	}

	namespace ForBitset
	{
		template <size_t MAX_SIZE>
			size_t FindFirstZero(const std::bitset<MAX_SIZE>& b)// 
		{
			size_t size = b.size();

			// 逐16位查找
			for (size_t i = 0; i < size / 16; ++i)
			{
				// 获取当前16位的值
				std::bitset<16> block = (b >> (i * 16)).to_ullong() & 0xFFFF;

				// 检查当前块是否为全 1
				if (block.to_ulong() != 0xFFFF)
				{
					// 找到非全 1 的16位块
					for (int j = 0; j < 16; ++j)
					{
						if (!block[j]) {
							return i * 16 + j;
						}
					}
				}
			}
			
			// 检查剩余的位
			for (size_t i = (size / 16) * 16; i < size; ++i)
			{
				if (!b[i])
				{
					return i;
				}
			}

			return size; // 如果没有找到，返回 size
		}
		template <size_t MAX_SIZE>
			size_t FindFirstOne(const std::bitset<MAX_SIZE>& b)
		{
			size_t size = b.size();

			// 逐16位查找
			for (size_t i = 0; i < size / 16; ++i)
			{
				// 获取当前16位的值
				std::bitset<16> block = (b >> (i * 16)).to_ullong() & 0xFFFF;

				// 检查当前块是否为全 1
				if (block.to_ulong() != 0)
				{
					// 找到非全 1 的16位块
					for (int j = 0; j < 16; ++j)
					{
						if (!block[j]) {
							return i * 16 + j;
						}
					}
				}
			}
			
			// 检查剩余的位
			for (size_t i = (size / 16) * 16; i < size; ++i)
			{
				if (b[i])
				{
					return i;
				}
			}

			return size; // 如果没有找到，返回 size
		}
	}
}

#endif // _MYALGO_H
	   //
	   //
