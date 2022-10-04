/*
  파일명 : "실습5_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 클래스 Date, Person, Student(Person을 상속받음), StudentArray를 만들고, 학생 데이터를 생성, 출력함
  프로그램 작성자 : 신대홍(2022년 10월 3일)
  최종 Update : Version 1.0.0, 2022년 10월 3일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자	  수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/10/03		v1.0.0		  최초작성
	신대홍		 2022/10/05		v1.1.0		  완성
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