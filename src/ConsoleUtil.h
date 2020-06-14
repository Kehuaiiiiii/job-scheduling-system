#pragma once
#include <Windows.h>
#include <conio.h>
#include <string>
using namespace std;

class ConsoleUtil
{
public:
	ConsoleUtil();
	~ConsoleUtil();
	// 打印信息
	void print(string s, int color);
	void print(string s, int x, int y, int color);
	// 清空屏幕
	void clear();
	// 获取按键
	int getKey();
	// 打印错误信息
	void error(string s);

private:
	// 控制台句柄
	HANDLE handle;
	// 控制台光标
	CONSOLE_CURSOR_INFO cci;
	// 光标位置
	COORD pos;
};

