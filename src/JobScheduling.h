#pragma once
#include <vector>
#include "Job.h"
using namespace std;

class JobScheduling
{
public:
	// �����ȷ��� (First Come First Served)
	void FCFS(const vector<Job>& jobs, vector<Job>& result);
	// �����ҵ���� (Shortest Job First)
	void SJF(const vector<Job>& jobs, vector<Job>& result);
	// �����Ӧ������ (Highest Response Ratio First)
	void HRRF(const vector<Job>& jobs, vector<Job>& result);
};
