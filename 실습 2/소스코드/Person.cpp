#include "Person.h"

void Person::setRandPersonAttribute()				// 사람 랜덤으로 속성 생성
{
	char names[MAX_NAME_LEN + 1];					// 이름을 담는 배열
	int name_len;

	birthDate.setRandDateAttributes();				// 날짜 랜덤해서 생성
	// 이름 랜덤 생성
	name_len = rand() % (MAX_NAME_LEN - MIN_NAME_LEN) + MIN_NAME_LEN;
	for (int i = 0; i < name_len; i++)
		names[i] = rand() % 26 + 'a';				// rand()한 후, 26(알파벳 개수)를 나눈 나머지 + 아스키코드 'a'
	names[name_len] = '\0';							// 마지막 NULL 문자 삽입

	name = string(names);							// 배열을 문자열화 한 후, 저장
}


//	Person 데이터 출력 함수
void Person::fprintPerson(ostream& fout)
{
	fout << "Person [ name: ";							// 이름 출력
	fout.setf(ios::left); fout << setw(16) << name;		// 이름은 왼쪽 정렬 후, 칸은 16칸으로 설정)
	fout.unsetf(ios::left); fout << ", birth date: ";	// 생년월일은 오른쪽 정렬 후, 미리 만든 함수로 출력
	birthDate.fprintDate(fout); fout << "]";
}