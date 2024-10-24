<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : Class AlgoBase.md
   Last Modified : 2024-10-24 17:49
   Describe      : 

--->

Class PRAlgoBase
====

### 类的关联文档

### 类用途和应用场景说明

Class PRAlgoBase是所有页面置换算法的基类
这个类的目的是：
1. 给一级页表提供一个指针接口
2. 子类补全Base函数中规定的若干接口来满足页面算法的需求
3. 页表能够使用这个类的公开虚函数来调用子类的函数

### 源代码

```c++
class PRAlgoBase
{
	private:
		int PageReplacementCounter;
		void increasePRCounter();
		void PrintPRCounter();
		int GetPRCounter();
		void ResetPRCounter();

	public:
		virtual void init();
		virtual void clear();
		virtual int16_t size();

		virtual int16_t AddNewPagePtr(PageEntry* PagePtr);
		virtual int16_t AddNewPage(int8_t PageID);
		virtual int16_t CurrentPageUniqueVar();
		virtual int8_t	GetReplacePageID();
		virtual bool UpdatePageUniqVar();
		virtual bool RemovePageID();

		// DEBUG FUNCITON
		virtual int16_t CheckReplacePageID();
};

```

### 类的公开函数接口

#### virtual void init()

权限：公开public
用途：初始化类，子类必须重载

#### virtual void clear()

权限：公开public
用途：重置类到初始状态，子类必须重载

#### virtual int16_t size()

权限：公开public
用途：返回目前PRAlgoBase中管理的在内存中的页面数量（非磁盘缓存的页面）

#### virtual int16_t AddNewPagePtr(PageEntry \*PagePtr)

权限：公开public
用途：加入一个新页面，返回值内容待定
同类型函数：AddNewPageID(int8_t PageID) | 可能被删除

#### virtual int16_t CurrentPageUniqueVar()

权限：公开public
用途：获取页面算法标记在当前函数执行时刻的用于执行页面交换算法的标志
Q: 为什么这个函数能够设置为public?
A ：因为页面算法（FIFO，LRU，Clock，ImprovedClock）通常来说算法选择页面的方法是与时间强相关，由于时间轴必定单调递增，所以能够保证后更新的算法依赖值一定是单调递增的，因此能够保证中途执行调用计算算法依赖值的函数不会影响页面置换算法的正确性。

#### virtual int8_t GetReplacePageID()

权限：公开public
用途：在需要剔除页面时获取要交换出内存的页面ID

#### virtual bool RemovePagePtr(PageEntry \*PagePtr)

权限：公开public
用途：在deAlloc()环节中，移除页面置换管理算法中存储的页面指针信息


### 类的DEBUG函数

#### virtual PageEntry* CheckReplacePagePtr();

权限：公开public
用途：检查某页面算法当前的换出页面（指针）

#### virtual int8_t CheckReplacePageID(PageEntry \*PagePtrBegin )

权限：公开public
用途：检查某页面算法当前的换出页面（下标）

#### virtual bool CheckPagePtrExist(PageEntry \*PagePtr)

权限：公开public
用途：检查页面置换算法中是否存在某一页内存

#### virtual void PrintReplacePageInfo();

权限：公开public
用途：输出当前要置换的页面的信息（待定
