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


istream& operator>>(istream& input, Date& D)
{
	int y, m, d;

	// ��¥ �Է� ( scanf ���� �� )
	cout << "Enter date in year month day : ";
	input >> y >> m >> d;

	// ��ȿ�� ��¥���� �˻�
	if (D.isValidDate(y, m, d))					// ��ȿ�� ��¥��� ���� �Է�
	{
		D.year = y;
		D.month = m;
		D.day = d;
	}
	else
	{												// ��ȿ���� ���� ��¥�� �����޼��� ���
		cout << "illegal date! (" << m << ", " << d << ") ==> Program aborted.\n";
		exit(1);
	}

	return input;
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& output, const Date& D)
{
	output << "(" << setw(4) << D.Year() << "-"
		<< setw(2) << D.Month() << "-" << setw(2) << D.Day() << ")";

	return output;
	// TODO: ���⿡ return ���� �����մϴ�.
}

Date genRandDate()
{
	Date temp(1, 1, 1);
	int year, month, day;
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	year = rand() % 100 + 2000;					// 2000 ~  2999�� ������ ���� ���
	if (isLeapYear(year))						// ���ذ� �������� �Ǵ�
		days_month[FEB] = 29;					// 2���� �ϼ��� 29���̴�.

	month = rand() % 12 + 1;					// 1������ �����̹Ƿ�
	day = rand() % days_month[month] + 1;		// 1�Ϻ��� ����

	temp.setDate(year, month, day);

	return temp;
}
bool isLeapYear(int y)
{
	if ((y % 100 == 0) && (y % 4) == 0 && (y % 400 != 0))
		// ���ذ� 4, 100���� ������ ��������, 400���� ������ �������� �ʴ°�
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
	/*							>> ��¥ ���� <<
			1. �⵵ ����
			2. �� ���� ( 1�� ~ 12�� �ȿ� ���ԵǾ�������, �ƴϸ� ����)
			3. �� ���� ( 1�� ~ 31�� �ȿ� ���ԵǾ�������, �ƴϸ� ����)
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
int Date::getYearDay() const					// �̹� �⵵���� ������ ���� ����
{
	// ������ ��, 2���� �ϼ��� ��ȭ�� �� �ֱ� ������ ����� �����ϸ� �ȵ�
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;

	if (isLeapYear(this->Year()))				// ���ذ� �������� �Ǵ�
		days_month[FEB] = 29;					// 2���� �ϼ��� 29���̴�.


	for (int m = JAN; m < this->Month(); m++)
	{
		yearDay += days_month[m];				// 1������ ����, ���� ���� ������ ���� ����
	}
	yearDay += this->Day();						// �̹��� 1�Ͽ��� ������ ���� ������

	return yearDay;								// ��ȯ
}
int Date::getWeekDay() const					// ������ ���� �������� �Ǻ����ִ� �Լ�
{
	int weekDay_AD010101 = MON;						// ������ (1�� 1�� 1��)�� ���� = ������
	int weekDay;
	int elapsedDays = 0;							// ������ ����

	elapsedDays = this->getElapsedDays();			// ������ ���� ���ϴ� �Լ�

	// (������ + ������ ����) ���� 7�� ������ ���� �������� ���� ���� �Ǻ�
	weekDay = (weekDay_AD010101 + elapsedDays) % 7;

	return weekDay;									// ��ȯ
}
int Date::getElapsedDays() const					// ������ ���� ���ϴ� �Լ�
{
	int yearDay;
	int elpsDay = 0;

	for (int y = 2; y < this->Year(); y++)			// 1���� �������̱� ������ 1���� ������
	{
		if (this->isLeapYear(y))							// y�� ������ �� �Ϸ� �߰��� 366�� �߰�
			elpsDay += 366;
		else
			elpsDay += 365;							// �ƴϸ� ����ó�� 365��
	}

	yearDay = this->getYearDay();					// �̹��⵵ 1�� 1�Ϸκ��� ��ĥ�� ������ �ִ°� ����
	elpsDay += (yearDay - 1);						// yearDay���� -1�� �ؾ� ������ �Ȼ���(���� : 1�� 1�� 1�� ���� yearDay�� 1�Ϸ� ����)

	return elpsDay;									// ��ȯ
}
void Date::printCalender_month()
{
	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>" << this->Year() << "��" << this->Month() << "��<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	cout << "==================================================================" << endl;
	cout << "	��	��	ȭ	��	��	��	��" << endl;
	cout << "==================================================================" << endl;

	if (isLeapYear(this->Year()))								// ���ذ� �������� �Ǵ�
		days_month[FEB] = 29;									// 2���� �ϼ��� 29���̴�.

	for (int wd = 0; wd < this->getWeekDay(); wd++)				// ���۳����� tapŰ�� �ǳʶٱ�
		cout << "\t";

	for (int d = 1; d <= days_month[month]; d++)				// 1�� ���� �����Ͽ� �� ���� ���� ���� �ݺ�
	{
		if (d % 7 == 0)
			cout << "\n";										// ���� �Ͽ����̸� ���� ������
		cout << "\t" << d;										// �ƴϸ� ���� ���
		d++;													// days�� �����༭ ������ �����.
	}

	cout << "\n==================================================================" << endl;
}

const Date& Date::operator=(const Date& rightSide)
{
	this->setDate(rightSide.Year(), rightSide.Month(), rightSide.Day());

	return *this;
	// TODO: ���⿡ return ���� �����մϴ�.
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
		// ���ذ� 4, 100���� ������ ��������, 400���� ������ �������� �ʴ°�
		return true;
	else
		return false;
}

bool Date::isValidDate(int y, int m, int d)			// �� ��¥�� ��ȿ�� ��¥�ΰ� �Ǻ��ϴ� �Լ�
{

	int days_month[MONTHS_YEAR + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (isLeapYear(y))										// ���ذ� �������� �Ǵ�
		days_month[FEB] = 29;								// 2���� �ϼ��� 29���̴�. 

	// ���� 1 ~ 12, ���� 1 ~ 31 ���̿� ����ִ� ���� �³�? �Ǻ�
	if ((y >= 1) && ((m >= 1) && (m <= 12)) && ((d >= 1) && (d <= days_month[m])))
		return true;
	else
	{	// �ƴϸ� false
		return false;
	}
}
bool Date::isLeapYear()
{
	if ((year % 100 == 0) && (year % 4) == 0 && (year % 400 != 0))
		// ���ذ� 4, 100���� ������ ��������, 400���� ������ �������� �ʴ°�
		return true;
	else
		return false;
}



