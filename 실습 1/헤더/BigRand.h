#ifndef BIGRAND_H
#define BIGRAND_H

#include <iostream>						// 기본적인 standard 라이브러리를 담고 있음
#include <fstream>						// 파일 입출력 관련 라이브러리
#include <iomanip>						// 출력형식 지정을 할때 쓰는 라이브러리
#include <stdbool.h>
using namespace std;

/*
					>>> 함수 목록 <<<
	1. 랜덤 수를 생성하는 함수
	2. 셔플해주는 함수
	3. 난수를 출력하는 함수

*/
int* genBigRandArray(int num_rands, int offset);							
void suffleArray(int* bigRand, int num_rands);								
void fPrintBigRandArray(ofstream& fout, int* bigRand, int num_rands);		

#endif