/*ConsoleDisplay.h  cmd displayed */
#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include <Windows.h>

HANDLE initConsoleHandler();			// 콘솔핸들러 초기화
void cls(HANDLE hConsole);				// 콘솔창 스크롤하기
void closeConsoleHandler(HANDLE hndlr);	// 콘솔창 닫기
int gotoxy(HANDLE consoleHandler, int x, int y);	// 콘솔창 커서 옮기기 

#endif // !CONSOLE_DISPLAY_H
