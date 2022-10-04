#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <iomanip>
#include "Mystring.h"
#include "Date.h"

class Person
{
	// Person ��ü ��� ������ �����ε�
	friend ostream& operator<< (ostream& output, const Person&);

public:
	Person();													// constructor (������)
	Person(string nm, Date bd) { birthDate = bd; name = nm; }	// constructor 2 ( �̸�, ������ �ִ°��)

	// setter ( ������ ) 
	void nameSetting(string n) { name = n; }
	void BirthSetting(Date bd) { birthDate = bd; }

	// getter ( ��ȯ��, const ������ ��밡�� ) 
	string Name() const { return name; }
	Date Birth() const { return birthDate; }

protected:
	string name;
	Date birthDate;
};


#endif 