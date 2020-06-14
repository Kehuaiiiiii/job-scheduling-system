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
	// ��ӡ��Ϣ
	void print(string s, int color);
	void print(string s, int x, int y, int color);
	// �����Ļ
	void clear();
	// ��ȡ����
	int getKey();
	// ��ӡ������Ϣ
	void error(string s);

private:
	// ����̨���
	HANDLE handle;
	// ����̨���
	CONSOLE_CURSOR_INFO cci;
	// ���λ��
	COORD pos;
};

