#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

#define WEEKDATY_AD01JAN01 MON					// 1�� 1�� 1���� �������̴�
#define MONTHS_YEAR 12							// 1�� �� �� : 12
#define DAYS_P_WEEK 7							// �������� 7��
#define Secs_in_Minute 60						// 1�� = 60��
#define Secs_in_Hour (Secs_in_Minute * 60)		// 1�ð� = 60�� * 60�� = 3600��
#define Secs_in_DAY (Secs_in_Hour* 24)			// 1�� = 24�ð� * 60�� * 60�� = 86400��
#define LOCAL_GMT_OFFSET_HOUR 9					// �ѱ��� ǥ�ؽ� ���� 9�ð� ���� (GMT +9H)

class Date
{
	friend istream& operator>>(istream& input, Date&);				// ��¥ �ϴ� ������ �����ε�
	friend ostream& operator<<(ostream& output, const Date&);		// ��¥ ��� ������ �����ε�

public:
	Date();										// default constructor (�⺻ ������), __init__ 
	Date(int y, int m, int d);					// constructor (������)

	// ������ ��� ������ (mutator)
	void setDate(int newYear, int newMonth, int newDay);			// ��¥ �����ϴ� �Լ�

	// ������ ��� ������ (accessor)
	int Year() const { return year; }
	int Month() const { return month; }			// ���������� ���� ( 1��, 2�� ..)
	int Day() const { return day; }
	int getYearDay() const;
	int getWeekDay() const;
	int getElapsedDays() const;				// 1�� 1�� 1�� ���� ��ĥ �������ִ��� ����ϴ� �Լ�
	void printCalender_month();				// �޷� ��� �Լ�

	// ������ ���۷����� ( ����, �ο� ��� )
	const Date& operator= (const Date& rightSide);
	bool operator> (const Date& rightSide);
	bool operator< (const Date& rightSide);
	bool operator>= (const Date& rightSide);
	bool operator<= (const Date& rightSide);
	bool operator== (const Date& rightSide);
	bool operator!= (const Date& rightSide);
	bool isLeapYear(int y) const;

private:
	bool isLeapYear();										// check whether the year is leap year
	bool isValidDate(int y, int m, int d); 				// check Valid Date 
	int year;												// privite ���� year, month, day
	int month;
	int day;
};

Date genRandDate();
bool isLeapYear(int y);

#endif // !DATE_H	