#include "Class_Mtrx.h"
#include <iostream>
#include <iomanip>

using namespace std;

/*					행렬 입출력 오버로딩
		1. 출력 연산자 << 오버로드 ( 행렬 출력 포맷 지정 )
		2. 입력 연산자 >> 오버로드 ( 행렬 입력 포맷 지정 )			*/
ostream& operator<<(ostream& output, const Mtrx& m)						// 출력 연산자 오버로드 ( 출력 포맷 지정 )
{
	const char a1 = 0xa1, a2 = 0xa2, a3 = 0xa3, a4 = 0xa4, a5 = 0xa5, a6 = 0xa6;
	//확장형 문자코드 : ( ─ : a6a1, │ : a6a2, ┌ : a6a3, ┐ : a6a4, ┘ : a6a5, └ : a6a6 )

	output << m.name << " = " << endl;
	for (int i = 0; i < m.n_row; i++)
	{
		for (int k = 0; k < m.n_col; k++)
		{

			// 대괄호 출력부분 ( 앞줄 [ )
			if (i == 0 && k == 0)
				output << a6 << a3;										// ┌
			else if (i > 0 && i < m.n_row - 1 && k == 0)
				output << a6 << a2;										// │
			else if (i == m.n_row - 1 && k == 0)
				output << a6 << a6;										// └

			output.setf(ios::fixed);  output.setf(ios::showpoint);
			output << setw(8); output.precision(2);
			output << m.dMtrx[i][k];						// 숫자 출력부분


			// 대괄호 출력부분 ( 뒷줄 ] )
			if (i == 0 && k == m.n_col - 1)
				output << a6 << a4;										// ┐
			else if (i > 0 && i < m.n_row - 1 && k == m.n_col - 1)
				output << a6 << a2;										// │
			else if (i == m.n_row - 1 && k == m.n_col - 1)
				output << a6 << a5;										// ┘
		}
		output << endl;
	}

	return output;
}
istream& operator>>(istream& input, Mtrx& m)						// 입력 연산자 오버로드 ( 입력 포맷 지정 )
{
	input >> m.n_row >> m.n_col;									// 입력을 받음 ( 열, 행 순서 ) 
	m.init(m.row(), m.col());										// 입력받은 행 열 데이터로 초기값 생성

	for (int i = 0; i < m.row(); i++)
	{
		for (int j = 0; j < m.col(); j++)
			input >> m.dMtrx[i][j];
	}
	return input;
}

/*					행렬 생성자, 소멸자
		1. 행렬 생성자 1 ( 아무런 데이터가 없을 시 )
		2. 행렬 생성자 2 ( 이름, 행, 열만 존재할 시)
		3. 행렬 생성자 3 ( 이름, 행, 열, 행렬 데이터가 모두 존재할 시)
		4. 행렬 소멿자 ( 함수가 끝나는 등의 소멸이 이루어질 때)			*/
Mtrx::Mtrx()													// constructor ( 생성자 ) 1, 아무것도 없을때 
{
	n_col = 0;
	n_row = 0;
	name = " ";
	dMtrx = NULL;
}
Mtrx::Mtrx(string nm, int num_row, int num_col)							// 생성자 2, 행, 열, 이름만 있을 떄
	: n_row(num_row), n_col(num_col), name(nm)
{
	init(n_row, n_col);
}
Mtrx::Mtrx(string nm, double* pA, int num_row, int num_col)			// 생성자3 , 행, 열, 이름, 데이터가 모두 있을때
	: n_row(num_row), n_col(num_col), name(nm)						// 먼저 이름, 행, 열은 전부 대입시켜버리고 시작
{
	init(n_row, n_col);												// 초기화된 행렬 클래스 객체에 행렬을 동적할당
	for (int j = 0; j < n_row; j++)
	{
		for (int k = 0; k < n_col; k++)
			dMtrx[j][k] = pA[j * num_row + k];						// 행렬에  pA 데이터 대입
	}
}
Mtrx::~Mtrx()									// destructor ( 소멸자 ) 
{
	//for (int i = 0; i < n_row; i++)
	//{
	//	delete[] dMtrx[i];						// delete 연산자를 통해 동적할당한 배열을 해제
	//}
	//delete[] dMtrx;							// 또한번 delete를 통한 동적할당 해제
}

/*						연산자 오버로드
		1. init() ( 초기화된 행렬에 값을 받아서 생성함 )
		2. + 오버로드 ( 행렬 덧셈 )
		3. - 오버로드 ( 행렬 뺼셈 )
		4. * 오버로드 ( 행렬 곱셈 )
		5. ~ 오버로드 ( 전치행렬 )
		6. = 오버로드 ( 행렬 대입 )
		6. == 오버로드 ( 행렬 일치하는지 비교 )
		6. != 오버로드 ( 행렬 다른지 비교 )					*/
void Mtrx::init(int num_row, int num_col)
{
	n_row = num_row; n_col = num_col;
	dMtrx = new double* [num_row];
	for (int i = 0; i < num_row; i++)
		dMtrx[i] = new double[num_col];

	for (int j = 0; j < n_row; j++)
	{
		for (int k = 0; k < n_col; k++)
			dMtrx[j][k] = 0.0;
	}
}
const Mtrx Mtrx::operator+(const Mtrx& mM)						// 덧셈 연산자 오버로드
{
	Mtrx mR;

	mR.init(this->row(), this->col());
	mR.NameSetting("Add Mtrx");									// 이름 지정

	for (int i = 0; i < this->row(); i++)								// 행렬 덧셈 진행
	{
		for (int j = 0; j < this->col(); j++)
			mR.dMtrx[i][j] = this->dMtrx[i][j] + mM.dMtrx[i][j];
	}

	return mR;
}
const Mtrx Mtrx::operator-(const Mtrx& mM)						// 뺄셈 연산자 오버로드
{
	Mtrx mR;													// 결과 행렬 생성
	mR.init(this->row(), this->col());
	mR.NameSetting("Sub Mtrx");									// 이름 지정

	for (int i = 0; i < this->row(); i++)
	{
		for (int j = 0; j < this->col(); j++)
			mR.dMtrx[i][j] = this->dMtrx[i][j] - mM.dMtrx[i][j];		// 행렬 뺄셈 진행
	}

	return mR;
}
const Mtrx Mtrx::operator*(const Mtrx& mM)						// 곱셈 연산자 오버로드
{
	int row_SIZE, col_SIZE, SIZE_k;
	row_SIZE = this->row(); col_SIZE = mM.col(); SIZE_k = mM.row();	// 결과를 담는 행렬의 행, 열데이터 

	Mtrx mR;													// 행, 열 데이터를 가지고 행렬 생성
	mR.init(row_SIZE, col_SIZE);
	mR.NameSetting("Mul Mtrx");									// 이름 설정

	for (int i = 0; i < row_SIZE; i++)							// 행 전환
	{
		for (int j = 0; j < col_SIZE; j++)						// 열 전환
		{
			for (int k = 0; k < SIZE_k; k++)					// 인수를 곱한것들 덧셈하기
			{
				mR.dMtrx[i][j] += this->dMtrx[i][k] * mM.dMtrx[k][j];
			}
		}
	}

	return mR;
}
const Mtrx Mtrx::operator~()									// ~ 연산자 오버로드 (전치행렬)
{
	Mtrx mT;													// 전치행렬용 행렬 생성
	mT.init(this->col(), this->row());							// 행과 열이 바뀜
	mT.NameSetting("Transpose Matrix");

	for (int i = 0; i < this->col(); i++)
	{
		for (int j = 0; j < this->row(); j++)
			mT.dMtrx[i][j] = this->dMtrx[j][i];					// 행과 열을 다르게해서 넣음
	}
	return mT;
}
const Mtrx& Mtrx::operator=(const Mtrx& mM)						// 대입 연산자 오버로드
{
	init(mM.row(), mM.col());									// 초기값 설정

	for (int i = 0; i < mM.row(); i++)
		for (int j = 0; j < mM.col(); j++)
			this->dMtrx[i][j] = mM.dMtrx[i][j];					// 행렬 대입

	return *this;												// 본인을 반환
}
bool Mtrx::operator==(const Mtrx& mM)							// 행렬이 일치하는지 계산
{
	int equalcount = 0;											// 행렬내의 모든 데이터가 일치해야하므로 카운트를 센다

	if (this->n_row == mM.n_row && this->n_col == mM.n_col)		// 행, 열이 일치하다면
	{
		for (int i = 0; i < n_row; i++)
		{
			for (int j = 0; j < n_col; j++)
			{
				if (this->dMtrx[i][j] == mM.dMtrx[i][j])		// 행렬 데이터를 하나하나 모두 대조해 같은지 확인한다.
					equalcount++;								// 같으면 equalcount를 하나씩 업한다.
			}
		}
		if (equalcount == n_row * n_col)						// 만약 equalcount가 행렬의 데이터의 갯수와 같다면 완전 일치
			return true;
		else
			return false;										// 아니면 false
	}
	else
		return false;											// 행과 열이 같지 않아도 false
}
bool Mtrx::operator!=(const Mtrx& mM)
{
	int equalcount = 0;

	if (this->n_row != mM.n_row || this->n_col != mM.n_col)		// 행과 열이 같지 않다면 true
		return true;
	else
	{															// 만약 같다면 
		for (int i = 0; i < n_row; i++)
		{
			for (int j = 0; j < n_col; j++)
			{
				if (this->dMtrx[i][j] == mM.dMtrx[i][j])		// 행렬 내의 데이터가 같은지 카운트를 센다
					equalcount++;
			}
		}
		if (equalcount != n_row * n_col)						// equalcount가 행렬 데이터 개수가 아니라면 true(모두 같지 않음)
			return true;
		else
			return false;										// 아니면 false (모두같음)
	}

}
