#ifndef CYCLICSHIFTHASHCODE_H
#define CYCLICSHIFTHASHCODE_H

#include <string>

#define BIT_SHIFTS 5
#define BITS_INT 32

using namespace std;

class CyclicShiftHashCode
{
public:
	int operator() (const string key)
	{
		int len = key.length();				// 길이를 구함 
		unsigned int h = 0;
		for (int i = 0; i < len; i++)			
		{
			h = (h << BIT_SHIFTS) | (h >> (BITS_INT - BIT_SHIFTS));			// 회전시프트 함
			h += (unsigned int)key.at(i);					// 문자열의 값 하나를 h에 더함
		}

		return h;
	}
};

#endif // !CYCLICSHIFTHASHCODE_H

