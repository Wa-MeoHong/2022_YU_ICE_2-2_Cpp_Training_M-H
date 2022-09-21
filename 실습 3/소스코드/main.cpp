/*
  파일명 : "실습3_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- Class Mtrx (행렬 클래스)를 만들어 출력을 하는 프로그램
  프로그램 작성자 : 신대홍(2022년 9월 21일)
  최종 Update : Version 1.0.1, 2022년 9월 22일 (신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
   신대홍		 2022/09/21		v1.0.0		  최초작성
   신대홍		 2022/09/22		v1.0.1		  완성

===========================================================================================================
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Mtrx.h"

#define INPUT "Matrix_data.txt"				// 입력파일 "Matrix_date.txt"
#define OUTPUT "output.txt"					// 출력파일 "output.txt"
using namespace std;

int main(void)
{
	ifstream fin;							// 입력용 파일
	ofstream fout;							// 출력용 파일

	// 파일 오픈 후, 오류가 생기면 즉시 종료
	fin.open(INPUT); fout.open(OUTPUT);
	if (fin.fail())
	{
		cout << "Error in opening Matrix_data.txt!!" << endl; exit;
	}
	if (fout.fail())
	{
		cout << "Error in opening output.txt!!" << endl; exit;
	}

	Mtrx mtrxA(fin);						// 행렬 A 생성
	mtrxA.NameSetting("mtrxA");				// 이름 세팅
	mtrxA.fprintMtrx(fout);					// 출력

	// 행렬 B 생성 및 출력
	Mtrx mtrxB(fin);
	mtrxB.NameSetting("mtrxB");
	mtrxB.fprintMtrx(fout);

	// 행렬 C 생성 및 출력
	Mtrx mtrxC(fin);
	mtrxC.NameSetting("mtrxC");
	mtrxC.fprintMtrx(fout);

	// 행렬 D ( 행렬 A + 행렬 B ) 생성 및 출력
	Mtrx mtrxD(mtrxA.row(), mtrxB.col());
	mtrxD = mtrxA.addMtrx(mtrxB);
	mtrxD.NameSetting("mtrxD = mtrxA.add(mtrxB)");
	mtrxD.fprintMtrx(fout);

	// 행렬 E ( 행렬 A - 행렬 B ) 생성 및 출력
	Mtrx mtrxE(mtrxA.row(), mtrxB.col());
	mtrxE = mtrxA.subMtrx(mtrxB);
	mtrxE.NameSetting("mtrxE = mtrxA.sub(mtrxB)");
	mtrxE.fprintMtrx(fout);

	// 행렬 F ( 행렬 A * 행렬 C ) 생성 및 출력
	Mtrx mtrxF(mtrxA.row(), mtrxC.col());
	mtrxF = mtrxA.mulMtrx(mtrxC);
	mtrxF.NameSetting("mtrxF = mtrxA.multiply(mtrxC)");
	mtrxF.fprintMtrx(fout);

	// 행렬 G ( 행렬 A 전치행렬) 생성 및 출력
	Mtrx mtrxG(mtrxA.row(), mtrxA.col());
	mtrxG = mtrxA.transposeMtrx();
	mtrxG.NameSetting("mtrxG = mtrxA.transposeMtrx()");
	mtrxG.fprintMtrx(fout);

	// 파일 닫기
	fin.close();
	fout.close();
}