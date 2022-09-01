/*
  ���ϸ� : "�ǽ�1_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- ����ü Student�� build�Ͽ�, ū ������ ������ �й����� ���, ���������� �� ���� ���

  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 8�� 29��)
  ���� Update : Version 1.0.1, 2022�� 8�� 29�� (�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
   �Ŵ�ȫ		 2022/08/29		v1.0.0		  �����ۼ�
   �Ŵ�ȫ		 2022/08/29		v1.0.1		  �ϼ�
   �Ŵ�ȫ		 2022/09/01		v1.0.2		  ���� ���� (GPA, ID) ����

===========================================================================================================
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "BigRand.h"
#include "Student.h"
using namespace std;

#define NUM_STUDENTS 5000											// �л��� ��
#define NUM_SEARCH 5												// SEARCH�� �л� ��
#define NUM_FIRST_LAST_BLOCK 100									// ����� �л��� ����

int main()
{
	ofstream fout;																			// ���� ����� ���� fout
	int* student_ids;																		// �й� ����Ʈ
	Student* students = NULL, * pSt;														// �л� �迭, �л� ����ü ������
	int student_search[NUM_SEARCH] = { 1, 123, 999, 2500, 4999 };							// SEARCH�� �л� ��

	/*				�л� ������ ���� ��� ������ ������� ����				
		- ���� ���н� �����޼����� ����ϸ� ����						*/	
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Error in opening 'output.txt'" << endl;
		exit(0);
	}

	/*				>> ���� �޸� �Ҵ� �� �ʱⰪ ����<< 				*/			
	student_ids = (int*)calloc(NUM_STUDENTS, sizeof(int));				// �л� ���� �°� �й� �迭 �Ҵ�
	students = (Student*)calloc(NUM_STUDENTS, sizeof(Student));			// �л� ���� �°� �л� ����ü �迭 �Ҵ�
	student_ids = genBigRandArray(NUM_STUDENTS, 0);						// �й� �迭 ����
	cout << "init Students Date ..." << endl;
	initStudents(students, student_ids, NUM_STUDENTS);
	cout << "init Students Date Complete...!" << endl << endl;

	/*					>> �л� ����ü �迭 ��� <<					
			- ������� �� ���Ͽ� �ʱⰪ������ �л� ������ ��, �й����� ���	*/		
	cout << "printing Students id in file..." << endl;
	fout << endl << endl;
	fout << "Initialized array of students : " << endl;
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);			// �й����� ����ϴ� �Լ�
	cout << "printing Students id in file Complete...!" << endl << endl;

	/*					>> �л� ����ü �迭 ���� 1 <<							
			- �л� �����͸� �й����� �̿��ؼ� ������������ ���� �� ��, �����	*/
	cout << "sorting Students by increasing id..." << endl;
	fout << endl << endl;
	fout << "Sorting array of students by non-decreasing order of ID : " << endl;
	sortStudentsByID(students, NUM_STUDENTS);													// �й� ������������ ����
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);			// ��� ���
	cout << "sorting Students by increasing id Complete...!" << endl << endl;


	/*					>> �л� ����ü �迭 ���� 2 <<
		- �л� �����͸�  ���� �� ��, �����	
		(1���� : ����(��������), 2���� : �й�(��������)						*/	
	cout << "sorting Students by (decreasing GPA and increasing id)..." << endl;
	fout << endl << endl;
	fout << "Sorting array of students by (decreasing order of GPA, increasing order of ID) : "  << endl;
	SS_StudentsByGPA_ID(students, NUM_STUDENTS);												// ������ �й��� �̿��� ����
	fprintBigArrayOfStudent_GPA_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);		// ���
	cout << "sorting Students by (decreasing GPA and increasing id) Complete...!" << endl << endl;

	/*					>> �л� ������ ���� Ž�� <<
			- ã�� ������ �迭�� �̿��� �л����� ����Ž������ ��ġ				*/
	cout << "Searching Students ..." << endl;
	fout << endl << endl;
	fout << "Sorting array of students by non-decreasing order of ID : " << endl;				// ���� 1�������� �й�������� �������� ������ (����Ž���� ���ĵ� �����Ϳ����� ����)
	sortStudentsByID(students, NUM_STUDENTS);
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);			// ���� ��� ���
	fout << endl << endl;
	fout <<  "Searching student with student_ID : " << endl;
	for (int i = 0; i < NUM_SEARCH; i++)														// Ž�� ����
	{
		pSt = binarySearchStudentByID(students, NUM_STUDENTS, student_search[i]);				// ����Ž������ �̿��� ã�� �л� ����ü �ּҰ��� ��ȯ����
		fout << "Student search by ID (" << setw(4) << student_search[i] << ") : ";				
		if (pSt != NULL)
			fprintStudent(fout, pSt);
		else
			fout << "NULL! - student was not found !!" << endl;									// ���� ��� ã�� ���ߴٴ� �޼��� ���
	}
	cout << "Searching Students Complete..!" << endl;

	/*					>> ������ <<		
			- ��� �۾��� ���� ��, ���� �ݱ�, �����Ҵ��� �迭�� ��ȯ����			*/
	fout.close();
	free(student_ids);
	free(students);

	return 0;
}