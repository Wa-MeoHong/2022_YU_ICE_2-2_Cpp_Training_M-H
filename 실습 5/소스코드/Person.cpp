#include "Person.h"

// 출력 연산자 오버로딩
ostream& operator<<(ostream& output, const Person& h)
{
	output << "Name : " << setw(8) << h.Name();				// 이름 출력
	output << ", BirthDate : " << h.Birth();				// 생일 출력

	return output;											// ostream 변수 output 반환
}

Person::Person()										// person 클래스 생성자
{
	name = "";
	birthDate = Date(1, 1, 1);
}