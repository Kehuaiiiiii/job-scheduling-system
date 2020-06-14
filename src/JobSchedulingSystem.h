#pragma once
#include <vector>
#include <string>
#include "JobScheduling.h"
#include "Job.h"
#include "ConsoleUtil.h"
#include "Constant.h"
using namespace std;

class JobSchedulingSystem
{
public:
	void start();
	void readFiles();
	void openFile(string path);
	void schedule();

private:
	JobScheduling jobScheduling;
	vector<Job> jobs;
	vector<Job> result4FCFS;
	vector<Job> result4SJF;
	vector<Job> result4HRRF;
	ConsoleUtil console;

	void showResult();
	void showTable(const vector<Job>& results);
	int calcTT(const Time& arrive, const Time& finish);
	double calcWTT(const Time& arrive, const Time& finish, const Time& process);
};