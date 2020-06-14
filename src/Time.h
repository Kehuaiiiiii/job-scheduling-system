#pragma once
#include <string>
using namespace std;
class Time
{
public:
	Time() {}
	Time(int hour, int minute) {
		this->hour = hour;
		this->minute = minute;
	}
	Time(string time) {
		// ¸ñÊ½	HH:MM
		this->hour = 10 * (time[0] - '0') + (time[1] - '0');
		this->minute = 10 * (time[3] - '0') + (time[4] - '0');
	}
	string toString() {
		string result = "";
		if (hour < 10)
			result += "0";
		result += to_string(hour);
		result += ":";
		if (minute < 10)
			result += "0";
		result += to_string(minute);
		return result;
	}
	bool operator < (const Time& t) {
		if (hour == t.hour)
			return minute < t.minute;
		return hour < t.hour;
	}
	Time operator + (const Time& t) {
		Time result = Time(hour + t.hour, minute + t.minute);
		result.hour += result.minute / 60;
		result.minute = result.minute % 60;
		return result;
	}
	int getHour() const { return hour; }
	int getMinute() const { return minute; }

private:
	int hour;
	int minute;
};

