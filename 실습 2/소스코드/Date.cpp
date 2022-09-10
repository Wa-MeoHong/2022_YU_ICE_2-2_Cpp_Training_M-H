#include "Date.h"
#include <iostream>
#include <iomanip>
#include <string>

// ������ �ڷ��� enum ����, enum �� �̸� 
enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT };
enum MONTHS { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
// ���ڿ� ��� �迭�� ( ���� �̸�, �� �̸� )
const char* WeekDayName[DAYS_P_WEEK] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const char* MonthName[MONTHS_YEAR + 1] = { "", "January", "February", "March", "April",
	"May", "June", "July", "August", "September", "October", "November", "December" };

// init Date ( ��¥ �ʱⰪ ���� �� �Է� ) 
Date::Date()						// Date Ŭ���� �ʱ��� ����
{
	year = 0; month = 0; day = 0;
}
Date::Date(int y, int m, int d)		// Date Ŭ���� �Է°��� ���� �ʱⰪ ����
{
	setDate(y, m, d);
}
Date::~Date()						// Date Ŭ���� ��ü�� �Ҹ��Ҷ� �۵���
{
	// cout << "Date object instance is destructed" << endl;
	// delete();
}

/*					>> ��¥ ����� �Լ� <<
	1. ��¥�� �Է��ϴ� �Լ�, �� ��¥�� ��ȿ�� ��¥������ �˻�
	2. �Էµ� ��¥�� ������Ŀ� �°� ������ִ� �Լ�
														*/
void Date::inputDate()							// ��¥ �Է��Լ�
{
	int y, m, d;

	// ��¥ �Է� ( scanf ���� �� )
	cout << "Enter date in year month day : ";
	cin >> y >> m >> d;

	// ��ȿ�� ��¥���� �˻�
	if (isValidDate(y, m, d))					// ��ȿ�� ��¥��� ���� �Է�
	{
		year = y;
		month = m;
		day = d;
	}
	else
	{											// ��ȿ���� ���� ��¥�� �����޼��� ���
		cout << "illegal Date! Program aborted. \n";
		exit(1);
	}
}
void Date::printDate()							// ��¥ ����Լ�
{
	// 1. ���� �̸��� ���� ���ڿ� ��� �迭
	// 2. �� �̸��� ���� ���ڿ� ��� �迭
	int yearDay = 0;
	int weekday = 0;

	// ���� ���� �����. string�� �̿��� ���ڿ� ���
	if ((month >= 1) && (month <= 12))
		cout << right << setw(10) << string(MonthName[month]);
	cout << " " << setw(2) << day << ", " << setw(4) << year;

	// ������ ���ϱ� ���� weekday()�� ����
	yearDay = getYearDay();
	weekday = getWeekDay();
	cout << "(" << setw(10) << string(WeekDayName[weekday]) << ")";
}

void Date::fprintDate(ostream& fout)			// ��¥ ���� ��� �Լ�
{
	// 1. ���� �̸��� ���� ���ڿ� ��� �迭
	// 2. �� �̸��� ���� ���ڿ� ��� �迭
	
	int yearDay = 0;
	int weekday = 0;

	// ���� ���� �����. string�� �̿��� ���ڿ� ���
	if ((month >= 1) && (month <= 12))
		fout << right << setw(10) << string(MonthName[month]);
	fout << " " << setw(2) << day << ", " << setw(4) << year;

	// ������ ���ϱ� ���� weekday()�� ����
	yearDay = getYearDay();
	weekday = getWeekDay();
	fout << "(" << setw(10) << string(WeekDayName[weekday]) << ")";
}

void Date::fprintCalender_month(ostream& fout)
{
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	fout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>" <<  year << "��" << month << "��<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	fout << "==================================================================" << endl;
	fout << "	��	��	ȭ	��	��	��	��" << endl;
	fout << "==================================================================" << endl;

	if (isLeapYear())											// ���ذ� �������� �Ǵ�
		days_month[FEB] = 29;									// 2���� �ϼ��� 29���̴�.

	for (int wd = 0; wd < (day % 7); wd++)						// ���۳����� tapŰ�� �ǳʶٱ�
		fout << "\t";

	for (int d = 1; d <= days_month[month]; d++)				// 1�� ���� �����Ͽ� �� ���� ���� ���� �ݺ�
	{
		if (day % 7 == 0)
			fout << "\n   ";									// ���� �Ͽ����̸� ���� ������
		fout << "\t" << d;										// �ƴϸ� ���� ���
		day++;													// days�� �����༭ ������ �����.
	}
	printf("\n==================================================================\n");
}

void Date::setDate(int y, int m, int d)				// ��¥ �����ϴ� �Լ�
{
	/*							>> ��¥ ���� <<
			1. �⵵ ����
			2. �� ���� ( 1�� ~ 12�� �ȿ� ���ԵǾ�������, �ƴϸ� ����)
			3. �� ���� ( 1�� ~ 31�� �ȿ� ���ԵǾ�������, �ƴϸ� ����)
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
void Date::setMonth(int m)						// �� �����ϴ� �Լ�
{
	// 1��~12�� �ȿ� �ִ� ��¥�� ���. �ƴϸ� �����޼��� ���
	if ((m >= 1) && (m <= 12))
		month = m;
	else
	{
		cout << "illegal month value! Program aborted. \n";
		exit(1);
	}
	day = 1;
}
void Date::setYear(int y)						// �� �����ϴ� �Լ�
{
	// ����� �⵵�� ���Խ�Ű�� �ʴ´�. ���� 1�� �̻��� �⵵�� ���
	if (y >= 1)
		year = y;
	else
	{	// ���Ե��� �ʴ� �⵵ �Է½� �����޼��� ���
		cout << "illegal year value! Program aborted. \n";
		exit(1);
	}
}
void Date::setRandDateAttributes()
{
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	year = rand() % 122 + 1900;					// ���� �⵵�� 2022���̹Ƿ� �ִ� �⵵�� 2022���� �ѱ��� �ʰ� ��
	month = rand() % 12 + 1;					// 1������ �����̹Ƿ�
	if (isLeapYear())											// ���ذ� �������� �Ǵ�
		days_month[FEB] = 29;									// 2���� �ϼ��� 29���̴�.
	day = rand() % days_month[month] + 1;		// 1�Ϻ��� ����
}
/*					>> ������ �� ��, ���� ���� <<
		1. �̹��⵵ 1�� 1�� ���� ���� ��¥���� ��ĥ�� ���������� �����ϴ� �Լ�
		2. ������ ������ ���� ���� ��ȯ�Ͽ� �˾Ƴ��� �Լ�
*/
int Date::getYearDay()							// �̹� �⵵���� ������ ���� ����
{
	// ������ ��, 2���� �ϼ��� ��ȭ�� �� �ֱ� ������ ����� �����ϸ� �ȵ�
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;

	if (isLeapYear())							// ���ذ� �������� �Ǵ�
		days_month[FEB] = 29;					// 2���� �ϼ��� 29���̴�.

	// 1������ ����, ���� ���� ������ ���� ����
	for (int m = JAN; m < month; m++)
	{
		yearDay += days_month[m];
	}
	yearDay += day;								// �̹��� 1�Ͽ��� ������ ���� ������

	return yearDay;								// ��ȯ
}
int Date::getYearDay(int m, int d)				// ���� ����, �Ű������� ���� ���� �޾ƿ��°͸� �ٸ�
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
int Date::getWeekDay()								// ������ ���� �������� �Ǻ����ִ� �Լ�
{
	int weekDay_AD010101 = MON;						// ������ (1�� 1�� 1��)�� ���� = ������
	int weekDay;
	int elapsedDays = 0;							// ������ ����

	elapsedDays = getElapsedDaysFromAD010101();		// ������ ���� ���ϴ� �Լ�

	// (������ + ������ ����) ���� 7�� ������ ���� �������� ���� ���� �Ǻ�
	weekDay = (weekDay_AD010101 + elapsedDays) % 7;

	return weekDay;									// ��ȯ
}
/*						>> ������ ���� ���ϴ� �Լ� <<
		1. ������ (1�� 1�� 1��)�κ��� ��ĥ�� �������� �˾Ƴ��� �Լ�
																		*/
int Date::getElapsedDaysFromAD010101()				// ������ ���� ���ϴ� �Լ�
{
	int yearDay;
	int elpsDay = 0;

	for (int y = 2; y < year; y++)					// 1���� �������̱� ������ 1���� ������
	{
		if (isLeapYear(y))							// y�� ������ �� �Ϸ� �߰��� 366�� �߰�
			elpsDay += 366;
		else
			elpsDay += 365;							// �ƴϸ� ����ó�� 365��
	}

	yearDay = getYearDay();							// �̹��⵵ 1�� 1�Ϸκ��� ��ĥ�� ������ �ִ°� ����
	elpsDay += (yearDay - 1);						// yearDay���� -1�� �ؾ� ������ �Ȼ���(���� : 1�� 1�� 1�� ���� yearDay�� 1�Ϸ� ����)

	return elpsDay;									// ��ȯ
}
int Date::getElapsedDaysFromAD010101(Date today)	// ����, �Ű������� ���� �޾ƿͼ� getyear���� ����ؼ� ���� ������
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

/*								>> ���� �Ǵ��ϴ� �Լ� <<
		1. ���ذ� �������� �Ǵ��ϴ� �Լ�
		2. ���ذ� 4, 100���� ������ ����������, 400���� ������ �������� �ʴ� �� = ����
															*/
bool Date::isLeapYear()
{
	if ((year % 100 == 0) && (year % 4) == 0 && (year % 400 != 0))
		// ���ذ� 4, 100���� ������ ��������, 400���� ������ �������� �ʴ°�
		return true;
	else
		return false;
}
bool Date::isLeapYear(int y)		// ���� ����
{
	if ((y % 100 == 0) && (y % 4) == 0 && (y % 400 != 0))
		return true;
	else
		return false;
}

bool Date::isValidDate(int y, int m, int d)				// �� ��¥�� ��ȿ�� ��¥�ΰ� �Ǻ��ϴ� �Լ�
{
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (isLeapYear())							// ���ذ� �������� �Ǵ�
		days_month[FEB] = 29;					// 2���� �ϼ��� 29���̴�. 

	// ���� 1 ~ 12, ���� 1 ~ 31 ���̿� ����ִ� ���� �³�? �Ǻ�
	if (((m >= 1) && (m <= 12)) && ((d >= 1) && (d <= days_month[m])))
		return true;
	else
	{	// �ƴϸ� ���� �����޼��� ���
		cout << "illegal date! (" << m << ", " << d << ") ==> Program aborted.\n";
		return false;
	}
}