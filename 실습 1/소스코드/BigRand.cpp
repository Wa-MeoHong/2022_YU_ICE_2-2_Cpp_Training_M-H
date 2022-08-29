#include "BigRand.h"

#define RANDOMIZE() srand((unsigned int)time(NULL))
#define BIG_SIZE 500
#define LINESIZE 20

// BigRand(32764 = RAND_MAX 보다 더 큰 난수)를 만드는 함수
int* genBigRandArray(int num_rands, int offset)	
{
	int* bigRand = NULL;									

	bigRand = (int*)calloc(sizeof(int), num_rands);				// num_rands(생성할 랜덤한 수 갯수)만큼 동적할당 

	/* 
				>> 중복이 없는 랜덤한 수를 생성하기 때문에 이런 방식도 가능 <<
		1. for문을 통해 0 ~ 생성한 수 까지 1열로 차례대로 배열에 집어넣음
		2. 그 후, suffle을 통해 순서를 섞어버림 
	*/
	for (int i = 0; i < num_rands; i++)							
	{															
		bigRand[i] = i + offset;												
	}
	suffleArray(bigRand, num_rands);

	return bigRand;												// bigRand의 배열 주소를 반환, 이렇게 동적할당한 배열은 이어짐
}

// 만든 배열의 순서를 뒤섞는 함수
void suffleArray(int* bigRand, int num_rands)
{
	int i1, i2, temp, i = 0;
	RANDOMIZE();												// 랜덤 시드 생성

	while (i != num_rands)										// i가 난수 개수까지
	{
		// 바꿀 숫자를 2개 선정함. 선정은 RAND함수로 결정
		i1 = (((unsigned int)rand() << 15) | rand()) % num_rands;
		i2 = (((unsigned int)rand() << 15) | rand()) % num_rands;

		// swapping, 바꿀때는 temp같은 빈 변수 하나가 필요함
		temp = bigRand[i1];
		bigRand[i1] = bigRand[i2];
		bigRand[i2] = temp;
		
		i++;													// i 증가
	}
}

// BigRand배열을 파일출력하는 함수
void fPrintBigRandArray(ofstream& fout, int* bigRand, int num_rands)
{
	int count = 0;												// 출력할 때 필요함
	int num_lines = 5;											// 중간 생략할 시, 몇줄만 출력하게 하는가에 필요

	/*				>>> 출력 방식 <<<
		1. num_rands(난수의 개수)에 따라 출력방식을 결정한다. 
		2. BIG_SIZE보다 적을 경우, 생략없이 출력
		3. BIG_SIZE보다 많을 경우, 처음 50개 출력하고 나서 중간 생략 후, 끝에 한번더 50개 출력
	*/

	if (num_rands < BIG_SIZE)
	{
		num_lines = num_rands / LINESIZE; 
	}

	for (int i = 0; i < num_lines; i++)
	{
		for (int j = 0; j < LINESIZE; j++)
		{
			if (count == num_rands)								// 전부 출력했으면 탈출
				break;
			fout << setw(7) << bigRand[count] ;					// 출력, 자리수를 7로 지정해, 7자리
			count++;
		}
		fout << endl;											// 10개 출력 후 엔터
	}

	// 랜덤한 수가 BIG_SIZE보다 더 큰 경우, 생략 후, 출력한다.
	if (num_rands >= BIG_SIZE)
	{
		fout << ". . . . . . . ." << endl;						// 생략하는 것
		count = num_rands - (LINESIZE * num_lines);

		for (int i = 0; i < num_lines; i++)
		{
			for (int j = 0; j < LINESIZE; j++)
			{
				fout << setw(7) << bigRand[count];				// 출력
				count++;
			}
			fout << endl;										// 한줄 띄우기
		}
		fout << endl;
	}
}