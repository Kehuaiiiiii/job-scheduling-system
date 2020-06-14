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
			// job����ʱ�����һ��job���ʱ������ζ��cpu�п���ʱ��
			begin = job.getArriveTime();
		}
		else {
			// cpu�޿��У���������
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
				// ��������job��ֱ�ӿ�ʼ����
				begin = job.getArriveTime();
				finish = begin + job.getProcessTime();
				Job temp(job.getName(), job.getArriveTime(),
						job.getProcessTime(), begin, finish);
				result.push_back(temp);
				isDone = true;
			}
			else {
				// ȡ�������д���ʱ����̵�job
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
			// ��������еȴ�����
			queue.push(job);
		}

	}
	// ���������ʣ���job
	while (!queue.empty())
	{
		// ȡ�������д���ʱ����̵�job
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
	// ��Ӧ�� = ���ȴ�ʱ�� + ����ʱ�䣩/ ����ʱ�� = 1 + �ȴ�ʱ�� / ����ʱ��
	for (auto job : jobs) {
		bool isDone = false;
		while (finish < job.getArriveTime())
		{
			if (queue.empty()) {
				// ��������job��ֱ�ӿ�ʼ����
				begin = job.getArriveTime();
				finish = begin + job.getProcessTime();
				Job temp(job.getName(), job.getArriveTime(),
						job.getProcessTime(), begin, finish);
				result.push_back(temp);
				isDone = true;
			}
			else {
				// ȡ����������Ӧ����ߵ�job
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
			// ��������еȴ�����
			queue.push_back(job);
		}
	}
	// ���������ʣ���job
	while (!queue.empty())
	{
		// ȡ����������Ӧ����ߵ�job
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
		//cout << "�����Ӧ��:" << maxResponseRadio << endl;
		Job current = queue[index];
		queue.erase(queue.begin() + index);
		begin = finish;
		finish = begin + current.getProcessTime();
		Job temp(current.getName(), current.getArriveTime(),
				current.getProcessTime(), begin, finish);
		result.push_back(temp);
	}
}
