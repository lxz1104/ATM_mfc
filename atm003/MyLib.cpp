#include "MyLib.h"
#include <Windows.h>

#include <iostream>

using std::endl;
using std::cout;

//设置光标位置
void SetPosition(short int x,short int y)
{
	//定义输出句柄
	HANDLE winHandle;
	COORD pos = { x,y };
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//设置光标位置
	SetConsoleCursorPosition(winHandle, pos);
}

//隐藏光标
void hideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//隐藏输入符号
}

//显示光标
void showCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 1 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//隐藏输入符号
}

//交换
inline void Swap(int& a, int& b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}

void Interface_Login(int Start_x, int Start_y)
{
	int i;
	hideCursor();
	SetPosition(Start_x, Start_y);
	cout << "<>==<>==<>==<>==<>==<>==<>==<>==<>==<>==<>==<>==<>" << endl;
	for (i = 0; i < 11; i++)
	{
		while (i % 2 == 0 && i != 1)
		{
			SetPosition(Start_x, Start_y + i + 1);
			cout << "/" << endl;
			break;
		}
		while (i % 2 != 0 || i == 1)
		{
			SetPosition(Start_x, Start_y + i + 1);
			cout << "\\" << endl;
			break;
		}
	}
	for (i = 0; i < 11; i++)
	{
		SetPosition(49 + Start_x, i + 1 + Start_y);
		while (i % 2 == 0 && i != 1)
		{
			cout <<"\\" << endl;
			break;
		}
		while (i % 2 != 0 || i == 1)
		{
			cout << "/" << endl;
			break;
		}
	}
	SetPosition(Start_x, Start_y + 9);
	cout << "<>==<>==<>==<>==<>==<>==<>==<>==<>==<>==<>==<>==<>" << endl;
	SetPosition(Start_x, Start_y + 11);
	cout << "<>==<>==<>==<>==<>==<>==<>==<>==<>==<>==<>==<>==<>" << endl;
	SetPosition(Start_x + 18, Start_y + 10);
	showCursor();
}

void LocalClear(int start_x, int start_y, int end_x, int end_y)
{
	if (start_x > end_x && start_y <= end_y)
	{
		Swap(start_x, end_x);
	}
	else if (start_x <= end_x && start_y > end_y)
	{
		Swap(start_y, end_y);
	}
	else if (start_x > end_x && start_y > end_y)
	{
		Swap(start_x, end_x);
		Swap(start_y, end_y);
	}
	hideCursor();
	for (register int i = start_y; i <= end_y; ++i)
	{
		SetPosition(start_x, start_y + i - start_y);
		for (register int  j = start_x; j <= end_x; ++j)
		{
			cout << char(00100000);
		}
		cout << endl;
	}
	showCursor();
}
