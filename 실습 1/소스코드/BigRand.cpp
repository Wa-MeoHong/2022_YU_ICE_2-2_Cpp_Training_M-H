#include "BigRand.h"

#define RANDOMIZE() srand((unsigned int)time(NULL))
#define BIG_SIZE 500
#define LINESIZE 20

// BigRand(32764 = RAND_MAX ���� �� ū ����)�� ����� �Լ�
int* genBigRandArray(int num_rands, int offset)	
{
	int* bigRand = NULL;									

	bigRand = (int*)calloc(sizeof(int), num_rands);				// num_rands(������ ������ �� ����)��ŭ �����Ҵ� 

	/* 
				>> �ߺ��� ���� ������ ���� �����ϱ� ������ �̷� ��ĵ� ���� <<
		1. for���� ���� 0 ~ ������ �� ���� 1���� ���ʴ�� �迭�� �������
		2. �� ��, suffle�� ���� ������ ������� 
	*/
	for (int i = 0; i < num_rands; i++)							
	{															
		bigRand[i] = i + offset;												
	}
	suffleArray(bigRand, num_rands);

	return bigRand;												// bigRand�� �迭 �ּҸ� ��ȯ, �̷��� �����Ҵ��� �迭�� �̾���
}

// ���� �迭�� ������ �ڼ��� �Լ�
void suffleArray(int* bigRand, int num_rands)
{
	int i1, i2, temp, i = 0;
	RANDOMIZE();												// ���� �õ� ����

	while (i != num_rands)										// i�� ���� ��������
	{
		// �ٲ� ���ڸ� 2�� ������. ������ RAND�Լ��� ����
		i1 = (((unsigned int)rand() << 15) | rand()) % num_rands;
		i2 = (((unsigned int)rand() << 15) | rand()) % num_rands;

		// swapping, �ٲܶ��� temp���� �� ���� �ϳ��� �ʿ���
		temp = bigRand[i1];
		bigRand[i1] = bigRand[i2];
		bigRand[i2] = temp;
		
		i++;													// i ����
	}
}

// BigRand�迭�� ��������ϴ� �Լ�
void fPrintBigRandArray(ofstream& fout, int* bigRand, int num_rands)
{
	int count = 0;												// ����� �� �ʿ���
	int num_lines = 5;											// �߰� ������ ��, ���ٸ� ����ϰ� �ϴ°��� �ʿ�

	/*				>>> ��� ��� <<<
		1. num_rands(������ ����)�� ���� ��¹���� �����Ѵ�. 
		2. BIG_SIZE���� ���� ���, �������� ���
		3. BIG_SIZE���� ���� ���, ó�� 50�� ����ϰ� ���� �߰� ���� ��, ���� �ѹ��� 50�� ���
	*/

	if (num_rands < BIG_SIZE)
	{
		num_lines = num_rands / LINESIZE; 
	}

	for (int i = 0; i < num_lines; i++)
	{
		for (int j = 0; j < LINESIZE; j++)
		{
			if (count == num_rands)								// ���� ��������� Ż��
				break;
			fout << setw(7) << bigRand[count] ;					// ���, �ڸ����� 7�� ������, 7�ڸ�
			count++;
		}
		fout << endl;											// 10�� ��� �� ����
	}

	// ������ ���� BIG_SIZE���� �� ū ���, ���� ��, ����Ѵ�.
	if (num_rands >= BIG_SIZE)
	{
		fout << ". . . . . . . ." << endl;						// �����ϴ� ��
		count = num_rands - (LINESIZE * num_lines);

		for (int i = 0; i < num_lines; i++)
		{
			for (int j = 0; j < LINESIZE; j++)
			{
				fout << setw(7) << bigRand[count];				// ���
				count++;
			}
			fout << endl;										// ���� ����
		}
		fout << endl;
	}
}