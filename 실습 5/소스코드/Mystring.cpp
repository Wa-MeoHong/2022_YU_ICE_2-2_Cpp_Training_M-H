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
			temps[0] = rand() % 26 + 'A';				// ù ���ڴ� �빮���̱� ������ 65(A)���� 90(Z)����
		else
			temps[0] = rand() % 26 + 'a';				// ������ ���ڴ� �ҹ��ڷ� 

		// ���ڿ��� ����
		temps[1] = '\0';

		names.append(temps);						// names�� append�Ѵ�.						
	}

	return names;
}