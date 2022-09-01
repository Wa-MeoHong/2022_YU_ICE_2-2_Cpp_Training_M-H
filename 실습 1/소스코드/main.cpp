/*
  파일명 : "실습1_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 구조체 Student를 build하여, 큰 난수를 생성해 학번으로 사용, 선택정렬한 후 파일 출력

  프로그램 작성자 : 신대홍(2022년 8월 29일)
  최종 Update : Version 1.0.1, 2022년 8월 29일 (신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
   신대홍		 2022/08/29		v1.0.0		  최초작성
   신대홍		 2022/08/29		v1.0.1		  완성
   신대홍		 2022/09/01		v1.0.2		  선택 정렬 (GPA, ID) 수정

===========================================================================================================
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "BigRand.h"
#include "Student.h"
using namespace std;

#define NUM_STUDENTS 5000											// 학생의 수
#define NUM_SEARCH 5												// SEARCH할 학생 수
#define NUM_FIRST_LAST_BLOCK 100									// 출력할 학생의 개수

int main()
{
	ofstream fout;																			// 파일 입출력 변수 fout
	int* student_ids;																		// 학번 리스트
	Student* students = NULL, * pSt;														// 학생 배열, 학생 구조체 포인터
	int student_search[NUM_SEARCH] = { 1, 123, 999, 2500, 4999 };							// SEARCH할 학생 수

	/*				학생 데이터 관련 출력 파일을 쓰기모드로 열기				
		- 만약 실패시 에러메세지를 출력하며 종료						*/	
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Error in opening 'output.txt'" << endl;
		exit(0);
	}

	/*				>> 동적 메모리 할당 및 초기값 설정<< 				*/			
	student_ids = (int*)calloc(NUM_STUDENTS, sizeof(int));				// 학생 수에 맞게 학번 배열 할당
	students = (Student*)calloc(NUM_STUDENTS, sizeof(Student));			// 학생 수에 맞게 학생 구조체 배열 할당
	student_ids = genBigRandArray(NUM_STUDENTS, 0);						// 학번 배열 생성
	cout << "init Students Date ..." << endl;
	initStudents(students, student_ids, NUM_STUDENTS);
	cout << "init Students Date Complete...!" << endl << endl;

	/*					>> 학생 구조체 배열 출력 <<					
			- 쓰기모드로 연 파일에 초기값설정된 학생 데이터 중, 학번만을 출력	*/		
	cout << "printing Students id in file..." << endl;
	fout << endl << endl;
	fout << "Initialized array of students : " << endl;
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);			// 학번만을 출력하는 함수
	cout << "printing Students id in file Complete...!" << endl << endl;

	/*					>> 학생 구조체 배열 정렬 1 <<							
			- 학생 데이터를 학번만을 이용해서 오름차순으로 정렬 한 후, 출력함	*/
	cout << "sorting Students by increasing id..." << endl;
	fout << endl << endl;
	fout << "Sorting array of students by non-decreasing order of ID : " << endl;
	sortStudentsByID(students, NUM_STUDENTS);													// 학번 오름차순으로 정렬
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);			// 결과 출력
	cout << "sorting Students by increasing id Complete...!" << endl << endl;


	/*					>> 학생 구조체 배열 정렬 2 <<
		- 학생 데이터를  정렬 한 후, 출력함	
		(1순위 : 성적(내림차순), 2순위 : 학번(오름차순)						*/	
	cout << "sorting Students by (decreasing GPA and increasing id)..." << endl;
	fout << endl << endl;
	fout << "Sorting array of students by (decreasing order of GPA, increasing order of ID) : "  << endl;
	SS_StudentsByGPA_ID(students, NUM_STUDENTS);												// 성적과 학번을 이용해 정렬
	fprintBigArrayOfStudent_GPA_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);		// 출력
	cout << "sorting Students by (decreasing GPA and increasing id) Complete...!" << endl << endl;

	/*					>> 학생 데이터 이진 탐색 <<
			- 찾을 데이터 배열을 이용해 학생들을 이진탐색으로 서치				*/
	cout << "Searching Students ..." << endl;
	fout << endl << endl;
	fout << "Sorting array of students by non-decreasing order of ID : " << endl;				// 먼저 1차적으로 학번순서대로 오름차순 정렬함 (이진탐색은 정렬된 데이터에서만 가능)
	sortStudentsByID(students, NUM_STUDENTS);
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);			// 정렬 결과 출력
	fout << endl << endl;
	fout <<  "Searching student with student_ID : " << endl;
	for (int i = 0; i < NUM_SEARCH; i++)														// 탐색 시작
	{
		pSt = binarySearchStudentByID(students, NUM_STUDENTS, student_search[i]);				// 이진탐색법을 이용해 찾은 학생 구조체 주소값을 반환받음
		fout << "Student search by ID (" << setw(4) << student_search[i] << ") : ";				
		if (pSt != NULL)
			fprintStudent(fout, pSt);
		else
			fout << "NULL! - student was not found !!" << endl;									// 없을 경우 찾지 못했다는 메세지 출력
	}
	cout << "Searching Students Complete..!" << endl;

	/*					>> 마무리 <<		
			- 모든 작업이 끝난 후, 파일 닫기, 동적할당한 배열을 반환해줌			*/
	fout.close();
	free(student_ids);
	free(students);

	return 0;
}