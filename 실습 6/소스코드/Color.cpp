#include "Color.h"

ostream& printRGB(ostream& ostr, const COLORREF color)		// 색깔 출력 함수
{
	// 6자리만 출력, 16진수, 대문자 형식
	ostr.fill('0');
	ostr << setw(6) << uppercase << hex << color << dec;
	ostr.fill(' ');
	return ostr;
	// TODO: 여기에 return 문을 삽입합니다.
}
