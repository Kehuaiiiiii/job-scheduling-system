#pragma once
#include <Windows.h>

class COLOR
{
public:
	const static int RED = FOREGROUND_RED | 0x8;
	const static int GREEN = FOREGROUND_GREEN | 0x8;
	const static int BLUE = FOREGROUND_BLUE | 0x8;
};

class KEY
{
public:
	const static int UP = 72;
	const static int DOWN = 80;
	const static int ENTER = 13;
	const static int ESC = 27;
};

class TABLE
{
public:
	const static int ROW_WEIGHT = 13;
};