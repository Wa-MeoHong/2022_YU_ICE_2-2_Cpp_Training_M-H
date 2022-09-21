#include "Mtrx.h"

#define MAX(x, y) ((x) > (y)) ? (x) : (y)					// 최대값 찾기 매크로함수
#define MIN(x, y) ((x) < (y)) ? (x) : (y)					// 최소값 찾기 매크로함수
#define Epsilon 0.000001


/*				constructor (생성자)
	1. 열(num_row), 행(num_col)을 알고있는 상태에서 만드는 행렬( 데이터는 0.0으로 초기화 )
	2. 열과 행, 데이터를 모두 파일에서 받아와서 만드는 행렬
															*/
Mtrx::Mtrx(int num_row, int num_col)						
{
	n_row = num_row;						// 열 대입
	n_col = num_col;						// 행 대입
	dMtrx = new double*[n_row];				// new 연산자를 통해 double* 형의 배열 생성 ( 원소개수가 n_row개 만큼 )
	for (int i = 0; i < n_row; i++)			// new 연산자를 통해 double 형의 배열 생성 ( 배열당 n_col개 만큼)
	{
		dMtrx[i] = new double[n_col];
	}

	for (int j = 0; j < n_row; j++)			// 값을 대입함 ( 0.0으로 )
	{
		for (int k = 0; k < n_col; k++)
		{
			dMtrx[j][k] = 0.0;
		}
	}

}
Mtrx::Mtrx(ifstream& fin)
{
	fin >> n_row >> n_col;					// 열과 행의 데이터를 파일에서 읽어옴

	dMtrx = new double* [n_row];			// new 연산자를 통해 double* 형의 배열 생성 ( 원소개수가 n_row개 만큼 )
	for (int i = 0; i < n_row; i++)			// new 연산자를 통해 double 형의 배열 생성 ( 배열당 n_col개 만큼)
	{
		dMtrx[i] = new double[n_col];
	}

	for (int j = 0; j < n_row; j++)			// 파일로부터 데이터를 읽어옴
	{
		for (int k = 0; k < n_col; k++)
		{
			if (fin.eof())
				dMtrx[j][k] = 0.0;			// 만약 파일에서 데이터를 모두 읽었으나 초기값 설정이 안끝났다면 0.0으로 
			else {
				fin >> dMtrx[j][k];			// 파일애서 데이터를 읽어와 배열에 저장
			}
		}
	}
}

/*				 distructor (소멸자)					*/
Mtrx::~Mtrx()
{
	//for (int i = 0; i < n_row; i++)
	//{
	//	delete[] dMtrx[i];						// delete 연산자를 통해 동적할당한 배열을 해제
	//}
	//delete[] dMtrx;							// 또한번 delete를 통한 동적할당 해제
}

/*				 행렬 연산 관련 멤버					
	1. 행렬 덧셈 ( 다른 배열 하나를 const 변수로 들고와 계산) 
	2. 행렬 뺄셈 ( 다른 배열 하나를 const 변수로 들고와 계산) 
	3. 행렬 곱셈 ( 다른 배열 하나를 const 변수로 들고와 계산) 
	4. 전치 행렬 ( 행렬을 원점대칭시킴 )
	5. 행렬 내의 최대, 최소값 계산
	6. 행렬 데이터 계산
	7. 가우스 조던 소거법을 통한 해를 산출하는 함수
	8. 역행렬 산출	
												*/
Mtrx Mtrx::addMtrx(const Mtrx& mM)								// 행렬 덧셈
{
	Mtrx mR(n_row, n_col);										// 결과 행렬 생성
	mR.NameSetting("Add Mtrx");									// 이름 지정

	for (int i = 0; i < n_row; i++)								// 행렬 덧셈 진행
	{
		for (int j = 0; j < n_col; j++)
			mR.dMtrx[i][j] = dMtrx[i][j] + mM.dMtrx[i][j];
	}

	return mR;													// 행렬 반환
}
Mtrx Mtrx::subMtrx(const Mtrx& mM)								// 행렬 뺄셈
{
	Mtrx mR(n_row, n_col);										// 결과 행렬 생성
	mR.NameSetting("Sub Mtrx");

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
			mR.dMtrx[i][j] = dMtrx[i][j] - mM.dMtrx[i][j];
	}

	return mR;
}
Mtrx Mtrx::mulMtrx(const Mtrx& mM)							// 행렬 곱셈 함수
{
	int row_SIZE, col_SIZE, SIZE_k;

	row_SIZE = n_row; col_SIZE = mM.col(); SIZE_k = mM.row();	// 결과를 담는 행렬의 행, 열데이터 
	Mtrx mR(row_SIZE, col_SIZE);							// 행, 열 데이터를 가지고 행렬 생성
	mR.NameSetting("Mul Mtrx");								// 이름 설정

	for (int i = 0; i < row_SIZE; i++)						// 행 전환
	{
		for (int j = 0; j < col_SIZE; j++)					// 열 전환
		{
			for (int k = 0; k < SIZE_k; k++)				// 인수를 곱한것들 덧셈하기
			{
				mR.dMtrx[i][j] += dMtrx[i][k] * mM.dMtrx[k][j];
			}
		}
	}

	return mR;
}
Mtrx Mtrx::transposeMtrx()									// 전치행렬 (중심을 기준으로 원점대칭된 행렬)
{
	Mtrx mT(n_col, n_row);									// 결과값을 담는 행렬 생성
	mT.NameSetting("Transpose Matrix");

	for (int i = 0; i < n_col; i++)							// 전치행렬은 i,j가 반대가 되어 담긴다.
	{
		for (int j = 0; j < n_row; j++)
			mT.dMtrx[i][j] = dMtrx[j][i];
	}
	return mT;												// 반환
}		
double Mtrx::MaxMtrx() const								// const를 멤버함수 바로 뒤에 붙여, 클래스 데이터의 값을 변경하지 않음을 나타냄.
															// 또한 const로 선언된 클래스 객체가 사용가능함.
{
	double max = 0; 
	
	max = dMtrx[0][0];

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
			max = MAX(max, dMtrx[i][j]);					// 행렬 데이터중 가장 큰값을 찾아 max에 대입한다.(매크로 함수 사용)
	}

	return max;												// 최대값 반환
}
double Mtrx::MinMtrx() const
{
	double min = 0;

	min = dMtrx[0][0];

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
			min = MIN(min, dMtrx[i][j]);					// 행렬 데이터중 가장 최소값을 찾는다.
	}

	return min;												// 반환
}
void Mtrx::StaticDate(ofstream& fout, const Mtrx& mM)		// 행렬 데이터 계산
{
	double sum = 0, avg = 0, dev2sum = 0, var = 0, std = 0;	// 각각 합, 평균, 편차제곱의 합, 분산, 표준편차
	int num_M = mM.row() * mM.col();						// 총 행렬 데이터 개수

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
			sum += dMtrx[i][j];								// 합 계산
	}
	avg = sum / num_M;										// 평균 계산

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
			dev2sum += pow(dMtrx[i][j] - avg, 2);			// 편차 제곱의 합 계산
	}
	var = dev2sum / num_M;									// 편차제곱의 합의 평균
	std = sqrt(var);										// 분산의 제곱근 = 표준편차

	//출력
	fout << "Mtrx (" << mM.Name() << ")'s StaticsData :" << endl;
	fout << "Max : " << mM.MaxMtrx() << ", Min : " << mM.MinMtrx() << ", Average : " <<
		avg << ", Variance : " << var << ", Std : " << std << endl;
}

Mtrx Mtrx::InvMtrx(int* solexist) const						// 역행렬
{
	Mtrx InverseMtrx(n_row, n_col);
	Mtrx AugMtrx(n_row, n_col * 2);
	double pivDivide, anotherDiv;


	for (int j = 0; j < n_row; j++)			// 값을 대입함 ( 구할 행렬의 값으로 )
	{
		for (int k = 0; k < n_col; k++)
			AugMtrx.dMtrx[j][k] = dMtrx[j][k];
	}

	for (int j = 0; j < n_row; j++)			// 값을 대입함 ( 단위 행렬 I으로 )
	{
		for (int k = n_col; k < n_col * 2; k++)
			AugMtrx.dMtrx[j][k] = (j == k - n_col) ? 1.0 : 0.0;
	}

	for (int p = 0; p < n_col; p++)
	{
		double max = fabs(AugMtrx.dMtrx[p][p]);
		//기준 행, 열 절댓값 (1번째행,열 값, 2번째행, 열값, 3번째행,열 값)
		// abs() = int형의 절댓값 반환, fabs() = double 형의 절댓값 반환

		for (int i = 0; i < n_row; i++)
		{
			max = MAX(max, fabs(AugMtrx.dMtrx[i][p]));		// 행 p열의 각 행들에 대해 p열에서의 최대값을 갱신
		}

		if (max < Epsilon)									// 만약 max == 0이라면 
			*solexist = 0;									// 해를 구할 수 없는 상태라고 하고, solExist를 0으로 만들어줌
		else
			*solexist = 1;									// 아니면 solExist를 1로 만든 후, 
		//=================================해가 유무 판별 과정===================================

		if (*solexist == 0)									// 역행렬을 구할수 없기 때문에 종료
			break;

		if (AugMtrx.dMtrx[p][p] != 1.00)							// p,p의 값이 1이 아닌경우 (1이면 이 과정을 따로 안거침)
		{
			pivDivide = AugMtrx.dMtrx[p][p];
			AugMtrx.dMtrx[p][p] = 1.00;
			for (int k = p + 1; k < n_col * 2; k++)		// 역행렬 때문에 배열이 오른쪽으로 SIZE_N의 두배가 됨...
				AugMtrx.dMtrx[p][k] /= pivDivide;					// p,p의 값이 1이 되도록 행의 모든 값을 p,p의 값에 나눔
		}

		for (int j = 0; j < n_row; j++)
		{
			if ((j != p) && (AugMtrx.dMtrx[j][p] != 0.0))
				// p행을 제외한 나머지 행, 또한, j행의 p열의 값이 0(정리가 끝난상태)가 아닌 경우라면 진행
			{
				anotherDiv = AugMtrx.dMtrx[j][p];
				AugMtrx.dMtrx[j][p] = 0;
				for (int k = p + 1; k < n_col * 2; k++)	// 모든 행의 값을 기준행에 맞춰 다 빼줌 (즉, p,p번째의 값(1.0)빼고는 전부 0으로 만들어줌
					AugMtrx.dMtrx[j][k] = AugMtrx.dMtrx[j][k] - (anotherDiv * AugMtrx.dMtrx[p][k]);
			}
		}
	}

	for (int i = 0; i < n_row; i++)
		for (int j = 0; j < n_col; j++)
			InverseMtrx.dMtrx[i][j] = AugMtrx.dMtrx[i][j + n_col];

	
	return InverseMtrx;
}

/*					행렬 출력 함수					*/		
void Mtrx::fprintMtrx(ofstream& fout)						// 파일 출력함수
{
	const char a1 = 0xa1, a2 = 0xa2, a3 = 0xa3, a4 = 0xa4, a5 = 0xa5, a6 = 0xa6;
	//확장형 문자코드 : ( ─ : a6a1, │ : a6a2, ┌ : a6a3, ┐ : a6a4, ┘ : a6a5, └ : a6a6 )
	
	fout << name << " = " << endl;
	for (int i = 0; i < n_row; i++)
	{
		for (int k = 0; k < n_col; k++)
		{
			
			// 대괄호 출력부분 ( 앞줄 [ )
			if (i == 0 && k == 0)
				fout << a6 << a3;										// ┌
			else if (i > 0 && i < n_row - 1 && k == 0)
				fout << a6 << a2;										// │
			else if (i == n_row - 1 && k == 0)
				fout << a6 << a6;										// └

			fout.setf(ios::fixed);  fout.setf(ios::showpoint);
			fout << setw(9); fout.precision(2);
			fout << dMtrx[i][k];						// 숫자 출력부분
			

			// 대괄호 출력부분 ( 뒷줄 ] )
			if (i == 0 && k == n_col - 1)
				fout << a6 << a4;										// ┐
			else if (i > 0 && i < n_row - 1 && k == n_col - 1)
				fout << a6 << a2;										// │
			else if (i ==  n_row - 1 && k == n_col - 1)
				fout << a6 << a5;										// ┘
		}
		fout << endl;
	}
	fout << endl;

}
