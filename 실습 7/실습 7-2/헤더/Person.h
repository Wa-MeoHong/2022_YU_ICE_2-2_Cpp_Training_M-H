#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Person
{
	friend ostream operator<< (ostream&, Person&);
public:
	// constructor
	Person() : regID(0), nation(" ") { name = "nobody"; }				// 기본 디폴트 생성자
	Person(string n) : regID(0), nation(" ") { name = n; }				// 이름을 인자로 받은 생성자

	// getter 
	string Name() const { return name; }				// 이름
	int RegID() const { return regID; }				// 주민번호
	string Nat() const { return nation; }				// 국가

	// setter
	void set_Name(string n) { name = n; }		// 이름 설정
	void set_regID(int id) { regID = id; }		// 주민번호 설정
	void set_Nation(string country) { nation = country; }	// 나라 설정


protected:
	string name;						// 이름
	int regID;							// 주민번호
	string nation;						// 국가
};

#endif // !PERSON_H
