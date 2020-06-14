#include "JobScheduling.h"
#include <queue>
using namespace std;

void JobScheduling::FCFS(const vector<Job>& jobs, vector<Job>& result)
{
	if (jobs.size() == 0) return;
	Time begin = Time(0, 0);
	Time finish = Time(0, 0);
	for (auto job : jobs) {
		job.display();
		if (finish < job.getArriveTime()) {
			// job到达时间比上一个job完成时间晚，意味着cpu有空闲时间
			begin = job.getArriveTime();
		}
		else {
			// cpu无空闲，连续工作
			begin = finish;
		}
		finish = begin + job.getProcessTime();
		Job temp(job.getName(), job.getArriveTime(),
				job.getProcessTime(), begin, finish);
		result.push_back(temp);
	}
}

void JobScheduling::SJF(const vector<Job>& jobs, vector<Job>& result)
{
	if (jobs.size() == 0) return;
	Time begin = Time(0, 0);
	Time finish = Time(0, 0);
	auto cmpByProcessTime = [](const Job& a, const Job& b) {
		return b.getProcessTime() < a.getProcessTime();
	};
	priority_queue<Job, vector<Job>, decltype(cmpByProcessTime)> queue(cmpByProcessTime);
	for (auto job : jobs) {
		bool isDone = false;
		while (finish < job.getArriveTime())
		{
			if (queue.empty()) {
				// 队列中无job，直接开始工作
				begin = job.getArriveTime();
				finish = begin + job.getProcessTime();
				Job temp(job.getName(), job.getArriveTime(),
						job.getProcessTime(), begin, finish);
				result.push_back(temp);
				isDone = true;
			}
			else {
				// 取出队列中处理时间最短的job
				Job current = queue.top();
				queue.pop();
				begin = finish;
				finish = begin + current.getProcessTime();
				Job temp(current.getName(), current.getArriveTime(),
					current.getProcessTime(), begin, finish);
				result.push_back(temp);
			}
		}
		if (!isDone) {
			// 放入队列中等待调度
			queue.push(job);
		}

	}
	// 处理队列中剩余的job
	while (!queue.empty())
	{
		// 取出队列中处理时间最短的job
		Job current = queue.top();
		queue.pop();
		begin = finish;
		finish = begin + current.getProcessTime();
		Job temp(current.getName(), current.getArriveTime(),
				current.getProcessTime(), begin, finish);
		result.push_back(temp);
	}
}

void JobScheduling::HRRF(const vector<Job>& jobs, vector<Job>& result)
{
	if (jobs.size() == 0) return;
	Time begin = Time(0, 0);
	Time finish = Time(0, 0);
	vector<Job> queue;
	// 响应比 = （等待时间 + 处理时间）/ 处理时间 = 1 + 等待时间 / 处理时间
	for (auto job : jobs) {
		bool isDone = false;
		while (finish < job.getArriveTime())
		{
			if (queue.empty()) {
				// 队列中无job，直接开始工作
				begin = job.getArriveTime();
				finish = begin + job.getProcessTime();
				Job temp(job.getName(), job.getArriveTime(),
						job.getProcessTime(), begin, finish);
				result.push_back(temp);
				isDone = true;
			}
			else {
				// 取出队列中响应比最高的job
				int index = -1;
				double maxResponseRadio = -1;
				for (int i = 0; i < queue.size(); i++) {
					int nowMinute = 60 * finish.getHour() + finish.getMinute();
					int arriveMinute = 60 * queue[i].getArriveTime().getHour()
							+ queue[i].getArriveTime().getMinute();
					int processMinute = 60 * queue[i].getProcessTime().getHour()
							+ queue[i].getProcessTime().getMinute();
					int waitingMinute = nowMinute - arriveMinute;

					double responseRadio = 1 + double(waitingMinute) / processMinute;
					if (responseRadio > maxResponseRadio) {
						index = i;
						maxResponseRadio = responseRadio;
					}
				}
				Job current = queue[index];
				queue.erase(queue.begin() + index);
				begin = finish;
				finish = begin + current.getProcessTime();
				Job temp(current.getName(), current.getArriveTime(),
					current.getProcessTime(), begin, finish);
				result.push_back(temp);
			}
		}
		if (!isDone) {
			// 放入队列中等待调度
			queue.push_back(job);
		}
	}
	// 处理队列中剩余的job
	while (!queue.empty())
	{
		// 取出队列中响应比最高的job
		int index = -1;
		double maxResponseRadio = -1;
		for (int i = 0; i < queue.size(); i++) {
			int nowMinute = 60 * finish.getHour() + finish.getMinute();
			int arriveMinute = 60 * queue[i].getArriveTime().getHour()
				+ queue[i].getArriveTime().getMinute();
			int processMinute = 60 * queue[i].getProcessTime().getHour()
				+ queue[i].getProcessTime().getMinute();
			int waitingMinute = nowMinute - arriveMinute;

			double responseRadio = 1 + double(waitingMinute) / processMinute;
			if (responseRadio > maxResponseRadio) {
				index = i;
				maxResponseRadio = responseRadio;
			}
		}
		//cout << "最高响应比:" << maxResponseRadio << endl;
		Job current = queue[index];
		queue.erase(queue.begin() + index);
		begin = finish;
		finish = begin + current.getProcessTime();
		Job temp(current.getName(), current.getArriveTime(),
				current.getProcessTime(), begin, finish);
		result.push_back(temp);
	}
}
