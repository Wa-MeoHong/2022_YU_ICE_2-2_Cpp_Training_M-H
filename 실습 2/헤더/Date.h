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
public:
	Date();										// default constructor (�⺻ ������), __init__ 
	Date(int y, int m, int d);					// constructor (������)
	~Date();									// destructor (�Ҹ���)
	void inputDate();							// ��¥ input �ϴ� �Լ�
	void printDate();							// ��¥ ����ϴ� �Լ�
	void fprintDate(ostream& fout);				// ��¥ ��������� �Լ�
	void fprintCalender_month(ostream& fout);	// �޷� ��� �Լ�

	// ������ ��� ������ (mutator)
	void setDate(int y, int m, int dy);			// ��¥ �����ϴ� �Լ�
	void setMonth(int m);
	void setYear(int y);
	void setRandDateAttributes();

	// ������ ��� ������ (accessor)
	int getYear() { return year; }
	int getMonth() { return month; }			// ���������� ���� ( 1��, 2�� ..)
	int getDay() { return day; }
	int getYearDay();
	int getYearDay(int m, int d);
	int getWeekDay();
	int getElapsedDaysFromAD010101();			// 1�� 1�� 1�� ���� ��ĥ �������ִ��� ����ϴ� �Լ�
	int getElapsedDaysFromAD010101(Date);


private:
	bool isLeapYear();							// check whether the year is leap year
	bool isLeapYear(int y);
	bool isValidDate(int y, int m, int d);
	int year;									// privite ���� year, month, day
	int month;
	int day;
};

#endif // !DATE_H