#ifndef BIGRAND_H
#define BIGRAND_H

#include <iostream>						// �⺻���� standard ���̺귯���� ��� ����
#include <fstream>						// ���� ����� ���� ���̺귯��
#include <iomanip>						// ������� ������ �Ҷ� ���� ���̺귯��
#include <stdbool.h>
using namespace std;

/*
					>>> �Լ� ��� <<<
	1. ���� ���� �����ϴ� �Լ�
	2. �������ִ� �Լ�
	3. ������ ����ϴ� �Լ�

*/
int* genBigRandArray(int num_rands, int offset);							
void suffleArray(int* bigRand, int num_rands);								
void fPrintBigRandArray(ofstream& fout, int* bigRand, int num_rands);		

#endif