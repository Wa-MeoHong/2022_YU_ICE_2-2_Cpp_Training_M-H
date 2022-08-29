#ifndef STUDENT_H
#define BIGRAND_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdbool.h>
using namespace std;

#define MIN_NAME_LEN 5							// �ּ� �̸� ���� 5
#define MAX_NAME_LEN 15							// �ִ� �̸� ���� 5

/*
	�л� ����ü 
	{
		�й�(st_id)
		�̸�
		����
		�г�
		����
	}
*/

typedef struct Student 
{
	int st_id;
	char name[MAX_NAME_LEN + 1];
	char department[MAX_NAME_LEN + 1];
	int grade;
	double GPA;
} Student;

/* 
					>>> �Լ� ��� <<< 
	1. �л� ����ü �迭 �ʱ� ����
	2. �л� 1�� ���, printStudnet() �Լ� ���
	3. �л� 1�� ��� ( �й��� ��� )
	4. �л� ����ü �迭 ��� ( �ٿ��� ) 
	5. �л� 1�� ��� ( ����, �й��� ��� )
	6. �л� ����ü �迭 ��� ( ����, �й��� ���, �ٿ��� )
	7. �л� ����ü �迭 ���� ( ���� �������� ����, 2������ �й� ��������)
	8. �л� ���� Ž�� 
*/

void initStudents(Student* students, int* student_ids, int num_students);			
void fprintStudent(ostream& fout, Student* pSt);
void fprintStudentID(ostream& fout, Student* pSt);
void fprintBigArrayOfStudent_IDs(ostream& fout, Student* students, int size_array, int size_first_last_block);
void fprintStudentGPA_ID(ostream& fout, Student* pSt);
void fprintBigArrayOfStudent_GPA_IDs(ostream& fout, Student* students, int size_array, int size_first_last_block);
void sortStudentsByID(Student students[], int num_students);
void SS_StudentsByGPA_ID(Student* students, int num_students);
Student* binarySearchStudentByID(Student* students, int num_students, int st_id);

#endif