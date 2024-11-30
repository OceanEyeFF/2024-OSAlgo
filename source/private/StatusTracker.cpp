/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : StatusTracker.cpp
#   Last Modified : 2024-11-16 12:21
#   Describe      : 
#
# ====================================================*/

#include "StatusTracker.h"
#include "libgo/coroutine.h"
#include "easylogging++.h"

int StatusTracker::size()
{
	return StatusLog.size();
}

void StatusTracker::PushLog(std::string status)
{
	StatusLog.push_back(status);
}

void StatusTracker::PopLog()
{
	if(!StatusLog.empty()) StatusLog.pop_back();
}

void StatusTracker::Clear()
{
	while(!StatusLog.empty()) StatusLog.pop_back();
}

void StatusTracker::PrintStatus()
{
	std::cout << TrackerDescriber << std::endl;
	std::cout << "Print To Screen:\n";
	for (const auto& status : StatusLog) {
		std::cout << status << '\n';
	}
}

void StatusTracker::PrintStatusToLog()
{
	VLOG(1) << "Print To Log\n";
	for (const auto& status : StatusLog) {
		VLOG(2) << "function Record:\t" << status;
	}
}

void StatusTracker::SetDescriber(std::string Describer)
{
	TrackerDescriber = Describer;
	VLOG(0) << TrackerDescriber;
	VLOG(0) << "Print To Log File";
}
