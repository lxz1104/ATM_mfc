#ifndef _MYLIB_H_
#define _MYLIB_H_


//设置光标位置
void SetPosition(short int x,short  int y);

//隐藏光标
void hideCursor();
//显示光标
void showCursor();
//登录界面
void Interface_Login(int Start_x,int Start_y);
//局部清屏
void LocalClear(int start_x, int start_y, int end_x, int end_y);


#endif // !_MYLIB_H_
#pragma once
