#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

#define WEEKDATY_AD01JAN01 MON					// 1년 1월 1일은 월요일이다
#define MONTHS_YEAR 12							// 1년 달 수 : 12
#define DAYS_P_WEEK 7							// 일주일은 7일
#define Secs_in_Minute 60						// 1분 = 60초
#define Secs_in_Hour (Secs_in_Minute * 60)		// 1시간 = 60분 * 60초 = 3600초
#define Secs_in_DAY (Secs_in_Hour* 24)			// 1일 = 24시간 * 60분 * 60초 = 86400초
#define LOCAL_GMT_OFFSET_HOUR 9					// 한국은 표준시 기준 9시간 느림 (GMT +9H)

class Date
{
public:
	Date();										// default constructor (기본 생성자), __init__ 
	Date(int y, int m, int d);					// constructor (생성자)
	~Date();									// destructor (소멸자)
	void inputDate();							// 날짜 input 하는 함수
	void printDate();							// 날짜 출력하는 함수
	void fprintDate(ostream& fout);				// 날짜 파일입출력 함수
	void fprintCalender_month(ostream& fout);	// 달력 출력 함수

	// 데이터 멤버 변경자 (mutator)
	void setDate(int y, int m, int dy);			// 날짜 세팅하는 함수
	void setMonth(int m);
	void setYear(int y);
	void setRandDateAttributes();

	// 데이터 멤버 접근자 (accessor)
	int getYear() { return year; }
	int getMonth() { return month; }			// 무슨달인지 구함 ( 1월, 2월 ..)
	int getDay() { return day; }
	int getYearDay();
	int getYearDay(int m, int d);
	int getWeekDay();
	int getElapsedDaysFromAD010101();			// 1년 1월 1일 부터 며칠 떨어져있는지 계산하는 함수
	int getElapsedDaysFromAD010101(Date);


private:
	bool isLeapYear();							// check whether the year is leap year
	bool isLeapYear(int y);
	bool isValidDate(int y, int m, int d);
	int year;									// privite 변수 year, month, day
	int month;
	int day;
};

#endif // !DATE_H