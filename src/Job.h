#pragma once
#include <string>
#include "Time.h"
#include <iostream>
using namespace std;

class Job
{
public:
	Job() {}
	Job(string name, Time arriveTime, Time processTime) {
		this->name = name;
		this->arriveTime = arriveTime;
		this->processTime = processTime;
	}
	Job(string name, Time arriveTime, Time processTime,
				Time beginTime, Time finishTime) {
		this->name = name;
		this->arriveTime = arriveTime;
		this->processTime = processTime;
		this->beginTime = beginTime;
		this->finishTime = finishTime;
	}
	string getName() const { return name; }
	Time getArriveTime() const { return arriveTime; }
	Time getProcessTime() const { return processTime; }
	Time getBeginTime() const { return beginTime; }
	Time getFinishTime() const { return finishTime; }
	//void setFinishTime(Time finishTime) { this->finishTime = finishTime; }
	void display() {
		cout << this->getName() + " "
			+ this->getArriveTime().toString() + " "
			+ this->getProcessTime().toString() + " "
			+ this->getFinishTime().toString() << endl;
	}

private:
	string name;
	Time arriveTime;
	Time processTime;
	Time beginTime;
	Time finishTime;
};

