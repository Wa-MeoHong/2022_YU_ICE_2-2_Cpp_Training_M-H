/*
  ���ϸ� : "�ǽ�7-1_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- STL�� �̿��Ͽ� ���� ��ü�ν� �л������͸� �ٷ��
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 10�� 17��)
  ���� Update : Version 1.0.0, 2022�� 10�� 17��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������	  ������			����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/10/17		v1.0.0		  �����ۼ�
===========================================================================================================
*/

#include <iostream>
#include "VectorHandler.h"
#include "Student.h"

using namespace std;
#define NUM_STUDENTS 10

int main(void)
{
	// �л� ������
	Student students[NUM_STUDENTS] =
	{
		Student(5555, "Kim", 10205, "Korea", 3.57),
		Student(1234, "Lee", 11213, "Korea", 4.37),
		Student(4444, "Park", 12227, "Korea", 3.72),
		Student(2222, "Hao", 10121, "China", 2.35),
		Student(3333, "James", 11219, "USA", 3.89),
		Student(6666, "Thomas", 12320, "UK", 4.42),
		Student(7777, "Leon", 10722, "France", 4.12),
		Student(9999, "Carlo", 11519, "Italy", 4.35),
		Student(1000, "Tanaka", 13920, "Japan", 3.21),
		Student(8888, "Wang", 10622, "China", 3.45)
	};
	vector<Student> v_students(students, students + NUM_STUDENTS);
	cout << "Initial v_students :" << endl;
	printVector(v_students);

	sort(v_students.begin(), v_students.end());


	cout << "\nstudents after sorting by st_id :" << endl;
	printVector(v_students);

	return 0;
}