#include "ConsoleUtil.h"
#include <iostream>
#include "Constant.h"
using namespace std;

ConsoleUtil::ConsoleUtil()
{
	// ��ȡ��׼������
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	// ��ȡ�����Ϣ
	GetConsoleCursorInfo(handle, &cci);
	// ���ù���С
	cci.dwSize = 1;
	// ���ù�겻�ɼ�
	cci.bVisible = 0;
	// ���ù����Ϣ
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
