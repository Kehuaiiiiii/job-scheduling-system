#include "JobSchedulingSystem.h"
#include <io.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

void JobSchedulingSystem::start()
{
	vector<string> menus = {"����ȡ�ļ���\n",
							"����    ����\n"};
	int choice = 0;
	while (true)
	{
		console.clear();
		console.print("   ��ӭʹ����ҵ������ʾϵͳ   \n", 0, 0, COLOR::GREEN);
		console.print("   �밴��������ѡ��   \n", 2, 10, COLOR::GREEN);
		console.print("   Enter��ȷ�ϣ�Esc���˳�   \n", 0, 11, COLOR::GREEN);
		console.print("   by��B17070214 Ҷ�ƻ�   \n", 6, 14, COLOR::GREEN);
		for (int i = 0; i < menus.size(); i++) {
			if (i == choice)
				console.print(menus[i], 8, i + 2, COLOR::RED);
			else console.print(menus[i], 8, i + 2, COLOR::GREEN);
		}
		int key = console.getKey();
		if (key == KEY::ESC)
			exit(0);
		if (key == KEY::UP)
			choice = max(0, choice - 1);
		if (key == KEY::DOWN)
			choice = min(menus.size() - 1, choice + 1);
		if (key == KEY::ENTER) {
			switch (choice)
			{
			case 0:
				readFiles();
				break;
			case 1:
				exit(0);
				break;
			default:
				console.error("[JobSchedulingSystem::start] choice illegal");
				exit(0);
			}
		}
	}
}

void JobSchedulingSystem::readFiles()
{
	vector<string> files;
	string path = "./test/*.txt";
	// �ļ����  
	long hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileInfo;
	hFile = _findfirst(path.c_str(), &fileInfo);
	if (hFile != -1)
	{
		do
		{
			string name = fileInfo.name;
			// ȥ��.txt��׺
			files.push_back(name.substr(0, name.length() - 4));
		} while (_findnext(hFile, &fileInfo) == 0);
		_findclose(hFile);
	}
	//for (auto file : files)
	//	cout << file << endl;
	int choice = 0;
	while (true)
	{
		console.clear();
		for (int i = 0; i < files.size(); i++) {
			if (i == choice)
				console.print(files[i], 8, i + 2, COLOR::RED);
			else console.print(files[i], 8, i + 2, COLOR::GREEN);
		}
		int key = console.getKey();
		if (key == KEY::ESC)
			return;
		if (key == KEY::UP)
			choice = max(0, choice - 1);
		if (key == KEY::DOWN)
			choice = min(files.size() - 1, choice + 1);
		if (key == KEY::ENTER) {
			string filePath = "./test/" + files[choice] + ".txt";
			openFile(filePath);
		}
	}
}

void JobSchedulingSystem::openFile(string path)
{
	ifstream infile(path, ios::in);
	if (!infile.is_open()) {
		console.error("[JobSchedulingSystem::openFile] file can not open");
		return;
	}
	jobs.clear();
	string line;
	while (getline(infile, line))
	{
		stringstream ss(line);
		string name, arriveTime, processTime;
		ss >> name >> arriveTime >> processTime;
		Job job(name, arriveTime, processTime);
		jobs.push_back(job);
	}
	infile.close();
	// ��arriveTime����ҵ����
	sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
		return a.getArriveTime() < b.getArriveTime();
	});
	// ��ҵ����
	schedule();
}

void JobSchedulingSystem::schedule()
{
	result4FCFS.clear();
	result4SJF.clear();
	result4HRRF.clear();
	// ִ����ҵ�����㷨
	jobScheduling.FCFS(jobs, result4FCFS);
	jobScheduling.SJF(jobs, result4SJF);
	jobScheduling.HRRF(jobs, result4HRRF);
	// չʾ���
	showResult();
}

void JobSchedulingSystem::showResult()
{
	console.clear();
	console.print("�����ȷ�����Ƚ��\n", COLOR::RED);
	showTable(result4FCFS);
	console.print("�����ҵ���ȵ��Ƚ��\n", COLOR::RED);
	showTable(result4SJF);
	console.print("�����Ӧ�����ȵ��Ƚ��\n", COLOR::RED);
	showTable(result4HRRF);
	while (true)
	{
		int key = console.getKey();
		if (key == KEY::ESC)
			return;
	}
}

void JobSchedulingSystem::showTable(const vector<Job>& results)
{
	vector<vector<string>> table;
	vector<string> row;
	vector<string> HEAD = { "��ҵ��", "����ʱ��", "����ʱ��", "��ʼʱ��",
							"���ʱ��", "��תʱ��", "��Ȩ��תʱ��" };
	for (int i = 0; i < HEAD.size(); i++) {
		row.push_back(HEAD[i]);
	}
	table.push_back(row);

	// ��תʱ���ܺ�
	double sumTT = 0;
	// ��Ȩ��תʱ���ܺ�
	double sumWTT = 0;
	// stringstream�����������2λС��
	ostringstream oss;
	oss.precision(2);

	for (auto result : results) {
		row.clear();

		row.push_back(result.getName());
		row.push_back(result.getArriveTime().toString());
		row.push_back(result.getProcessTime().toString());
		row.push_back(result.getBeginTime().toString());
		row.push_back(result.getFinishTime().toString());

		int TT = calcTT(result.getArriveTime(), result.getFinishTime());
		double WTT = calcWTT(result.getArriveTime(),
			result.getFinishTime(), result.getProcessTime());
		sumTT += TT;
		sumWTT += WTT;
		oss.str("");
		oss << WTT;
		row.push_back(to_string(TT));
		row.push_back(oss.str());

		table.push_back(row);
	}

	// ��ӡtable
	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].size(); j++) {
			table[i][j].resize(TABLE::ROW_WEIGHT);
			console.print(table[i][j] + " ", COLOR::GREEN);
		}
		console.print("\n", COLOR::GREEN);
	}
	double ATT = sumTT / results.size();
	double AWTT = sumWTT / results.size();
	console.print("ƽ����תʱ�䣺" + to_string(ATT) + "\n", COLOR::BLUE);
	console.print("ƽ����Ȩ��תʱ�䣺" + to_string(AWTT) + "\n", COLOR::BLUE);
	console.print("\n\n", COLOR::GREEN);
}

int JobSchedulingSystem::calcTT(const Time& arrive, const Time& finish)
{
	int finishMinute = 60 * finish.getHour() + finish.getMinute();
	int arriveMinute = 60 * arrive.getHour() + arrive.getMinute();
	return finishMinute - arriveMinute;
}

double JobSchedulingSystem::calcWTT(const Time& arrive,
					const Time& finish, const Time& process)
{
	int finishMinute = 60 * finish.getHour() + finish.getMinute();
	int arriveMinute = 60 * arrive.getHour() + arrive.getMinute();
	int processMinute = 60 * process.getHour() + process.getMinute();
	return double(finishMinute - arriveMinute) / processMinute;
}