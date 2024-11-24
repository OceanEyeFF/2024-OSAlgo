/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : PageSystemGlobals.cpp
#   Last Modified : 2024-11-16 16:41
#   Describe      : 
#
# ====================================================*/

#include "PageSystemGlobals.h"
#include "MessageBus.hpp"
#include "PageContainer.h"
#include "StatusTracker.h"

// AddressPtr and AddressConj

/* Address has 16bits
 * 0000000000000000
 * 1122222233333333
 * 1 : FstPage FirstPage
 * 2 : PageContainer SecondPage
 * 3 : innerBlockID
 */

// 虚拟地址结构体访问

AddressConj::AddressConj()
{
	innerAddress = PageID = PageContainerID = 0;
}

AddressConj::AddressConj(AddressPtr ptr)
{
	PageContainerID	= (ptr.__ptr__ >>  FIRST_LEVEL_SHIFT) & FIRST_LEVEL_MASK;
	PageID			= (ptr.__ptr__ >> SECOND_LEVEL_SHIFT) & SECOND_LEVEL_MASK;
//	innerAddress	= (ptr.__ptr__ >>  THIRD_LEVEL_SHIFT) & THIRD_LEVEL_MASK;
	innerAddress	= ptr.__ptr__ & THIRD_LEVEL_MASK;

}

AddressConj::AddressConj(int8_t __PageContainerID, int8_t __PageID, int8_t __innerAddress):
	PageContainerID(__PageContainerID),PageID(__PageID),innerAddress(__innerAddress)
{
}

AddressPtr AddressConj::ToPtr()
{
	AddressPtr ret;
	ret.__ptr__= 
		(PageContainerID << FIRST_LEVEL_SHIFT) |
		(PageID << SECOND_LEVEL_SHIFT) |
		(innerAddress << THIRD_LEVEL_SHIFT);
	return ret;
}

// Tracker definition
namespace SystemTracker
{
	StatusTracker Tracker;
	void RegistMessageBus()
	{
		Tracker.SetDescriber("----Memory Tracker Log----");
		MessageBus::Attach("MemLogPush",&StatusTracker::PushLog,&Tracker);
		MessageBus::Attach("MemLogPop",&StatusTracker::PopLog,&Tracker);
		MessageBus::Attach("MemLogClear",&StatusTracker::Clear,&Tracker);

		MessageBus::Attach("MemStatusLogPrintFile",&StatusTracker::PrintStatusToLog,&Tracker);
		MessageBus::Attach("MemStatusLogPrintScreen",&StatusTracker::PrintStatus,&Tracker);
	}

	void CallLog(std::string CLASSNAME, std::string LOG)
	{
		std :: string LOGINFO = "Part:\t"+CLASSNAME+"\tFuncion Name:\t"+LOG+"\t";
		MessageBus::Notify("MemLogPush",LOGINFO);
		if(Tracker.size() == 5)
		{
//			MessageBus::Notify("MemStatusLogPrintScreen"); // 探底输出
			MessageBus::Notify("MemStatusLogPrintFile"); // 探底输出
		}
	}

	void RemoveLog()
	{
		MessageBus::Notify("MemLogPop");
	}

	void FlushTracker()
	{
#ifdef _DEBUG
		MessageBus::Notify("MemStatusLogPrintScreen"); // 探底输出
#endif
//		MessageBus::Notify("MemStatusLogPrintFile");	// 探底输出
														// Deprecated
	}
}