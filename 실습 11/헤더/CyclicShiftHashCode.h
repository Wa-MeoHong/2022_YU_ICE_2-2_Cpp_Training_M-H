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
		int len = key.length();
		unsigned int h = 0;
		for (int i = 0; i < len; i++)
		{
			h = (h << BIT_SHIFTS) | (BITS_INT - BIT_SHIFTS);
			h += (unsigned int)key.at(i);
		}

		return h;
	}
};

#endif // !CYCLICSHIFTHASHCODE_H



