#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>

using namespace std;

// 색깔 클래스 COLORRREF는 Windows.h에 정의되어 있음.
// RGB를 얼마나 주는가에 따라 색을 달리할 수 있음
// 16진수(hexadeciaml)의 형태 0x00bbggrr ( 파, 초, 빨 순서 )

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
