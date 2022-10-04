#include "Mystring.h"

string genRandString(int minLen, int maxLen)
{
	string names;
	char temps[2] = { };
	int name_len = 0;

	name_len = (rand() % (maxLen - minLen + 1)) + minLen;

	for (int i = 0; i < name_len; i++)
	{
		if (i == 0)
			temps[0] = rand() % 26 + 'A';				// 첫 글자는 대문자이기 때문에 65(A)부터 90(Z)까지
		else
			temps[0] = rand() % 26 + 'a';				// 나머지 글자는 소문자로 

		// 문자열로 만듦
		temps[1] = '\0';

		names.append(temps);						// names에 append한다.						
	}

	return names;
}