#include "Date.h"
#include <iostream>
#include <iomanip>
#include <string>

// 열거형 자료형 enum 요일, enum 월 이름 
enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT };
enum MONTHS { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
// 문자열 상수 배열들 ( 요일 이름, 월 이름 )
const char* WeekDayName[DAYS_P_WEEK] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const char* MonthName[MONTHS_YEAR + 1] = { "", "January", "February", "March", "April",
	"May", "June", "July", "August", "September", "October", "November", "December" };

// init Date ( 날짜 초기값 설정 및 입력 ) 
Date::Date()						// Date 클래스 초기형 설정
{
	year = 0; month = 0; day = 0;
}
Date::Date(int y, int m, int d)		// Date 클래스 입력값을 통한 초기값 설정
{
	setDate(y, m, d);
}
Date::~Date()						// Date 클래스 객체를 소멸할때 작동함
{
	// cout << "Date object instance is destructed" << endl;
	// delete();
}

/*					>> 날짜 입출력 함수 <<
	1. 날짜를 입력하는 함수, 그 날짜가 유효한 날짜인지도 검사
	2. 입력된 날짜를 출력형식에 맞게 출력해주는 함수
														*/
void Date::inputDate()							// 날짜 입력함수
{
	int y, m, d;

	// 날짜 입력 ( scanf 같은 것 )
	cout << "Enter date in year month day : ";
	cin >> y >> m >> d;

	// 유효한 날짜인지 검사
	if (isValidDate(y, m, d))					// 유효한 날짜라면 정상 입력
	{
		year = y;
		month = m;
		day = d;
	}
	else
	{											// 유효하지 않은 날짜는 에러메세지 출력
		cout << "illegal Date! Program aborted. \n";
		exit(1);
	}
}
void Date::printDate()							// 날짜 출력함수
{
	// 1. 요일 이름을 담은 문자열 상수 배열
	// 2. 월 이름을 담은 문자열 상수 배열
	int yearDay = 0;
	int weekday = 0;

	// 월을 먼저 출력함. string을 이용해 문자열 출력
	if ((month >= 1) && (month <= 12))
		cout << right << setw(10) << string(MonthName[month]);
	cout << " " << setw(2) << day << ", " << setw(4) << year;

	// 요일을 구하기 위해 weekday()로 구함
	yearDay = getYearDay();
	weekday = getWeekDay();
	cout << "(" << setw(10) << string(WeekDayName[weekday]) << ")";
}

void Date::fprintDate(ostream& fout)			// 날짜 파일 출력 함수
{
	// 1. 요일 이름을 담은 문자열 상수 배열
	// 2. 월 이름을 담은 문자열 상수 배열
	
	int yearDay = 0;
	int weekday = 0;

	// 월을 먼저 출력함. string을 이용해 문자열 출력
	if ((month >= 1) && (month <= 12))
		fout << right << setw(10) << string(MonthName[month]);
	fout << " " << setw(2) << day << ", " << setw(4) << year;

	// 요일을 구하기 위해 weekday()로 구함
	yearDay = getYearDay();
	weekday = getWeekDay();
	fout << "(" << setw(10) << string(WeekDayName[weekday]) << ")";
}

void Date::fprintCalender_month(ostream& fout)
{
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	fout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>" <<  year << "년" << month << "월<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	fout << "==================================================================" << endl;
	fout << "	일	월	화	수	목	금	토" << endl;
	fout << "==================================================================" << endl;

	if (isLeapYear())											// 올해가 윤년인지 판단
		days_month[FEB] = 29;									// 2월의 일수는 29일이다.

	for (int wd = 0; wd < (day % 7); wd++)						// 시작날까지 tap키로 건너뛰기
		fout << "\t";

	for (int d = 1; d <= days_month[month]; d++)				// 1일 부터 시작하여 그 달의 날수 까지 반복
	{
		if (day % 7 == 0)
			fout << "\n   ";									// 만약 일요일이면 한줄 내리기
		fout << "\t" << d;										// 아니면 정상 출력
		day++;													// days를 더해줘서 날수를 맞춘다.
	}
	printf("\n==================================================================\n");
}

void Date::setDate(int y, int m, int d)				// 날짜 설정하는 함수
{
	/*							>> 날짜 설정 <<
			1. 년도 설정
			2. 월 설정 ( 1월 ~ 12월 안에 포함되어있으면, 아니면 에러)
			3. 일 설정 ( 1일 ~ 31일 안에 포함되어있으면, 아니면 에러)
																	*/
	year = y;
	if ((m >= 1) && (m <= 12))
		month = m;
	else
	{
		cout << "illegal month value! Program aborted. \n";
		exit(1);
	}

	if ((d >= 1) && (d <= 31))
		day = d;
	else
	{
		cout << "illegal day value! Program aborted. \n";
		exit(1);
	}
}
void Date::setMonth(int m)						// 월 설정하는 함수
{
	// 1월~12월 안에 있는 날짜만 허용. 아니면 에러메세지 출력
	if ((m >= 1) && (m <= 12))
		month = m;
	else
	{
		cout << "illegal month value! Program aborted. \n";
		exit(1);
	}
	day = 1;
}
void Date::setYear(int y)						// 년 설정하는 함수
{
	// 기원전 년도는 포함시키지 않는다. 따라서 1년 이상의 년도만 허용
	if (y >= 1)
		year = y;
	else
	{	// 포함되지 않는 년도 입력시 에러메세지 출력
		cout << "illegal year value! Program aborted. \n";
		exit(1);
	}
}
void Date::setRandDateAttributes()
{
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	year = rand() % 122 + 1900;					// 현재 년도가 2022년이므로 최대 년도가 2022년을 넘기지 않게 함
	month = rand() % 12 + 1;					// 1월부터 시작이므로
	if (isLeapYear())											// 올해가 윤년인지 판단
		days_month[FEB] = 29;									// 2월의 일수는 29일이다.
	day = rand() % days_month[month] + 1;		// 1일부터 시작
}
/*					>> 지나간 날 수, 요일 측정 <<
		1. 이번년도 1월 1일 부터 현재 날짜까지 며칠이 지나갔는지 측정하는 함수
		2. 오늘의 요일이 뭔지 값을 반환하여 알아내는 함수
*/
int Date::getYearDay()							// 이번 년도에서 지나간 날수 측정
{
	// 윤년일 때, 2월의 일수가 변화할 수 있기 때문에 상수로 지정하면 안됨
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;

	if (isLeapYear())							// 올해가 윤년인지 판단
		days_month[FEB] = 29;					// 2월의 일수는 29일이다.

	// 1월부터 시작, 현재 달의 전까지 일을 더함
	for (int m = JAN; m < month; m++)
	{
		yearDay += days_month[m];
	}
	yearDay += day;								// 이번달 1일에서 지나간 날수 더해줌

	return yearDay;								// 반환
}
int Date::getYearDay(int m, int d)				// 이하 동일, 매개변수로 월과 일을 받아오는것만 다름
{
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;

	if (isLeapYear())
		days_month[FEB] = 29;
	for (int months = JAN; months < m; months++)
	{
		yearDay += days_month[months];
	}
	yearDay += d;

	return yearDay;
}
int Date::getWeekDay()								// 오늘이 무슨 요일인지 판별해주는 함수
{
	int weekDay_AD010101 = MON;						// 기준일 (1년 1월 1일)의 요일 = 월요일
	int weekDay;
	int elapsedDays = 0;							// 지나간 날수

	elapsedDays = getElapsedDaysFromAD010101();		// 지나간 날수 구하는 함수

	// (기준일 + 지나간 날수) 에서 7을 나누고 남은 나머지를 통해 요일 판별
	weekDay = (weekDay_AD010101 + elapsedDays) % 7;

	return weekDay;									// 반환
}
/*						>> 지나간 날수 구하는 함수 <<
		1. 기준일 (1년 1월 1일)로부터 며칠이 지났는지 알아내는 함수
																		*/
int Date::getElapsedDaysFromAD010101()				// 지나간 날수 구하는 함수
{
	int yearDay;
	int elpsDay = 0;

	for (int y = 2; y < year; y++)					// 1년이 기준일이기 때문에 1년은 제외함
	{
		if (isLeapYear(y))							// y가 윤년일 때 하루 추가된 366일 추가
			elpsDay += 366;
		else
			elpsDay += 365;							// 아니면 기존처럼 365일
	}

	yearDay = getYearDay();							// 이번년도 1월 1일로부터 며칠이 떨어져 있는가 구함
	elpsDay += (yearDay - 1);						// yearDay에서 -1을 해야 오차가 안생김(이유 : 1년 1월 1일 계산시 yearDay가 1일로 계산됨)

	return elpsDay;									// 반환
}
int Date::getElapsedDaysFromAD010101(Date today)	// 동일, 매개변수로 값을 받아와서 getyear등을 사용해서 값을 가져옴
{
	int yearDay;
	int elpsDay = 0;

	for (int y = 2; y < today.getYear(); y++)
	{
		if (isLeapYear(y))
			elpsDay += 366;
		else
			elpsDay += 365;
	}

	yearDay = getYearDay();
	elpsDay += (yearDay - 1);

	return elpsDay;
}

/*								>> 윤년 판단하는 함수 <<
		1. 올해가 윤년인지 판단하는 함수
		2. 올해가 4, 100으로 나누어 떨어지지만, 400으로 나누어 떨어지지 않는 해 = 윤년
															*/
bool Date::isLeapYear()
{
	if ((year % 100 == 0) && (year % 4) == 0 && (year % 400 != 0))
		// 올해가 4, 100으로 나누어 떨어지고, 400으로 나누어 떨어지지 않는가
		return true;
	else
		return false;
}
bool Date::isLeapYear(int y)		// 이하 동일
{
	if ((y % 100 == 0) && (y % 4) == 0 && (y % 400 != 0))
		return true;
	else
		return false;
}

bool Date::isValidDate(int y, int m, int d)				// 이 날짜가 유효한 날짜인가 판별하는 함수
{
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (isLeapYear())							// 올해가 윤년인지 판단
		days_month[FEB] = 29;					// 2월의 일수는 29일이다. 

	// 월이 1 ~ 12, 일이 1 ~ 31 사이에 들어있는 값이 맞나? 판별
	if (((m >= 1) && (m <= 12)) && ((d >= 1) && (d <= days_month[m])))
		return true;
	else
	{	// 아니면 오류 에러메세지 출력
		cout << "illegal date! (" << m << ", " << d << ") ==> Program aborted.\n";
		return false;
	}
}