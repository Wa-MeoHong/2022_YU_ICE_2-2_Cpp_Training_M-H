#ifndef MTRX_H
#define MTRX_H
#pragma warning(disable: 4996)					// 오류 안뜨게 하는 pragma정의

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define MAX_SIZE 100


class Mtrx {
public:
	Mtrx(int num_row, int num_col);					// constructor (생성자)
	Mtrx(ifstream& fin);					
	~Mtrx();										// distructor (소멸자)
	int row() const { return n_row; }
	int col() const { return n_col; }
	void NameSetting(string nm) { name = nm; };
	string Name() const { return name; }
	Mtrx addMtrx(const Mtrx&);						// 행렬 덧셈
	Mtrx subMtrx(const Mtrx&);						// 행렬 뺄셈
	Mtrx mulMtrx(const Mtrx&);						// 행렬 곱셈
	Mtrx transposeMtrx();							// 전치행렬 만들기
	double MaxMtrx() const;							// 행렬의 최댓값 구하기
	double MinMtrx() const;							// 행렬의 최소값 구하기
	void StaticDate(ofstream& fout, const Mtrx&);	// 행렬 데이터 계산
	Mtrx InvMtrx(int* solexist) const;				// 역행렬 산출
	void fprintMtrx(ofstream& fout);				// 행렬 파일 출력

private:
	string name;
	int n_row;
	int n_col;
	double** dMtrx;									// 행렬 변수 dMtrx
};


#endif // !MTRX_H


