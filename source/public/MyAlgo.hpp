/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : MyAlgo.hpp
#   Last Modified : 2024-11-04 20:57
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
			std :: bitset<MAX_SIZE> Mask16;
			std :: bitset<MAX_SIZE> tmp;
			Mask16.reset();
			// 尝试触发强制并发优化
			{
				Mask16.set(0);
				Mask16.set(1);
				Mask16.set(2);
				Mask16.set(3);
				Mask16.set(4);
				Mask16.set(5);
				Mask16.set(6);
				Mask16.set(7);
				Mask16.set(8);
				Mask16.set(9);
				Mask16.set(10);
				Mask16.set(11);
				Mask16.set(12);
				Mask16.set(13);
				Mask16.set(14);
				Mask16.set(15);
			}
			size_t size = b.size();

			// 逐16位查找，理论性能64位最佳（字长64）
			for (size_t i = 0; i < size / 16; ++i, Mask16 <<= 16)
			{
				// 获取当前16位的值
				tmp = Mask16 & b;
				// 检查当前块是否为全 1
				// 如果不等于0xFFFF说明该块中有0
				if (tmp.count() != 16)
				{
					// 找到为 0 的位
					for (int j = i*16; j < (i+1)*16; ++j)
					{
						if (!tmp[j]) {
							return j;
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
			std :: bitset<MAX_SIZE> Mask16;
			std :: bitset<MAX_SIZE> tmp;
			Mask16.reset();
			// 尝试触发强制并发优化
			{
				Mask16.set(0);
				Mask16.set(1);
				Mask16.set(2);
				Mask16.set(3);
				Mask16.set(4);
				Mask16.set(5);
				Mask16.set(6);
				Mask16.set(7);
				Mask16.set(8);
				Mask16.set(9);
				Mask16.set(10);
				Mask16.set(11);
				Mask16.set(12);
				Mask16.set(13);
				Mask16.set(14);
				Mask16.set(15);
			}

			size_t size = b.size();

			// 逐16位查找
			for (size_t i = 0; i < size / 16; ++i, Mask16 <<= 16)
			{
				// 获取当前16位的值
				tmp = Mask16 & b;

				// 检查当前块是否为全 0
				// 如果不等于0 说明当前块中有一个位上有1
				if (tmp.count() != 0)
				{
					// 找到为 1 的位
					for (int j = i*16; j < (i+1)*16; ++j)
					{
						if (tmp[j]) {
							return j;
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
