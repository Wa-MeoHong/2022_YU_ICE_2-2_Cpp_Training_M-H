#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>

using namespace std;

// ���� Ŭ���� COLORRREF�� Windows.h�� ���ǵǾ� ����.
// RGB�� �󸶳� �ִ°��� ���� ���� �޸��� �� ����
// 16����(hexadeciaml)�� ���� 0x00bbggrr ( ��, ��, �� ���� )

const COLORREF RGB_BLACK	= 0x00000000;
const COLORREF RGB_RED		= 0x000000FF;
const COLORREF RGB_GREEN	= 0x0000FF00;
const COLORREF RGB_BLUE		= 0x00FF0000;
const COLORREF RGB_ORANGE	= 0x0000A5FF;
const COLORREF RGB_YELLOW	= 0x0000FFFF;
const COLORREF RGB_MAGENTA	= 0x00FF00FF;
const COLORREF RGB_WHITE	= 0x00FFFFFF;

ostream& printRGB(ostream& ostr, const COLORREF color);

#endif // !COLOR_H
