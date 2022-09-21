#include "Mtrx.h"

#define MAX(x, y) ((x) > (y)) ? (x) : (y)					// �ִ밪 ã�� ��ũ���Լ�
#define MIN(x, y) ((x) < (y)) ? (x) : (y)					// �ּҰ� ã�� ��ũ���Լ�
#define Epsilon 0.000001


/*				constructor (������)
	1. ��(num_row), ��(num_col)�� �˰��ִ� ���¿��� ����� ���( �����ʹ� 0.0���� �ʱ�ȭ )
	2. ���� ��, �����͸� ��� ���Ͽ��� �޾ƿͼ� ����� ���
															*/
Mtrx::Mtrx(int num_row, int num_col)						
{
	n_row = num_row;						// �� ����
	n_col = num_col;						// �� ����
	dMtrx = new double*[n_row];				// new �����ڸ� ���� double* ���� �迭 ���� ( ���Ұ����� n_row�� ��ŭ )
	for (int i = 0; i < n_row; i++)			// new �����ڸ� ���� double ���� �迭 ���� ( �迭�� n_col�� ��ŭ)
	{
		dMtrx[i] = new double[n_col];
	}

	for (int j = 0; j < n_row; j++)			// ���� ������ ( 0.0���� )
	{
		for (int k = 0; k < n_col; k++)
		{
			dMtrx[j][k] = 0.0;
		}
	}

}
Mtrx::Mtrx(ifstream& fin)
{
	fin >> n_row >> n_col;					// ���� ���� �����͸� ���Ͽ��� �о��

	dMtrx = new double* [n_row];			// new �����ڸ� ���� double* ���� �迭 ���� ( ���Ұ����� n_row�� ��ŭ )
	for (int i = 0; i < n_row; i++)			// new �����ڸ� ���� double ���� �迭 ���� ( �迭�� n_col�� ��ŭ)
	{
		dMtrx[i] = new double[n_col];
	}

	for (int j = 0; j < n_row; j++)			// ���Ϸκ��� �����͸� �о��
	{
		for (int k = 0; k < n_col; k++)
		{
			if (fin.eof())
				dMtrx[j][k] = 0.0;			// ���� ���Ͽ��� �����͸� ��� �о����� �ʱⰪ ������ �ȳ����ٸ� 0.0���� 
			else {
				fin >> dMtrx[j][k];			// ���Ͼּ� �����͸� �о�� �迭�� ����
			}
		}
	}
}

/*				 distructor (�Ҹ���)					*/
Mtrx::~Mtrx()
{
	//for (int i = 0; i < n_row; i++)
	//{
	//	delete[] dMtrx[i];						// delete �����ڸ� ���� �����Ҵ��� �迭�� ����
	//}
	//delete[] dMtrx;							// ���ѹ� delete�� ���� �����Ҵ� ����
}

/*				 ��� ���� ���� ���					
	1. ��� ���� ( �ٸ� �迭 �ϳ��� const ������ ���� ���) 
	2. ��� ���� ( �ٸ� �迭 �ϳ��� const ������ ���� ���) 
	3. ��� ���� ( �ٸ� �迭 �ϳ��� const ������ ���� ���) 
	4. ��ġ ��� ( ����� ������Ī��Ŵ )
	5. ��� ���� �ִ�, �ּҰ� ���
	6. ��� ������ ���
	7. ���콺 ���� �ҰŹ��� ���� �ظ� �����ϴ� �Լ�
	8. ����� ����	
												*/
Mtrx Mtrx::addMtrx(const Mtrx& mM)								// ��� ����
{
	Mtrx mR(n_row, n_col);										// ��� ��� ����
	mR.NameSetting("Add Mtrx");									// �̸� ����

	for (int i = 0; i < n_row; i++)								// ��� ���� ����
	{
		for (int j = 0; j < n_col; j++)
			mR.dMtrx[i][j] = dMtrx[i][j] + mM.dMtrx[i][j];
	}

	return mR;													// ��� ��ȯ
}
Mtrx Mtrx::subMtrx(const Mtrx& mM)								// ��� ����
{
	Mtrx mR(n_row, n_col);										// ��� ��� ����
	mR.NameSetting("Sub Mtrx");

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
			mR.dMtrx[i][j] = dMtrx[i][j] - mM.dMtrx[i][j];
	}

	return mR;
}
Mtrx Mtrx::mulMtrx(const Mtrx& mM)							// ��� ���� �Լ�
{
	int row_SIZE, col_SIZE, SIZE_k;

	row_SIZE = n_row; col_SIZE = mM.col(); SIZE_k = mM.row();	// ����� ��� ����� ��, �������� 
	Mtrx mR(row_SIZE, col_SIZE);							// ��, �� �����͸� ������ ��� ����
	mR.NameSetting("Mul Mtrx");								// �̸� ����

	for (int i = 0; i < row_SIZE; i++)						// �� ��ȯ
	{
		for (int j = 0; j < col_SIZE; j++)					// �� ��ȯ
		{
			for (int k = 0; k < SIZE_k; k++)				// �μ��� ���Ѱ͵� �����ϱ�
			{
				mR.dMtrx[i][j] += dMtrx[i][k] * mM.dMtrx[k][j];
			}
		}
	}

	return mR;
}
Mtrx Mtrx::transposeMtrx()									// ��ġ��� (�߽��� �������� ������Ī�� ���)
{
	Mtrx mT(n_col, n_row);									// ������� ��� ��� ����
	mT.NameSetting("Transpose Matrix");

	for (int i = 0; i < n_col; i++)							// ��ġ����� i,j�� �ݴ밡 �Ǿ� ����.
	{
		for (int j = 0; j < n_row; j++)
			mT.dMtrx[i][j] = dMtrx[j][i];
	}
	return mT;												// ��ȯ
}		
double Mtrx::MaxMtrx() const								// const�� ����Լ� �ٷ� �ڿ� �ٿ�, Ŭ���� �������� ���� �������� ������ ��Ÿ��.
															// ���� const�� ����� Ŭ���� ��ü�� ��밡����.
{
	double max = 0; 
	
	max = dMtrx[0][0];

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
			max = MAX(max, dMtrx[i][j]);					// ��� �������� ���� ū���� ã�� max�� �����Ѵ�.(��ũ�� �Լ� ���)
	}

	return max;												// �ִ밪 ��ȯ
}
double Mtrx::MinMtrx() const
{
	double min = 0;

	min = dMtrx[0][0];

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
			min = MIN(min, dMtrx[i][j]);					// ��� �������� ���� �ּҰ��� ã�´�.
	}

	return min;												// ��ȯ
}
void Mtrx::StaticDate(ofstream& fout, const Mtrx& mM)		// ��� ������ ���
{
	double sum = 0, avg = 0, dev2sum = 0, var = 0, std = 0;	// ���� ��, ���, ���������� ��, �л�, ǥ������
	int num_M = mM.row() * mM.col();						// �� ��� ������ ����

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
			sum += dMtrx[i][j];								// �� ���
	}
	avg = sum / num_M;										// ��� ���

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
			dev2sum += pow(dMtrx[i][j] - avg, 2);			// ���� ������ �� ���
	}
	var = dev2sum / num_M;									// ���������� ���� ���
	std = sqrt(var);										// �л��� ������ = ǥ������

	//���
	fout << "Mtrx (" << mM.Name() << ")'s StaticsData :" << endl;
	fout << "Max : " << mM.MaxMtrx() << ", Min : " << mM.MinMtrx() << ", Average : " <<
		avg << ", Variance : " << var << ", Std : " << std << endl;
}

Mtrx Mtrx::InvMtrx(int* solexist) const						// �����
{
	Mtrx InverseMtrx(n_row, n_col);
	Mtrx AugMtrx(n_row, n_col * 2);
	double pivDivide, anotherDiv;


	for (int j = 0; j < n_row; j++)			// ���� ������ ( ���� ����� ������ )
	{
		for (int k = 0; k < n_col; k++)
			AugMtrx.dMtrx[j][k] = dMtrx[j][k];
	}

	for (int j = 0; j < n_row; j++)			// ���� ������ ( ���� ��� I���� )
	{
		for (int k = n_col; k < n_col * 2; k++)
			AugMtrx.dMtrx[j][k] = (j == k - n_col) ? 1.0 : 0.0;
	}

	for (int p = 0; p < n_col; p++)
	{
		double max = fabs(AugMtrx.dMtrx[p][p]);
		//���� ��, �� ���� (1��°��,�� ��, 2��°��, ����, 3��°��,�� ��)
		// abs() = int���� ���� ��ȯ, fabs() = double ���� ���� ��ȯ

		for (int i = 0; i < n_row; i++)
		{
			max = MAX(max, fabs(AugMtrx.dMtrx[i][p]));		// �� p���� �� ��鿡 ���� p�������� �ִ밪�� ����
		}

		if (max < Epsilon)									// ���� max == 0�̶�� 
			*solexist = 0;									// �ظ� ���� �� ���� ���¶�� �ϰ�, solExist�� 0���� �������
		else
			*solexist = 1;									// �ƴϸ� solExist�� 1�� ���� ��, 
		//=================================�ذ� ���� �Ǻ� ����===================================

		if (*solexist == 0)									// ������� ���Ҽ� ���� ������ ����
			break;

		if (AugMtrx.dMtrx[p][p] != 1.00)							// p,p�� ���� 1�� �ƴѰ�� (1�̸� �� ������ ���� �Ȱ�ħ)
		{
			pivDivide = AugMtrx.dMtrx[p][p];
			AugMtrx.dMtrx[p][p] = 1.00;
			for (int k = p + 1; k < n_col * 2; k++)		// ����� ������ �迭�� ���������� SIZE_N�� �ι谡 ��...
				AugMtrx.dMtrx[p][k] /= pivDivide;					// p,p�� ���� 1�� �ǵ��� ���� ��� ���� p,p�� ���� ����
		}

		for (int j = 0; j < n_row; j++)
		{
			if ((j != p) && (AugMtrx.dMtrx[j][p] != 0.0))
				// p���� ������ ������ ��, ����, j���� p���� ���� 0(������ ��������)�� �ƴ� ����� ����
			{
				anotherDiv = AugMtrx.dMtrx[j][p];
				AugMtrx.dMtrx[j][p] = 0;
				for (int k = p + 1; k < n_col * 2; k++)	// ��� ���� ���� �����࿡ ���� �� ���� (��, p,p��°�� ��(1.0)����� ���� 0���� �������
					AugMtrx.dMtrx[j][k] = AugMtrx.dMtrx[j][k] - (anotherDiv * AugMtrx.dMtrx[p][k]);
			}
		}
	}

	for (int i = 0; i < n_row; i++)
		for (int j = 0; j < n_col; j++)
			InverseMtrx.dMtrx[i][j] = AugMtrx.dMtrx[i][j + n_col];

	
	return InverseMtrx;
}

/*					��� ��� �Լ�					*/		
void Mtrx::fprintMtrx(ofstream& fout)						// ���� ����Լ�
{
	const char a1 = 0xa1, a2 = 0xa2, a3 = 0xa3, a4 = 0xa4, a5 = 0xa5, a6 = 0xa6;
	//Ȯ���� �����ڵ� : ( �� : a6a1, �� : a6a2, �� : a6a3, �� : a6a4, �� : a6a5, �� : a6a6 )
	
	fout << name << " = " << endl;
	for (int i = 0; i < n_row; i++)
	{
		for (int k = 0; k < n_col; k++)
		{
			
			// ���ȣ ��ºκ� ( ���� [ )
			if (i == 0 && k == 0)
				fout << a6 << a3;										// ��
			else if (i > 0 && i < n_row - 1 && k == 0)
				fout << a6 << a2;										// ��
			else if (i == n_row - 1 && k == 0)
				fout << a6 << a6;										// ��

			fout.setf(ios::fixed);  fout.setf(ios::showpoint);
			fout << setw(9); fout.precision(2);
			fout << dMtrx[i][k];						// ���� ��ºκ�
			

			// ���ȣ ��ºκ� ( ���� ] )
			if (i == 0 && k == n_col - 1)
				fout << a6 << a4;										// ��
			else if (i > 0 && i < n_row - 1 && k == n_col - 1)
				fout << a6 << a2;										// ��
			else if (i ==  n_row - 1 && k == n_col - 1)
				fout << a6 << a5;										// ��
		}
		fout << endl;
	}
	fout << endl;

}
