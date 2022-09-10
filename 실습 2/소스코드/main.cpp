/*
  파일명 : "실습2_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- Class Date, Class Person을 구성하여, 크리스마스와 날짜가 얼마 차이나는지 구하는 프로그램
  프로그램 작성자 : 신대홍(2022년 9월 8일)
  최종 Update : Version 1.0.0, 2022년 9월 8일 (신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자		   수정일		 버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
   신대홍		 2022/09/08		v1.0.0		  최초작성
   신대홍		 2022/09/11		v1.0.1		  완성
===========================================================================================================
*/

#pragma warning(disable: 4996)					// 오류 안뜨게 하는 pragma정의
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "Date.h"
#include "Person.h"

using namespace std;

#define NUM_PERSON 10
#define OUTPUT "output.txt"

int main()
{
	ofstream fout;
	fout.open(OUTPUT);
	if (fout.fail())
	{
		cout << "Error in opening output.txt !!" << endl;
		exit;
	}

	/*			파트 1 : Class Date			*/

	Date AD010101(1, 1, 1);
	int year, month, day;
	int daysToChristmas;
	time_t currentTime;
	struct tm* time_and_date;		// 오늘 날짜를 가져오기 위한 구조체 tm

	time(&currentTime);
	time_and_date = localtime(&currentTime);			// 현재 날짜와 시간을 가져옴
	year = time_and_date->tm_year + 1900;				// 가져온 데이터와 표기할 데이터가 달라 맞게 수정
	month = time_and_date->tm_mon + 1;					// 1900년을 0년으로 시작, 1월이 0으로 시작함
	day = time_and_date->tm_mday;
	Date newYearDay(year, 1, 1), today(year, month, day), christmas(year, 12, 25);	// 객체 생성

	// 출력 ( 1년 1월 1일, 오늘 날짜, 크리스마스 등, 크리스마스까지 남은 날짜도 출력 ) 
	fout << "AD Jan. 1, 1 is"; AD010101.fprintDate(fout); fout << endl;
	fout << "Today is "; today.fprintDate(fout); fout << endl;
	fout << "New year's day of this year was "; newYearDay.fprintDate(fout); fout << endl;
	fout << "Christmas of this year is "; christmas.fprintDate(fout); fout << endl;

	if (today.getMonth() == christmas.getMonth() && today.getDay() == christmas.getDay())
	{
		fout << "Today is Christmas! Happy Christmas to you all !!" << endl;			// 축하메세지 출력
	}
	// 아니면
	else
	{
		// 크리스마스까지 며칠이 남았는지 계산
		daysToChristmas = christmas.getElapsedDaysFromAD010101() 
			- today.getElapsedDaysFromAD010101();
		fout << "Sorry, today is not Christmas!\n";
		fout << "You must wait " << daysToChristmas << " day(s) to Christmas !" << endl;
	}
	fout << endl;

	/*			파트 2 : Class Person			*/

	srand((unsigned int)time(NULL));								// 랜덤 시드 생성
	
	/*			임의의 사람 2명을 클래스 객체로 생성 후, 출력			*/
	Person p1(string("Hong, Gil-Dong"), Date(2000, 1, 1)),
		p2(string("Lee, Soo - Jeong"), Date(2018, 9, 1));
				// 출력
	fout << "Person p1 : " << endl; p1.fprintPerson(fout); fout << endl;
	fout << "Person p2 : " << endl; p2.fprintPerson(fout); fout << endl;

	/*			임의의 사람 n명을 클래스 객체로 동적할당으로 생성 후, 출력			*/
	fout << endl << "Generating array of persons ... " << endl;
	Person* persons;												// 클래스 포인터(배열) 할당
	persons = (Person*) new Person[NUM_PERSON];						// 동적할당함 (10개만큼 배열 할당)
	for (int i = 0; i < NUM_PERSON; i++)
	{
		persons[i].setRandPersonAttribute();						// 랜덤으로 사람을 생성
		persons[i].fprintPerson(fout);								// 바로바로 출력
		fout << endl;
	}
	fout << endl;

	delete[] persons;												// 다 끝난 후, 반환 (free())
	fout.close();													// 파일닫기
	return 0;
}

