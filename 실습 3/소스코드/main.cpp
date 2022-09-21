/*
  ���ϸ� : "�ǽ�3_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- Class Mtrx (��� Ŭ����)�� ����� ����� �ϴ� ���α׷�
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 9�� 21��)
  ���� Update : Version 1.0.1, 2022�� 9�� 22�� (�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
   �Ŵ�ȫ		 2022/09/21		v1.0.0		  �����ۼ�
   �Ŵ�ȫ		 2022/09/22		v1.0.1		  �ϼ�

===========================================================================================================
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Mtrx.h"

#define INPUT "Matrix_data.txt"				// �Է����� "Matrix_date.txt"
#define OUTPUT "output.txt"					// ������� "output.txt"
using namespace std;

int main(void)
{
	ifstream fin;							// �Է¿� ����
	ofstream fout;							// ��¿� ����

	// ���� ���� ��, ������ ����� ��� ����
	fin.open(INPUT); fout.open(OUTPUT);
	if (fin.fail())
	{
		cout << "Error in opening Matrix_data.txt!!" << endl; exit;
	}
	if (fout.fail())
	{
		cout << "Error in opening output.txt!!" << endl; exit;
	}

	Mtrx mtrxA(fin);						// ��� A ����
	mtrxA.NameSetting("mtrxA");				// �̸� ����
	mtrxA.fprintMtrx(fout);					// ���

	// ��� B ���� �� ���
	Mtrx mtrxB(fin);
	mtrxB.NameSetting("mtrxB");
	mtrxB.fprintMtrx(fout);

	// ��� C ���� �� ���
	Mtrx mtrxC(fin);
	mtrxC.NameSetting("mtrxC");
	mtrxC.fprintMtrx(fout);

	// ��� D ( ��� A + ��� B ) ���� �� ���
	Mtrx mtrxD(mtrxA.row(), mtrxB.col());
	mtrxD = mtrxA.addMtrx(mtrxB);
	mtrxD.NameSetting("mtrxD = mtrxA.add(mtrxB)");
	mtrxD.fprintMtrx(fout);

	// ��� E ( ��� A - ��� B ) ���� �� ���
	Mtrx mtrxE(mtrxA.row(), mtrxB.col());
	mtrxE = mtrxA.subMtrx(mtrxB);
	mtrxE.NameSetting("mtrxE = mtrxA.sub(mtrxB)");
	mtrxE.fprintMtrx(fout);

	// ��� F ( ��� A * ��� C ) ���� �� ���
	Mtrx mtrxF(mtrxA.row(), mtrxC.col());
	mtrxF = mtrxA.mulMtrx(mtrxC);
	mtrxF.NameSetting("mtrxF = mtrxA.multiply(mtrxC)");
	mtrxF.fprintMtrx(fout);

	// ��� G ( ��� A ��ġ���) ���� �� ���
	Mtrx mtrxG(mtrxA.row(), mtrxA.col());
	mtrxG = mtrxA.transposeMtrx();
	mtrxG.NameSetting("mtrxG = mtrxA.transposeMtrx()");
	mtrxG.fprintMtrx(fout);

	// ���� �ݱ�
	fin.close();
	fout.close();
}