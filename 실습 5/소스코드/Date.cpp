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


istream& operator>>(istream& input, Date& D)
{
	int y, m, d;

	// 날짜 입력 ( scanf 같은 것 )
	cout << "Enter date in year month day : ";
	input >> y >> m >> d;

	// 유효한 날짜인지 검사
	if (D.isValidDate(y, m, d))					// 유효한 날짜라면 정상 입력
	{
		D.year = y;
		D.month = m;
		D.day = d;
	}
	else
	{												// 유효하지 않은 날짜는 에러메세지 출력
		cout << "illegal date! (" << m << ", " << d << ") ==> Program aborted.\n";
		exit(1);
	}

	return input;
	// TODO: 여기에 return 문을 삽입합니다.
}
ostream& operator<<(ostream& output, const Date& D)
{
	output << "(" << setw(4) << D.Year() << "-"
		<< setw(2) << D.Month() << "-" << setw(2) << D.Day() << ")";

	return output;
	// TODO: 여기에 return 문을 삽입합니다.
}

Date genRandDate()
{
	Date temp(1, 1, 1);
	int year, month, day;
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	year = rand() % 100 + 2000;					// 2000 ~  2999년 사이의 값을 출력
	if (isLeapYear(year))						// 올해가 윤년인지 판단
		days_month[FEB] = 29;					// 2월의 일수는 29일이다.

	month = rand() % 12 + 1;					// 1월부터 시작이므로
	day = rand() % days_month[month] + 1;		// 1일부터 시작

	temp.setDate(year, month, day);

	return temp;
}
bool isLeapYear(int y)
{
	if ((y % 100 == 0) && (y % 4) == 0 && (y % 400 != 0))
		// 올해가 4, 100으로 나누어 떨어지고, 400으로 나누어 떨어지지 않는가
		return true;
	else
		return false;
}

Date::Date()
{
	year = 0; month = 0; day = 0;
}
Date::Date(int y, int m, int d)
{
	setDate(y, m, d);
}

void Date::setDate(int newYear, int newMonth, int newDay)
{
	/*							>> 날짜 설정 <<
			1. 년도 설정
			2. 월 설정 ( 1월 ~ 12월 안에 포함되어있으면, 아니면 에러)
			3. 일 설정 ( 1일 ~ 31일 안에 포함되어있으면, 아니면 에러)
																	*/

	if (isValidDate(newYear, newMonth, newDay))
	{
		year = newYear; month = newMonth; day = newDay;
	}
	else
	{
		cout << "illegal date value! Program aborted. \n";
		exit(1);
	}
}
int Date::getYearDay() const					// 이번 년도에서 지나간 날수 측정
{
	// 윤년일 때, 2월의 일수가 변화할 수 있기 때문에 상수로 지정하면 안됨
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;

	if (isLeapYear(this->Year()))				// 올해가 윤년인지 판단
		days_month[FEB] = 29;					// 2월의 일수는 29일이다.


	for (int m = JAN; m < this->Month(); m++)
	{
		yearDay += days_month[m];				// 1월부터 시작, 현재 달의 전까지 일을 더함
	}
	yearDay += this->Day();						// 이번달 1일에서 지나간 날수 더해줌

	return yearDay;								// 반환
}
int Date::getWeekDay() const					// 오늘이 무슨 요일인지 판별해주는 함수
{
	int weekDay_AD010101 = MON;						// 기준일 (1년 1월 1일)의 요일 = 월요일
	int weekDay;
	int elapsedDays = 0;							// 지나간 날수

	elapsedDays = this->getElapsedDays();			// 지나간 날수 구하는 함수

	// (기준일 + 지나간 날수) 에서 7을 나누고 남은 나머지를 통해 요일 판별
	weekDay = (weekDay_AD010101 + elapsedDays) % 7;

	return weekDay;									// 반환
}
int Date::getElapsedDays() const					// 지나간 날수 구하는 함수
{
	int yearDay;
	int elpsDay = 0;

	for (int y = 2; y < this->Year(); y++)			// 1년이 기준일이기 때문에 1년은 제외함
	{
		if (this->isLeapYear(y))							// y가 윤년일 때 하루 추가된 366일 추가
			elpsDay += 366;
		else
			elpsDay += 365;							// 아니면 기존처럼 365일
	}

	yearDay = this->getYearDay();					// 이번년도 1월 1일로부터 며칠이 떨어져 있는가 구함
	elpsDay += (yearDay - 1);						// yearDay에서 -1을 해야 오차가 안생김(이유 : 1년 1월 1일 계산시 yearDay가 1일로 계산됨)

	return elpsDay;									// 반환
}
void Date::printCalender_month()
{
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>" << this->Year() << "년" << this->Month() << "월<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	cout << "==================================================================" << endl;
	cout << "	일	월	화	수	목	금	토" << endl;
	cout << "==================================================================" << endl;

	if (isLeapYear(this->Year()))								// 올해가 윤년인지 판단
		days_month[FEB] = 29;									// 2월의 일수는 29일이다.

	for (int wd = 0; wd < this->getWeekDay(); wd++)				// 시작날까지 tap키로 건너뛰기
		cout << "\t";

	for (int d = 1; d <= days_month[month]; d++)				// 1일 부터 시작하여 그 달의 날수 까지 반복
	{
		if (d % 7 == 0)
			cout << "\n";										// 만약 일요일이면 한줄 내리기
		cout << "\t" << d;										// 아니면 정상 출력
		d++;													// days를 더해줘서 날수를 맞춘다.
	}

	cout << "\n==================================================================" << endl;
}

const Date& Date::operator=(const Date& rightSide)
{
	this->setDate(rightSide.Year(), rightSide.Month(), rightSide.Day());

	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}
bool Date::operator>(const Date& rightSide)
{
	if (this->getElapsedDays() > rightSide.getElapsedDays())
		return true;
	else
		return false;
}
bool Date::operator<(const Date& rightSide)
{
	if (this->getElapsedDays() < rightSide.getElapsedDays())
		return true;
	else
		return false;
}
bool Date::operator==(const Date& rightSide)
{
	if (this->getElapsedDays() == rightSide.getElapsedDays())
		return true;
	else
		return false;
}
bool Date::operator!=(const Date& rightSide)
{
	if (this->getElapsedDays() != rightSide.getElapsedDays())
		return true;
	else
		return false;
}
bool Date::isLeapYear(int y) const					// check whether the year is leap year
{
	if ((y % 100 == 0) && (y % 4) == 0 && (y % 400 != 0))
		// 올해가 4, 100으로 나누어 떨어지고, 400으로 나누어 떨어지지 않는가
		return true;
	else
		return false;
}

bool Date::isValidDate(int y, int m, int d)			// 이 날짜가 유효한 날짜인가 판별하는 함수
{

	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (isLeapYear(y))										// 올해가 윤년인지 판단
		days_month[FEB] = 29;								// 2월의 일수는 29일이다. 

	// 월이 1 ~ 12, 일이 1 ~ 31 사이에 들어있는 값이 맞나? 판별
	if ((y >= 1) && ((m >= 1) && (m <= 12)) && ((d >= 1) && (d <= days_month[m])))
		return true;
	else
	{	// 아니면 false
		return false;
	}
}
bool Date::isLeapYear()
{
	if ((year % 100 == 0) && (year % 4) == 0 && (year % 400 != 0))
		// 올해가 4, 100으로 나누어 떨어지고, 400으로 나누어 떨어지지 않는가
		return true;
	else
		return false;
}



