#ifndef CLASS_MTRX_H
#define CLASS_MTRX_H
#pragma warning(disable: 4996)					// 오류 안뜨게 하는 pragma정의

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class MtrxArray;

class Mtrx {
	friend ostream& operator<< (ostream&, const Mtrx&);
	friend istream& operator>> (istream&, Mtrx&);
	friend class MtrxArray;

public:
	Mtrx();											// constructor (생성자)
	Mtrx(string nm, int n_row, int n_col);
	Mtrx(string nm, double* pA, int n_row, int n_col);
	~Mtrx();										// distructor (소멸자)
	void init(int num_row, int num_col);
	void NameSetting(string nm) { name = nm; };
	string Name() const { return name; }
	int row() const { return n_row; }
	int col() const { return n_col; }
	const Mtrx operator+(const Mtrx&);				// 행렬 덧셈
	const Mtrx operator-(const Mtrx&);				// 행렬 뺄셈
	const Mtrx operator*(const Mtrx&);				// 행렬 곱셈
	const Mtrx operator~();							// 전치 행렬 
	const Mtrx& operator=(const Mtrx&);
	bool operator==(const Mtrx&);					// 행렬이 같은지 확인
	bool operator!=(const Mtrx&);					// 행렬이 다른지 확인

private:
	string name;
	int n_row;
	int n_col;
	double** dMtrx = NULL;									// 행렬 변수 dMtrx
};


#endif // !CLASS_MTRX_H