#include "Color.h"

ostream& printRGB(ostream& ostr, const COLORREF color)		// ���� ��� �Լ�
{
	// 6�ڸ��� ���, 16����, �빮�� ����
	ostr.fill('0');
	ostr << setw(6) << uppercase << hex << color << dec;
	ostr.fill(' ');
	return ostr;
	// TODO: ���⿡ return ���� �����մϴ�.
}
