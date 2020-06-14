#include "ConsoleUtil.h"
#include <iostream>
#include "Constant.h"
using namespace std;

ConsoleUtil::ConsoleUtil()
{
	// 获取标准输出句柄
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	// 获取光标信息
	GetConsoleCursorInfo(handle, &cci);
	// 设置光标大小
	cci.dwSize = 1;
	// 设置光标不可见
	cci.bVisible = 0;
	// 设置光标信息
	SetConsoleCursorInfo(handle, &cci);
}

ConsoleUtil::~ConsoleUtil()
{
	CloseHandle(handle);
}

void ConsoleUtil::print(string s, int color)
{
	SetConsoleTextAttribute(handle, color);
	cout << s;
}

void ConsoleUtil::print(string s, int x, int y, int color)
{
	SetConsoleTextAttribute(handle, color);
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
	cout << s;
}

void ConsoleUtil::clear()
{
	system("cls");
}

int ConsoleUtil::getKey()
{
	fflush(stdin);
	int key = _getch();
	return key;
}

void ConsoleUtil::error(string s)
{
	cerr << s << endl;
}
