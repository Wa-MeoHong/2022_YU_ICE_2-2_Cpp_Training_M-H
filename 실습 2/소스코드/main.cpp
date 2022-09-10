/*
  ���ϸ� : "�ǽ�2_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- Class Date, Class Person�� �����Ͽ�, ũ���������� ��¥�� �� ���̳����� ���ϴ� ���α׷�
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 9�� 8��)
  ���� Update : Version 1.0.0, 2022�� 9�� 8�� (�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������		   ������		 ����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
   �Ŵ�ȫ		 2022/09/08		v1.0.0		  �����ۼ�
   �Ŵ�ȫ		 2022/09/11		v1.0.1		  �ϼ�
===========================================================================================================
*/

#pragma warning(disable: 4996)					// ���� �ȶ߰� �ϴ� pragma����
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

	/*			��Ʈ 1 : Class Date			*/

	Date AD010101(1, 1, 1);
	int year, month, day;
	int daysToChristmas;
	time_t currentTime;
	struct tm* time_and_date;		// ���� ��¥�� �������� ���� ����ü tm

	time(&currentTime);
	time_and_date = localtime(&currentTime);			// ���� ��¥�� �ð��� ������
	year = time_and_date->tm_year + 1900;				// ������ �����Ϳ� ǥ���� �����Ͱ� �޶� �°� ����
	month = time_and_date->tm_mon + 1;					// 1900���� 0������ ����, 1���� 0���� ������
	day = time_and_date->tm_mday;
	Date newYearDay(year, 1, 1), today(year, month, day), christmas(year, 12, 25);	// ��ü ����

	// ��� ( 1�� 1�� 1��, ���� ��¥, ũ�������� ��, ũ������������ ���� ��¥�� ��� ) 
	fout << "AD Jan. 1, 1 is"; AD010101.fprintDate(fout); fout << endl;
	fout << "Today is "; today.fprintDate(fout); fout << endl;
	fout << "New year's day of this year was "; newYearDay.fprintDate(fout); fout << endl;
	fout << "Christmas of this year is "; christmas.fprintDate(fout); fout << endl;

	if (today.getMonth() == christmas.getMonth() && today.getDay() == christmas.getDay())
	{
		fout << "Today is Christmas! Happy Christmas to you all !!" << endl;			// ���ϸ޼��� ���
	}
	// �ƴϸ�
	else
	{
		// ũ������������ ��ĥ�� ���Ҵ��� ���
		daysToChristmas = christmas.getElapsedDaysFromAD010101() 
			- today.getElapsedDaysFromAD010101();
		fout << "Sorry, today is not Christmas!\n";
		fout << "You must wait " << daysToChristmas << " day(s) to Christmas !" << endl;
	}
	fout << endl;

	/*			��Ʈ 2 : Class Person			*/

	srand((unsigned int)time(NULL));								// ���� �õ� ����
	
	/*			������ ��� 2���� Ŭ���� ��ü�� ���� ��, ���			*/
	Person p1(string("Hong, Gil-Dong"), Date(2000, 1, 1)),
		p2(string("Lee, Soo - Jeong"), Date(2018, 9, 1));
				// ���
	fout << "Person p1 : " << endl; p1.fprintPerson(fout); fout << endl;
	fout << "Person p2 : " << endl; p2.fprintPerson(fout); fout << endl;

	/*			������ ��� n���� Ŭ���� ��ü�� �����Ҵ����� ���� ��, ���			*/
	fout << endl << "Generating array of persons ... " << endl;
	Person* persons;												// Ŭ���� ������(�迭) �Ҵ�
	persons = (Person*) new Person[NUM_PERSON];						// �����Ҵ��� (10����ŭ �迭 �Ҵ�)
	for (int i = 0; i < NUM_PERSON; i++)
	{
		persons[i].setRandPersonAttribute();						// �������� ����� ����
		persons[i].fprintPerson(fout);								// �ٷιٷ� ���
		fout << endl;
	}
	fout << endl;

	delete[] persons;												// �� ���� ��, ��ȯ (free())
	fout.close();													// ���ϴݱ�
	return 0;
}

