#ifndef PERSON_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "Date.h"
using namespace std;

#define MAX_NAME_LEN 15					// �̸� �ִ� ����
#define MIN_NAME_LEN 5					// �̸� �ּ� ����

/*			Ŭ���� Person			
	public:
		Person() : Ŭ���� �ʱ� �Լ�
		setName() : �̸��� ��������, �̸� �Է�
		setbirthDate() : ������� ���� �� �Է�
		setRandOPersonAttribute() : �̸�, ��������� ���� ��, ��� ������ �ۼ�
		getName() : �̸� ��ȯ
		getBirthDate() : ������� ��ȯ
		fprintPerson(ostream&) : ��� ������ ���
	private:
		birthDate : DateŬ���� ��ü ����
		name : string ��ü ����(���ڿ�)
*/

class Person
{
public:
	Person() : name(string("nobody")), birthDate(Date(1, 1, 1)) { }
	Person(string n, Date bd) : name(n), birthDate(bd) {}

	void setName(string n) { name = n; }
	void setbirthDate(Date bd) { birthDate = bd; }

	void setRandPersonAttribute();
	string getName() { return name; }
	Date getBirthDate() { return birthDate; }

	void fprintPerson(ostream& fout);

private:
	Date birthDate;
	string name;
};

#endif