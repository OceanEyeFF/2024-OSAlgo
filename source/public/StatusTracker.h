/* ====================================================
#   Copyright (C) 2024  All rights reserved.
#
#   Author        : OceanEyeFF
#   Email         : fdch00@163.com
#   File Name     : StatusTracker.h
#   Last Modified : 2024-11-10 21:59
#   Describe      : 
#
# ====================================================*/

#ifndef  _STATUSTRACKER_H
#define  _STATUSTRACKER_H

#include <string>
#include <vector>
#include <deque>
#include <mutex>

#include "libgo/coroutine.h"
#include "easylogging++.h"

class StatusTracker
{
private:
    std :: deque<std::string> StatusLog;
	std :: string TrackerDescriber;
	std :: mutex mtx;

public:
	int size();
    void PushLog(std::string status);
	void PopLog();
	void Clear();

    void PrintStatus();
	void PrintStatusToLog();
	void SetDescriber(std::string Describer);
};

#endif // _STATUSTRACKER_H
	   //
	   //
