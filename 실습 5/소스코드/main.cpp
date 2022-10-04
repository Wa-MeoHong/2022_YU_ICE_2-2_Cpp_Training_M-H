/*
  ���ϸ� : "�ǽ�5_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- Ŭ���� Date, Person, Student(Person�� ��ӹ���), StudentArray�� �����, �л� �����͸� ����, �����
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 10�� 3��)
  ���� Update : Version 1.0.0, 2022�� 10�� 3��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������	  ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/10/03		v1.0.0		  �����ۼ�
	�Ŵ�ȫ		 2022/10/05		v1.1.0		  �ϼ�
===========================================================================================================
*/

#include "StudentArray.h"
#include <iostream>
#include <fstream>

#define NUM_STUDENTS 10
#define LEN 20
#define OUTPUT "output.txt"
using namespace std;

const char* SortStand[LEN] = { "", "ST_id","Student Name", "GPA", "BirthDate" };

int main(void)
{
	srand((unsigned int)time(NULL));

	StudentArray studentArray(NUM_STUDENTS);
	ofstream fout;
	int st_ids[NUM_STUDENTS];

	fout.open(OUTPUT);
	if (fout.fail())
	{
		cout << "Fail to open an output file (output.txt)" << endl;
		exit(1);
	}
	genST_ids(NUM_STUDENTS, st_ids);
	fout << "Initializing Students Array ( NUM_students : " << NUM_STUDENTS << ")" << endl;

	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		studentArray[i] = genRandStudent(st_ids[i]);
	}
	fout << studentArray << endl;

	for (int sel = 1; sel <= 4; sel++)
	{
		fout << "Sorting Student Array by " << SortStand[sel] << ": " << endl;
		studentArray.SelectSort(sel);
		fout << studentArray << endl;
	}

	fout << endl;
	fout.close();
	/*for (int i = 0; i < NUM_STUDENTS; i++)
	{
		cout << st_ids[i] << endl;
	}*/

	return 0;
}