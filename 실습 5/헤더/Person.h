#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <iomanip>
#include "Mystring.h"
#include "Date.h"

class Person
{
	// Person 객체 출력 연산자 오버로드
	friend ostream& operator<< (ostream& output, const Person&);

public:
	Person();													// constructor (생성자)
	Person(string nm, Date bd) { birthDate = bd; name = nm; }	// constructor 2 ( 이름, 생일이 있는경우)

	// setter ( 설정자 ) 
	void nameSetting(string n) { name = n; }
	void BirthSetting(Date bd) { birthDate = bd; }

	// getter ( 반환자, const 변수가 사용가능 ) 
	string Name() const { return name; }
	Date Birth() const { return birthDate; }

protected:
	string name;
	Date birthDate;
};


#endif 