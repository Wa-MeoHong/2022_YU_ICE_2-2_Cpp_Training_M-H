#ifndef PERSON_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "Date.h"
using namespace std;

#define MAX_NAME_LEN 15					// 이름 최대 길이
#define MIN_NAME_LEN 5					// 이름 최소 길이

/*			클래스 Person			
	public:
		Person() : 클래스 초기 함수
		setName() : 이름을 설정해줌, 이름 입력
		setbirthDate() : 생년월일 설정 및 입력
		setRandOPersonAttribute() : 이름, 생년월일을 생성 후, 사람 데이터 작성
		getName() : 이름 반환
		getBirthDate() : 생년월일 반환
		fprintPerson(ostream&) : 사람 데이터 출력
	private:
		birthDate : Date클래스 객체 변수
		name : string 객체 변수(문자열)
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