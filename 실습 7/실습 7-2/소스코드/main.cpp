/*
  파일명 : "실습7-2_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- STL을 이용하여 T_Array 탬플릿로써 학생데이터를 다룬다
  프로그램 작성자 : 신대홍(2022년 10월 17일)
  최종 Update : Version 1.0.0, 2022년 10월 18일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자	  수정일			버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/10/18		v1.0.0		  최초작성
===========================================================================================================
*/

#include <iostream>
#include "VectorHandler.h"
#include "Student.h"
#include "T_Array.h"


using namespace std;
#define NUM_STUDENTS 10

int main(void)
{
	// 학생 데이터
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

	// 학생 데이터 대입
	T_Array<Student*, int> stArray_keySTID(NUM_STUDENTS, "T_Array<Student, keyST_ID>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keySTID.insert(i, &students[i]);
	}
	// 학생 데이터를 ST_ID(학번)으로 선택정렬 (오름차순)
	stArray_keySTID.selection_sort(string("ST_ID"), INCREASING);
	cout << "T_Array<Student*_keyID> at Initialization :" << endl;
	stArray_keySTID.print(1);

	// 학생 데이터 대입
	T_Array<Student*, string> stArray_keyName(NUM_STUDENTS, "T_Array<Student, keyName>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyName.insert(i, &students[i]);
	}
	// 학생 데이터를 NAME(이름)으로 선택정렬 (오름차순)
	stArray_keyName.selection_sort(string("NAME"), INCREASING);
	cout << "T_Array<Student*_keyName> after selection_sorting (increasing order) by Name :" << endl;
	stArray_keyName.print(1);

	// 학생 데이터 대입
	T_Array<Student*, double> stArray_keyGPA(NUM_STUDENTS, "T_Array<Student, keyGPA>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyGPA.insert(i, &students[i]);
	}
	// 학생 데이터를 GPA(성적)으로 선택정렬 (내림차순)
	stArray_keyGPA.selection_sort(string("GPA"), DECREASING);
	cout << "T_Array<Student*_keyGPA> after selection_sorting (decreasing order) by GPA:" << endl;
	stArray_keyGPA.print(1);

	// 학생 데이터 대입
	T_Array<Student*, int> stArray_keyRegID(NUM_STUDENTS, "T_Array<Student, keyRegID>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyRegID.insert(i, &students[i]);
	}
	// 학생 데이터를 REG_ID(주민등록)으로 병합정렬 (오름차순)
	stArray_keyRegID.merge_sort(string("REGID"), INCREASING);
	cout << "T_Array<Student*_keyRegID> after merge_sorting (increasing order) by regID :" << endl;
	stArray_keyRegID.print(1);

	// 학생 데이터 대입
	T_Array<Student*, string> stArray_keyNation(NUM_STUDENTS, "T_Array<Student, keyNation>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyNation.insert(i, &students[i]);
	}
	// 학생 데이터를 NATION(국가)으로 병합정렬 (오름차순)
	stArray_keyNation.merge_sort(string("NATION"), INCREASING);
	cout << "T_Array<Student*_keyNation> after merge sorting (increasing order) by nation : " << endl;
	stArray_keyNation.print(1);

	return 0;
}