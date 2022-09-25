#include "MtrxArray.h"
#include "CLass_Mtrx.h"


MtrxArray::MtrxArray(int array_size)						// 행렬 배열 초기 설정 
{
	mtrxArraySIZE = array_size;								// 배열의 크기 
	pMtrx = new Mtrx[array_size];							// 동적할당
}

MtrxArray::~MtrxArray()										// 배열 소멸자
{
	if (pMtrx != NULL)
	{
		delete[] pMtrx;										// 배열 동적할당 해제
	}
}
void subError()												// 에러 출력 함수
{
	cout << "ERROR: Subscript out of range.\n";	exit(0);
}

Mtrx& MtrxArray::operator[](int sub)						// 배열 인덱스로 불러오는 연산자 [] 오버로드
{
	if (isValidIndex(sub))									// 배열 인덱스 번호가 유효한지 확인
		return pMtrx[sub];									// 유효하면 배열의 인덱스에 해당되는 데이터 반환
	else
		subError();											// 아니면 에러 메세지 후 종료
}

int MtrxArray::ArraySize()									// 배열의 크기 반환
{
	return mtrxArraySIZE;	
}

bool MtrxArray::isValidIndex(int index)						// 배열 인덱스 유효성 검사
{
	if (index < 0 || index >= this->ArraySize())				// 배열인덱스 번호가 0부터 SIZE-1사이에 있는 숫자인지
		return false;										// 아니면 false, 맞으면 true
	else
		return true;
}
