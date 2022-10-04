#ifndef STUDENTARRAY_H
#define STUDENTARRAY_H

#include "Student.h"									// Student 클래스 들고옴
#include "Person.h"										// Person 클래스도 들고온다.

using namespace std;

class StudentArray
{
	// 연산자 오버로딩 << (출력)
	friend ostream& operator<< (ostream& out, const StudentArray&);
public:
	// constructor (생성자)
	StudentArray(int size);
	StudentArray(const StudentArray& obj);
	
	// destructor ( 소멸자 ) 
	~StudentArray();
	int SIZE() const { return num_students; }			// 사이즈 반환
	Student& operator[](int sub);						// 배열 인덱스의 값 반환
	
	/*				선택 정렬 함수들
			1. 생일 기준
			2. 이름 기준
			3. 학번 기준
			4. GPA(학점) 기준
			5. 선택에 따라 기준이 바뀜
	*/
	void sortByBirthDate();
	void sortByName();
	void sortByST_ID();
	void sortByGPA();
	void SelectSort( int sel );

private:
	Student* students;									// 학생 배열
	int num_students;									// 학생 수
	bool isValidIndex(int index) const;					// 배열의 인덱스 번호 유효성 검사
};

#endif 