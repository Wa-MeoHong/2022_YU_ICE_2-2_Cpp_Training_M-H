#include "ConsoleDisplay.h"
#include <stdio.h>

/*                      member functions        
        1. initConsoleHandler()          :  �ܼ��ڵ鷯 �ʱ� ���� 
        2. cls(hConsole)                 :  �ܼ�â ��ũ��
        3. closeConsoleHandler(hndlr)    :  �ܼ� �ڵ鷯 �ݱ�
        4. gotoxy(consoleHandler, x, y)  :  x, y ��ǥ�� Ŀ�� �̵�  */

HANDLE initConsoleHandler()
{
    HANDLE consoleHandler;
    HANDLE stdCnslHndlr;

    // �ܼ� �ڵ鷯�� ��� ( STD_OUTPUT_HANDLE�� ���� )
    stdCnslHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
    consoleHandler = stdCnslHndlr;

    // ���� ��, ��ȯ
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
    CloseHandle(hndlr); // �ܼ� �ڵ鷯 �ݱ�
}

int gotoxy(HANDLE consoleHandler, int x, int y)
{
    if (consoleHandler == INVALID_HANDLE_VALUE)
        return 0;       // ���� consoleHandler�� ���� ����(INVALID)��� �׳� 0�� ��ȯ
    COORD coords = { static_cast<short>(x), static_cast<short>(y) };
    // static_cast ���ø�����  x, y��ǥ�� ������ COORD �ڷ����� ����־���

    SetConsoleCursorPosition(consoleHandler, coords);   // �ܼ��ڵ鷯 Ŀ���� ��ġ ����
}
