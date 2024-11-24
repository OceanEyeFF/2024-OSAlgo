/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : MyAlgo.hpp
#   Last Modified : 2024-11-23 23:29
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _MYALGO_H
#define  _MYALGO_H
#include <iostream>
#include <bitset>
#include <cstdint>
#include <type_traits>

namespace MyAlgo
{
	namespace BasicFunc
	{
		template <class T>
			void SwapTwoIntegers(T &a, T &b) // Only Capable for INTEGER
		{
			a^=b;
			b^=a;
			a^=b;
		}

		template <class T>
			int CountOnes(T n)
		{
			static_assert(std::is_integral<T>::value, "Template argument must be an integral type.");
			std::bitset<sizeof(T) * 8> bits(n); // 根据类型大小创建 bitset
			return bits.count();
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

	template <typename T>
	class DoublyLinkedList
	{
	public:
		struct Node
		{
			T data;
			Node* prev;
			Node* next;

			Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
		};

	private:
		Node* head;
		Node* tail;
		size_t size;

	public:
		DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

		~DoublyLinkedList()
		{
			clear();
		}

		// 添加到链表末尾
		void push_back(const T& value)
		{
			Node* newNode = new Node(value);
			if (tail) {
				tail->next = newNode;
				newNode->prev = tail;
				tail = newNode;
			} else {
				head = tail = newNode;
			}
			size++;
		}

		// 添加到链表开头
		void push_front(const T& value)
		{
			Node* newNode = new Node(value);
			if (head) {
				head->prev = newNode;
				newNode->next = head;
				head = newNode;
			} else {
				head = tail = newNode;
			}
			size++;
		}

		// 在指定位置插入节点
		void insert(size_t index, const T& value)
		{
			if (index > size) {
				throw std::out_of_range("Index out of range");
			}
			if (index == 0) {
				push_front(value);
			} else if (index == size) {
				push_back(value);
			} else {
				Node* newNode = new Node(value);
				Node* current = head;
				for (size_t i = 0; i < index; ++i) {
					current = current->next;
				}
				newNode->prev = current->prev;
				newNode->next = current;
				if (current->prev) {
					current->prev->next = newNode;
				}
				current->prev = newNode;
				if (current == head) {
					head = newNode; // 如果插入在头部
				}
				size++;
			}
		}

		// 删除指定位置的节点
		void remove(size_t index)
		{
			if (index >= size) {
				throw std::out_of_range("Index out of range");
			}
			if (index == 0) {
				pop_front();
			} else if (index == size - 1) {
				pop_back();
			} else {
				Node* current = head;
				for (size_t i = 0; i < index; ++i) {
					current = current->next;
				}
				if (current->prev) {
					current->prev->next = current->next;
				}
				if (current->next) {
					current->next->prev = current->prev;
				}
				delete current;
				size--;
			}
		}

		// 在指定节点前插入
		void insert(Node* ptr, const T& value)
		{
			if (!ptr) {
				throw std::invalid_argument("Invalid pointer: ptr is null");
			}

			Node* newNode = new Node(value);
			
			// 插入到头部
			if (ptr == head) {
				newNode->next = head;
				head->prev = newNode;
				head = newNode;
			} else {
				newNode->prev = ptr->prev;
				newNode->next = ptr;
				if (ptr->prev) {
					ptr->prev->next = newNode;
				}
				ptr->prev = newNode;
			}
			size++;
		}

		// 删除指定节点
		void remove(Node* ptr)
		{
			if (!ptr) {
				throw std::invalid_argument("Invalid pointer: ptr is null");
			}
			
			if (ptr == head) {
				pop_front();
			} else if (ptr == tail) {
				pop_back();
			} else {
				if (ptr->prev) {
					ptr->prev->next = ptr->next;
				}
				if (ptr->next) {
					ptr->next->prev = ptr->prev;
				}
				delete ptr;
				size--;
			}
		}

		// 删除最后一个节点
		void pop_back()
		{
			if (tail) {
				Node* temp = tail;
				tail = tail->prev;
				if (tail) {
					tail->next = nullptr;
				} else {
					head = nullptr; // 链表变空
				}
				delete temp;
				size--;
			} else {
				throw std::underflow_error("List is empty");
			}
		}

		// 删除第一个节点
		void pop_front()
		{
			if (head) {
				Node* temp = head;
				head = head->next;
				if (head) {
					head->prev = nullptr;
				} else {
					tail = nullptr; // 链表变空
				}
				delete temp;
				size--;
			} else {
				throw std::underflow_error("List is empty");
			}
		}

		// 清空链表
		void clear()
		{
			while (head) {
				pop_front();
			}
		}

		// 获取链表大小
		size_t getSize() const
		{
			return size;
		}

		// 遍历链表
		void print() const
		{
			Node* current = head;
			while (current) {
				std::cout << current->data << " ";
				current = current->next;
			}
			std::cout << std::endl;
		}

		// 反向遍历链表
		void printReverse() const
		{
			Node* current = tail;
			while (current) {
				std::cout << current->data << " ";
				current = current->prev;
			}
			std::cout << std::endl;
		}

		// 获取头指针
		Node* getHead() const
		{
			return head;
		}
		// 获取尾指针
		Node* getTail() const
		{
			return tail;
		}
	};

}

#endif // _MYALGO_H
	   //
	   //
