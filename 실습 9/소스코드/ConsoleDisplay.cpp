#include "ConsoleDisplay.h"
#include <stdio.h>

/*                      member functions        
        1. initConsoleHandler()          :  콘솔핸들러 초기 설정 
        2. cls(hConsole)                 :  콘솔창 스크롤
        3. closeConsoleHandler(hndlr)    :  콘솔 핸들러 닫기
        4. gotoxy(consoleHandler, x, y)  :  x, y 좌표로 커서 이동  */

HANDLE initConsoleHandler()
{
    HANDLE consoleHandler;
    HANDLE stdCnslHndlr;

    // 콘솔 핸들러를 얻기 ( STD_OUTPUT_HANDLE로 설정 )
    stdCnslHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
    consoleHandler = stdCnslHndlr;

    // 대입 후, 반환
    return consoleHandler;
}

void cls(HANDLE hConsole)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;
     
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {    return;  }

    scrollRect.Left = 0;     scrollRect.Top = 0;
    scrollRect.Right = csbi.dwSize.X; scrollRect.Bottom = csbi.dwSize.Y;

    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;

    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void closeConsoleHandler(HANDLE hndlr)
{
    CloseHandle(hndlr); // 콘솔 핸들러 닫기
}

int gotoxy(HANDLE consoleHandler, int x, int y)
{
    if (consoleHandler == INVALID_HANDLE_VALUE)
        return 0;       // 만약 consoleHandler가 없는 상태(INVALID)라면 그냥 0를 반환
    COORD coords = { static_cast<short>(x), static_cast<short>(y) };
    // static_cast 탬플릿으로  x, y좌표를 생성해 COORD 자료형에 집어넣어줌

    SetConsoleCursorPosition(consoleHandler, coords);   // 콘솔핸들러 커서의 위치 설정
}
