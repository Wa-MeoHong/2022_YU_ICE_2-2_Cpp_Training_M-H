/*ConsoleDisplay.h  cmd displayed */
#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include <Windows.h>

HANDLE initConsoleHandler();			// �ܼ��ڵ鷯 �ʱ�ȭ
void cls(HANDLE hConsole);				// �ܼ�â ��ũ���ϱ�
void closeConsoleHandler(HANDLE hndlr);	// �ܼ�â �ݱ�
int gotoxy(HANDLE consoleHandler, int x, int y);	// �ܼ�â Ŀ�� �ű�� 

#endif // !CONSOLE_DISPLAY_H
