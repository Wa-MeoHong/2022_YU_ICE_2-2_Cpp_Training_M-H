/*
  파일명 : "실습4_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- Class Mtrx (행렬 클래스)를 만들고 연산자 오버로드를 이용해 계산을 하는 프로그램
  프로그램 작성자 : 신대홍(2022년 9월 26일)
  최종 Update : Version 1.0.0, 2022년 9월 26일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/09/26		v1.0.0		  최초작성

===========================================================================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Class_Mtrx.h"							// 행렬 클래스 헤더
#include "MtrxArray.h"						// 행렬 배열 클래스 헤더

using namespace std;

#define NUM_MTRX 8							// 만들 배열 개수
#define INPUT "Matrix_data.txt"				// 입력파일 "Matrix_date.txt"
#define OUTPUT "Result.txt"					// 출력파일 "Result.txt"


int main(void)
{
	ifstream fin;
	ofstream fout;

	fin.open(INPUT);						// 입력 파일 오픈
	if (fin.fail())	{
		cout << "Error! Matrix_data.txt doesn't open!!" << endl; exit(0);
	}
	fout.open(OUTPUT);						// 출력 파일 오픈
	if (fout.fail()) {
		cout << "Error! Result.txt doesn't open!!" << endl; exit(0);
	}
	MtrxArray mtrx(NUM_MTRX);				// 배열 만들기

	// 행렬 0, 행렬 1, 행렬 2 파일에서 입력 받음
	fin >> mtrx[0] >> mtrx[1] >> mtrx[2];
	// 입력받은 후, 이름 세팅
	mtrx[0].NameSetting("Mtrx[0] = ");
	mtrx[1].NameSetting("Mtrx[1] = ");
	mtrx[2].NameSetting("Mtrx[2] = ");

	// 행렬 0, 1, 2 파일에 출력
	fout << mtrx[0] << endl;
	fout << mtrx[1] << endl;
	fout << mtrx[2] << endl;
	cout << "Matrix data (Mtrx[0], Mtrx[1], Mtrx[2]) print complete! " << endl;

	// 행렬 덧셈 후 출력
	mtrx[3] = mtrx[0] + mtrx[1];
	mtrx[3].NameSetting("Mtrx[3] = Mtrx[0] + Mtrx[1] = ");
	fout << mtrx[3] << endl;
	cout << "Add Matrix print complete! " << endl;

	// 행렬 뺼셈 후 출력
	mtrx[4] = mtrx[0] - mtrx[1];
	mtrx[4].NameSetting("Mtrx[4] = Mtrx[0] - Mtrx[1] = ");
	fout << mtrx[4] << endl;
	cout << "Substract Matrix print complete! " << endl;

	// 행렬 곱셈 후 출력
	mtrx[5] = mtrx[0] * mtrx[2];
	mtrx[5].NameSetting("Mtrx[5] = Mtrx[0] * Mtrx[2] = ");
	fout << mtrx[5] << endl;
	cout << "Multiple Matrix print complete! " << endl;

	// 행렬 6은 행렬 5의 전치행렬
	mtrx[6] = ~mtrx[5];
	mtrx[6].NameSetting("Mtrx[6] = ~Mtrx[5] = ");
	fout << mtrx[6] << endl;
	cout << "Transpose Matrix print complete! " << endl;

	// 행렬 7 == 행렬 0, 행렬 0를 대입
	mtrx[7] = mtrx[0];
	mtrx[7].NameSetting("Mtrx[7] = Mtrx[0] = ");
	fout << mtrx[7] << endl;
	cout << "Substitute Matrix print complete! " << endl;

	// 행렬 0와 행렬 7이 같은지 다른지 비교
	if (mtrx[0] == mtrx[7])
		fout << "Mtrx[0] and Mtrx[7] are equal." << endl;
	if (mtrx[5] != mtrx[6])
		fout << "Mtrx[5] and Mtrx[6] are not equal." << endl;

	// 파일 닫기
	fin.close();
	fout.close();

	return 0;
}
