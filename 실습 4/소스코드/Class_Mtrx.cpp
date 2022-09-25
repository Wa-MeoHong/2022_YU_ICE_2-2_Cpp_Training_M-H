#include "Class_Mtrx.h"
#include <iostream>
#include <iomanip>

using namespace std;

/*					��� ����� �����ε�
		1. ��� ������ << �����ε� ( ��� ��� ���� ���� )
		2. �Է� ������ >> �����ε� ( ��� �Է� ���� ���� )			*/
ostream& operator<<(ostream& output, const Mtrx& m)						// ��� ������ �����ε� ( ��� ���� ���� )
{
	const char a1 = 0xa1, a2 = 0xa2, a3 = 0xa3, a4 = 0xa4, a5 = 0xa5, a6 = 0xa6;
	//Ȯ���� �����ڵ� : ( �� : a6a1, �� : a6a2, �� : a6a3, �� : a6a4, �� : a6a5, �� : a6a6 )

	output << m.name << " = " << endl;
	for (int i = 0; i < m.n_row; i++)
	{
		for (int k = 0; k < m.n_col; k++)
		{

			// ���ȣ ��ºκ� ( ���� [ )
			if (i == 0 && k == 0)
				output << a6 << a3;										// ��
			else if (i > 0 && i < m.n_row - 1 && k == 0)
				output << a6 << a2;										// ��
			else if (i == m.n_row - 1 && k == 0)
				output << a6 << a6;										// ��

			output.setf(ios::fixed);  output.setf(ios::showpoint);
			output << setw(8); output.precision(2);
			output << m.dMtrx[i][k];						// ���� ��ºκ�


			// ���ȣ ��ºκ� ( ���� ] )
			if (i == 0 && k == m.n_col - 1)
				output << a6 << a4;										// ��
			else if (i > 0 && i < m.n_row - 1 && k == m.n_col - 1)
				output << a6 << a2;										// ��
			else if (i == m.n_row - 1 && k == m.n_col - 1)
				output << a6 << a5;										// ��
		}
		output << endl;
	}

	return output;
}
istream& operator>>(istream& input, Mtrx& m)						// �Է� ������ �����ε� ( �Է� ���� ���� )
{
	input >> m.n_row >> m.n_col;									// �Է��� ���� ( ��, �� ���� ) 
	m.init(m.row(), m.col());										// �Է¹��� �� �� �����ͷ� �ʱⰪ ����

	for (int i = 0; i < m.row(); i++)
	{
		for (int j = 0; j < m.col(); j++)
			input >> m.dMtrx[i][j];
	}
	return input;
}

/*					��� ������, �Ҹ���
		1. ��� ������ 1 ( �ƹ��� �����Ͱ� ���� �� )
		2. ��� ������ 2 ( �̸�, ��, ���� ������ ��)
		3. ��� ������ 3 ( �̸�, ��, ��, ��� �����Ͱ� ��� ������ ��)
		4. ��� �ґl�� ( �Լ��� ������ ���� �Ҹ��� �̷���� ��)			*/
Mtrx::Mtrx()													// constructor ( ������ ) 1, �ƹ��͵� ������ 
{
	n_col = 0;
	n_row = 0;
	name = " ";
	dMtrx = NULL;
}
Mtrx::Mtrx(string nm, int num_row, int num_col)							// ������ 2, ��, ��, �̸��� ���� ��
	: n_row(num_row), n_col(num_col), name(nm)
{
	init(n_row, n_col);
}
Mtrx::Mtrx(string nm, double* pA, int num_row, int num_col)			// ������3 , ��, ��, �̸�, �����Ͱ� ��� ������
	: n_row(num_row), n_col(num_col), name(nm)						// ���� �̸�, ��, ���� ���� ���Խ��ѹ����� ����
{
	init(n_row, n_col);												// �ʱ�ȭ�� ��� Ŭ���� ��ü�� ����� �����Ҵ�
	for (int j = 0; j < n_row; j++)
	{
		for (int k = 0; k < n_col; k++)
			dMtrx[j][k] = pA[j * num_row + k];						// ��Ŀ�  pA ������ ����
	}
}
Mtrx::~Mtrx()									// destructor ( �Ҹ��� ) 
{
	//for (int i = 0; i < n_row; i++)
	//{
	//	delete[] dMtrx[i];						// delete �����ڸ� ���� �����Ҵ��� �迭�� ����
	//}
	//delete[] dMtrx;							// ���ѹ� delete�� ���� �����Ҵ� ����
}

/*						������ �����ε�
		1. init() ( �ʱ�ȭ�� ��Ŀ� ���� �޾Ƽ� ������ )
		2. + �����ε� ( ��� ���� )
		3. - �����ε� ( ��� �E�� )
		4. * �����ε� ( ��� ���� )
		5. ~ �����ε� ( ��ġ��� )
		6. = �����ε� ( ��� ���� )
		6. == �����ε� ( ��� ��ġ�ϴ��� �� )
		6. != �����ε� ( ��� �ٸ��� �� )					*/
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
const Mtrx Mtrx::operator+(const Mtrx& mM)						// ���� ������ �����ε�
{
	Mtrx mR;

	mR.init(this->row(), this->col());
	mR.NameSetting("Add Mtrx");									// �̸� ����

	for (int i = 0; i < this->row(); i++)								// ��� ���� ����
	{
		for (int j = 0; j < this->col(); j++)
			mR.dMtrx[i][j] = this->dMtrx[i][j] + mM.dMtrx[i][j];
	}

	return mR;
}
const Mtrx Mtrx::operator-(const Mtrx& mM)						// ���� ������ �����ε�
{
	Mtrx mR;													// ��� ��� ����
	mR.init(this->row(), this->col());
	mR.NameSetting("Sub Mtrx");									// �̸� ����

	for (int i = 0; i < this->row(); i++)
	{
		for (int j = 0; j < this->col(); j++)
			mR.dMtrx[i][j] = this->dMtrx[i][j] - mM.dMtrx[i][j];		// ��� ���� ����
	}

	return mR;
}
const Mtrx Mtrx::operator*(const Mtrx& mM)						// ���� ������ �����ε�
{
	int row_SIZE, col_SIZE, SIZE_k;
	row_SIZE = this->row(); col_SIZE = mM.col(); SIZE_k = mM.row();	// ����� ��� ����� ��, �������� 

	Mtrx mR;													// ��, �� �����͸� ������ ��� ����
	mR.init(row_SIZE, col_SIZE);
	mR.NameSetting("Mul Mtrx");									// �̸� ����

	for (int i = 0; i < row_SIZE; i++)							// �� ��ȯ
	{
		for (int j = 0; j < col_SIZE; j++)						// �� ��ȯ
		{
			for (int k = 0; k < SIZE_k; k++)					// �μ��� ���Ѱ͵� �����ϱ�
			{
				mR.dMtrx[i][j] += this->dMtrx[i][k] * mM.dMtrx[k][j];
			}
		}
	}

	return mR;
}
const Mtrx Mtrx::operator~()									// ~ ������ �����ε� (��ġ���)
{
	Mtrx mT;													// ��ġ��Ŀ� ��� ����
	mT.init(this->col(), this->row());							// ��� ���� �ٲ�
	mT.NameSetting("Transpose Matrix");

	for (int i = 0; i < this->col(); i++)
	{
		for (int j = 0; j < this->row(); j++)
			mT.dMtrx[i][j] = this->dMtrx[j][i];					// ��� ���� �ٸ����ؼ� ����
	}
	return mT;
}
const Mtrx& Mtrx::operator=(const Mtrx& mM)						// ���� ������ �����ε�
{
	init(mM.row(), mM.col());									// �ʱⰪ ����

	for (int i = 0; i < mM.row(); i++)
		for (int j = 0; j < mM.col(); j++)
			this->dMtrx[i][j] = mM.dMtrx[i][j];					// ��� ����

	return *this;												// ������ ��ȯ
}
bool Mtrx::operator==(const Mtrx& mM)							// ����� ��ġ�ϴ��� ���
{
	int equalcount = 0;											// ��ĳ��� ��� �����Ͱ� ��ġ�ؾ��ϹǷ� ī��Ʈ�� ����

	if (this->n_row == mM.n_row && this->n_col == mM.n_col)		// ��, ���� ��ġ�ϴٸ�
	{
		for (int i = 0; i < n_row; i++)
		{
			for (int j = 0; j < n_col; j++)
			{
				if (this->dMtrx[i][j] == mM.dMtrx[i][j])		// ��� �����͸� �ϳ��ϳ� ��� ������ ������ Ȯ���Ѵ�.
					equalcount++;								// ������ equalcount�� �ϳ��� ���Ѵ�.
			}
		}
		if (equalcount == n_row * n_col)						// ���� equalcount�� ����� �������� ������ ���ٸ� ���� ��ġ
			return true;
		else
			return false;										// �ƴϸ� false
	}
	else
		return false;											// ��� ���� ���� �ʾƵ� false
}
bool Mtrx::operator!=(const Mtrx& mM)
{
	int equalcount = 0;

	if (this->n_row != mM.n_row || this->n_col != mM.n_col)		// ��� ���� ���� �ʴٸ� true
		return true;
	else
	{															// ���� ���ٸ� 
		for (int i = 0; i < n_row; i++)
		{
			for (int j = 0; j < n_col; j++)
			{
				if (this->dMtrx[i][j] == mM.dMtrx[i][j])		// ��� ���� �����Ͱ� ������ ī��Ʈ�� ����
					equalcount++;
			}
		}
		if (equalcount != n_row * n_col)						// equalcount�� ��� ������ ������ �ƴ϶�� true(��� ���� ����)
			return true;
		else
			return false;										// �ƴϸ� false (��ΰ���)
	}

}
