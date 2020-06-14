#pragma once
#include <vector>
#include "Job.h"
using namespace std;

class JobScheduling
{
public:
	// 先来先服务 (First Come First Served)
	void FCFS(const vector<Job>& jobs, vector<Job>& result);
	// 最短作业优先 (Shortest Job First)
	void SJF(const vector<Job>& jobs, vector<Job>& result);
	// 最高响应比优先 (Highest Response Ratio First)
	void HRRF(const vector<Job>& jobs, vector<Job>& result);
};
