/*
  ���ϸ� : "�ǽ�4_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- Class Mtrx (��� Ŭ����)�� ����� ������ �����ε带 �̿��� ����� �ϴ� ���α׷�
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 9�� 26��)
  ���� Update : Version 1.0.0, 2022�� 9�� 26��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/09/26		v1.0.0		  �����ۼ�

===========================================================================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Class_Mtrx.h"							// ��� Ŭ���� ���
#include "MtrxArray.h"						// ��� �迭 Ŭ���� ���

using namespace std;

#define NUM_MTRX 8							// ���� �迭 ����
#define INPUT "Matrix_data.txt"				// �Է����� "Matrix_date.txt"
#define OUTPUT "Result.txt"					// ������� "Result.txt"


int main(void)
{
	ifstream fin;
	ofstream fout;

	fin.open(INPUT);						// �Է� ���� ����
	if (fin.fail())	{
		cout << "Error! Matrix_data.txt doesn't open!!" << endl; exit(0);
	}
	fout.open(OUTPUT);						// ��� ���� ����
	if (fout.fail()) {
		cout << "Error! Result.txt doesn't open!!" << endl; exit(0);
	}
	MtrxArray mtrx(NUM_MTRX);				// �迭 �����

	// ��� 0, ��� 1, ��� 2 ���Ͽ��� �Է� ����
	fin >> mtrx[0] >> mtrx[1] >> mtrx[2];
	// �Է¹��� ��, �̸� ����
	mtrx[0].NameSetting("Mtrx[0] = ");
	mtrx[1].NameSetting("Mtrx[1] = ");
	mtrx[2].NameSetting("Mtrx[2] = ");

	// ��� 0, 1, 2 ���Ͽ� ���
	fout << mtrx[0] << endl;
	fout << mtrx[1] << endl;
	fout << mtrx[2] << endl;
	cout << "Matrix data (Mtrx[0], Mtrx[1], Mtrx[2]) print complete! " << endl;

	// ��� ���� �� ���
	mtrx[3] = mtrx[0] + mtrx[1];
	mtrx[3].NameSetting("Mtrx[3] = Mtrx[0] + Mtrx[1] = ");
	fout << mtrx[3] << endl;
	cout << "Add Matrix print complete! " << endl;

	// ��� �E�� �� ���
	mtrx[4] = mtrx[0] - mtrx[1];
	mtrx[4].NameSetting("Mtrx[4] = Mtrx[0] - Mtrx[1] = ");
	fout << mtrx[4] << endl;
	cout << "Substract Matrix print complete! " << endl;

	// ��� ���� �� ���
	mtrx[5] = mtrx[0] * mtrx[2];
	mtrx[5].NameSetting("Mtrx[5] = Mtrx[0] * Mtrx[2] = ");
	fout << mtrx[5] << endl;
	cout << "Multiple Matrix print complete! " << endl;

	// ��� 6�� ��� 5�� ��ġ���
	mtrx[6] = ~mtrx[5];
	mtrx[6].NameSetting("Mtrx[6] = ~Mtrx[5] = ");
	fout << mtrx[6] << endl;
	cout << "Transpose Matrix print complete! " << endl;

	// ��� 7 == ��� 0, ��� 0�� ����
	mtrx[7] = mtrx[0];
	mtrx[7].NameSetting("Mtrx[7] = Mtrx[0] = ");
	fout << mtrx[7] << endl;
	cout << "Substitute Matrix print complete! " << endl;

	// ��� 0�� ��� 7�� ������ �ٸ��� ��
	if (mtrx[0] == mtrx[7])
		fout << "Mtrx[0] and Mtrx[7] are equal." << endl;
	if (mtrx[5] != mtrx[6])
		fout << "Mtrx[5] and Mtrx[6] are not equal." << endl;

	// ���� �ݱ�
	fin.close();
	fout.close();

	return 0;
}
