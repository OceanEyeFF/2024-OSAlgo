/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : MyAlgo.hpp
#   Last Modified : 2024-11-30 00:40
#   Describe      : 
#
# ====================================================*/

#pragma once

#ifndef  _MYALGO_H
#define  _MYALGO_H
#include <cstddef>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <bitset>
#include <cstdint>
#include <vector>
#include <thread>
#include <mutex>
#include <fstream>
#include <string>
#include <cstring>
#include <atomic>
#include "libgo/libgo.h"
#include "libgo/coroutine.h"
#include "libgo/scheduler/scheduler.h"
#include "libgo/sync/co_mutex.h"
#include "libgo/common/util.h"

namespace MyAlgo
{
	namespace BasicFunc
	{
		template <class T>
			void SwapTwoIntegers(T &a, T &b) // Only Capable for INTEGER
		{
			static_assert(std::is_integral<T>::value, "Template argument must be an integral type.");
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

		template <class T>
		T read_int(char* c)
		{
			static_assert(std::is_integral<T>::value, "Template argument must be an integral type.");
			T ret=0;
			short int flag=1;
			for(;*c==' '||*c=='\n';++c);
			if(*c=='-')
			{
				flag=-1;
				++c;
			}
			for(;'0'<=*c&&*c<='9';++c)
			{
				ret=(ret<<3)+(ret<<1)+(*c-'0');
			}
			return ret;
		}

		// Should guarantee c has enough size
		// not safe might access violation
		template <class T>
		void write_int(char* c,T x)
		{
			static_assert(std::is_integral<T>::value, "Template argument must be an integral type.");
			std::strcpy(c,std::to_string(x).c_str());
			/*
			std::string s=std::to_string(x);
			for(int i=0;i<s.length();++i,++c)
			{
				*c=s[i];
			}
			*/
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

class FileHandler
{
private:
	std::vector<std::string> data;		// 存储读取的数据
	std::mutex dataMutex;				// 互斥量保护共享数据
	co::co_mutex codataMutex;			// 互斥量保护共享数据（给协程使用
	std::string fileName;				// 文件名
	co::Scheduler* remoteSchedHost;		// 远端协程管理器
	int totalLines;						// 文件总行数
	std::condition_variable read_cv;	// 多线程读取同步量
	std::ofstream coro_outfile;			// 实时追加输出
	std::string combine_outstring;		// 合并输出
	std::atomic<bool> isReadingComplete;// 原子锁，用于检测读取是否读完文件，帮助实现无锁读取
										//

    // 读取文件的线程函数
	// 读取范围是在数轴上的左闭右开区间
	void ReadLines(size_t startLine, size_t endLine)
	{
		std::vector<std::string> tempData;
		std::ifstream file(fileName);
		std::string line;
		int currentLine=0;

		// 逐行读取文件
		while (std::getline(file, line))
		{
			if (currentLine >= startLine && currentLine < endLine)
			{
				tempData.push_back(line);
			}
			if (currentLine >= endLine) break; // 达到结束行，停止读取
			++currentLine;
		}
		file.close();

		// 数据已准备好，给data上锁写入data
		{
			std::unique_lock<std::mutex> rdlock(dataMutex);
			read_cv.wait(rdlock, [this,startLine](){ return this->data.size()==startLine; } );
			data.insert(data.end(),tempData.begin(),tempData.end());
			read_cv.notify_all();
		}
	}

	// 快速计算文件行数
	void FastGetLine()
	{
		FILE *pFile;
		pFile=fopen(fileName.c_str(),"r");
		if(pFile==NULL)
		{
			totalLines = 0;
			return;
		}
		else
		{
			int n=0;
			int cnt=0;
			for(char c=std::fgetc(pFile);c!=EOF;c=std::fgetc(pFile))
			{
				n+=(c=='\n')?1:0;
				cnt=(c=='\n')?0:cnt+1;
			}
			totalLines = n+(cnt?1:0);
			return;
		}
		fclose(pFile);
	}

public:
	//构造函数和析构函数
	FileHandler(std::string filename, co::Scheduler* SchedHost)
	{
		fileName=filename;		// 设置文件名
								// 常规初始化
		remoteSchedHost=SchedHost;// 远端协程管理器
		totalLines=0;			// 设置总行数为0
		coro_outfile=std::ofstream(fileName,std::ios::app);
								//初始化协程输出流
		combine_outstring.clear();
	}

	FileHandler(const FileHandler& another)
	{
		fileName=another.fileName;	// 设置文件名
									// 常规初始化
		remoteSchedHost=another.remoteSchedHost;// 远端协程管理器
		totalLines=0;			// 设置总行数为0
		coro_outfile=std::ofstream(fileName,std::ios::app);
								//初始化协程输出流
		combine_outstring.clear();
	}

	~FileHandler()
	{
	}
    // 多线程读取文件的函数
    void ReadFile()
    {
		//未完成读写标记
		isReadingComplete.store(false);
		//文件输入流
        std::ifstream file(fileName);
		// 如果文件不存在则创建文件
		// 并且不用进行下面的所有行为
		if(!file)
		{
			std::ofstream newFile(fileName);
			if (newFile) {
				std::cout << "file not exist, now created " << fileName << std::endl;
			} else {
				std::cerr << "file not exist, unable to create: " << fileName << std::endl;
			}
		}
        // 计算文件行数
		FastGetLine();
		if(!totalLines)
		{
			return;
		}
		data.reserve(totalLines);
		// 打开文件
        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return;
        }

        size_t NUM_THREADS = 12; // 线程数
		size_t LINES_PER_THREAD = totalLines/NUM_THREADS; // 块内行数
        std::vector<std::thread> threads;

        for (size_t i = 0,begin_id=0; i < NUM_THREADS; ++i,begin_id+=LINES_PER_THREAD)
        {
			threads.emplace_back(&FileHandler::ReadLines,this,begin_id,begin_id+LINES_PER_THREAD);
        }
		if(LINES_PER_THREAD*NUM_THREADS!=totalLines)
		{
			threads.emplace_back(&FileHandler::ReadLines,this,LINES_PER_THREAD*NUM_THREADS,totalLines);
		}

        // 等待所有线程完成
        for (auto& t : threads)
        {
            t.join();
        }
		//完成读写标记
		isReadingComplete.store(true);
    }

    // 读取文件的函数
    void ReadFileSimple()
    {
		//未完成读写标记
		isReadingComplete.store(false);
		std::ifstream file(fileName);
		// 如果文件不存在则创建文件
		// 并且不用进行下面的所有行为
		if(!file)
		{
			std::ofstream newFile(fileName);
			if (newFile) {
				std::cout << "file not exist, now created " << fileName << std::endl;
			} else {
				std::cerr << "file not exist, unable to create: " << fileName << std::endl;
			}
		}
        // 计算文件行数
		FastGetLine();
		if(!totalLines)
		{
			return;
		}
		data.reserve(totalLines);
		// 打开文件
        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return;
        }

		std::string line;
		while (std::getline(file, line))
		{
			data.push_back(line); // 将读取到的行存入 vector
			if(!combine_outstring.empty()) combine_outstring.append("\n"); // 给上一行打回车
			combine_outstring.append(line);					  //
		}
		//完成读写标记
		isReadingComplete.store(true);
    }

	// 当前是否正在读写
	bool isReading()
	{
		return !isReadingComplete.load();
	}
    // 清零并从头写入文件的函数
    void WriteToFile()
	{
		std::lock_guard<co::co_mutex> lock(codataMutex);
		std::ofstream file(fileName);
		if (!file.is_open())
		{
			std::cerr << "Error opening file for writing: " << fileName << std::endl;
			return;
		}
		for (const auto& line : this->data)
		{
			file << line << std::endl; // 写入每一行
		}
		file.close(); // 关闭文件
	}

    // 清零并从头写入文件的函数
	// 已经合并，只需要输出
    void WriteToFileOnlyFlush()
	{
		std::lock_guard<co::co_mutex> lock(codataMutex);
		std::ofstream file(fileName);
		if (!file.is_open())
		{
			std::cerr << "Error opening file for writing: " << fileName << std::endl;
			return;
		}
		file << combine_outstring << std::endl;
		file.close(); // 关闭文件
	}

    // 清零并从头写入文件的函数
	// 在最后才合并并输出
    void WriteToFileMergeAndFlush()
	{
		std::lock_guard<co::co_mutex> lock(codataMutex);
		std::ofstream file(fileName);
		if (!file.is_open())
		{
			std::cerr << "Error opening file for writing: " << fileName << std::endl;
			return;
		}
		for(size_t i=0;i<data.size();++i)
		{
			combine_outstring.append(data[i]+((i!=data.size()-1)?"\n":"")); //合并每一行
		}
		file << combine_outstring << std::endl;
		file.close(); // 关闭文件
	}
    // 获取读取的数据
    const std::vector<std::string>& GetData() const
    {
        return data;
    }

    // 重载 [] 操作符（读）
    const std::string& operator[](size_t index) const
    {
        assert(index < data.size() && "Index out of bounds!"); // 越界断言
        return data[index];
    }

    // 重载 [] 操作符（写）
    std::string& operator[](size_t index)
    {
        assert(index < data.size() && "Index out of bounds!"); // 越界断言
        return data[index];
    }

    // 添加新行的函数，协程合并
	// 协程因为反复创建删除实际效率很差
	// 协程写入比合并慢
	// 多线程实现方向应该是无锁循环队列存储消息+notify或者condition_variables
	// deprecated
	// 仅保留用于给测试提供函数入口
    void AddLine(const std::string& newLine)
    {
		std::unique_lock<co::co_mutex> lock(codataMutex); // 加锁
		data.push_back(newLine); // 添加新行
		go co_scheduler(this->remoteSchedHost)[this,newLine]
		{
			if(!this->combine_outstring.empty()) this->combine_outstring.append("\n"); // 给上一行打回车
			this->combine_outstring.append(newLine);
			co_sleep(10);
		};
		lock.unlock();
    }

    // 添加新行的函数，无写入
    void AddLineSimple(const std::string& newLine)
    {
        std::unique_lock<co::co_mutex> lock(codataMutex); // 加锁
        data.push_back(newLine); // 添加新行
		lock.unlock();
    }

    // 添加新行的函数，无写入，但会合并到即将输出的string
    void AddLineSimpleMerge(const std::string& newLine)
    {
        std::unique_lock<co::co_mutex> lock(codataMutex); // 加锁
        data.push_back(newLine); // 添加新行
		if(!combine_outstring.empty()) combine_outstring.append("\n"); // 给上一行打回车
		combine_outstring.append(newLine);
		lock.unlock();
    }
};

class GoSchedHost
{
public:
    GoSchedHost()
    {
		LocalSched = co::Scheduler::Create();
		T = std::thread([this]{ this->LocalSched->Start(1); });
		T.detach();
    }

    GoSchedHost(int num_thread)
    {
		if(!num_thread)
		{
			num_thread=1;
		}
		LocalSched = co::Scheduler::Create();
		T = std::thread([this,num_thread]{ this->LocalSched->Start(num_thread); });
		T.detach();
    }

    ~GoSchedHost()
    {
    }

	co::Scheduler* getSched()
	{
		return LocalSched;
	}

	void endHost()
	{
		go co_scheduler(LocalSched)[this]
		{
			this->LocalSched->Stop();
		};
//		T.join();
	}

	bool isRunning()
	{
		return LocalSched->IsCoroutine();
	}
private:
	co::Scheduler* LocalSched;
	std::thread T;
};

class Timer 
{
public:

    Timer() : running(false) {}

    void start() 
    {
        start_time = std::chrono::high_resolution_clock::now();
        running = true;
    }

    void stop() 
    {
        if (running) 
        {
            end_time = std::chrono::high_resolution_clock::now();
            running = false;
        }
    }

    double elapsedMilliseconds() 
    {
        if (running) 
        {
            end_time = std::chrono::high_resolution_clock::now();
        }
        return std::chrono::duration<double, std::milli>(end_time - start_time).count();
    }

    void reset() 
    {
        running = false;
    }

private:

    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
    bool running;
};

class ArgConverter 
{
private:
    int argc;
    char** argv;

    void stringToArgcArgv(const std::string& input) 
    {
        std::istringstream iss(input);
        std::vector<std::string> args;
        std::string arg;

        // 分割字符串为参数
        while (iss >> arg) 
        {
            args.push_back(arg);
        }

        // 设置 argc
        argc = args.size();

        // 分配内存给 argv
        argv = new char*[argc + 1]; // +1 for null terminator

        for (int i = 0; i < argc; ++i) 
        {
            argv[i] = new char[args[i].size() + 1]; // +1 for null terminator
            std::strcpy(argv[i], args[i].c_str());
        }
        argv[argc] = nullptr; // 设置最后一个元素为 nullptr
    }

    void freeArgv() 
    {
        if (argv) 
        {
            for (int i = 0; i < argc; ++i) 
            {
                delete[] argv[i]; // 释放每个参数的内存
            }
            delete[] argv; // 释放 argv 的内存
            argv = nullptr; // 防止重复释放
        }
    }

public:
    ArgConverter(const std::string& input) : argc(0), argv(nullptr) 
    {
        stringToArgcArgv(input);
    }

    ~ArgConverter() 
    {
        freeArgv();
    }

    int getArgc() const 
    {
        return argc;
    }

    char** getArgv() const 
    {
        return argv;
    }

};

#endif // _MYALGO_H
	   //
	   //
