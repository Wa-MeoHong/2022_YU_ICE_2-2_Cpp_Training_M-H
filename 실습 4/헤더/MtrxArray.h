#ifndef MTRXARRAY_H
#define MTRXARRAY_H

#include "Class_Mtrx.h"
#include <iostream>

using namespace std;

class MtrxArray						// 행렬 배열 클래스
{
public:
	MtrxArray(int array_size);		// 행렬 배열 생성자 
	~MtrxArray();					// 행렬 배열 소멸자
	Mtrx& operator[](int);			// 행렬 반환
	int ArraySize();				// 배열의 크기 반환

private:
	Mtrx* pMtrx;					// 행렬 배열 담는 포인터
	int mtrxArraySIZE;				// 배열의 크기
	bool isValidIndex(int index);	// 행렬 인덱스 번호 유효성 검사
};

#endif