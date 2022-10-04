#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include "Person.h"

using namespace std;

class StudentArray;

class Student : public Person					// Person 클래스를 상속받음
{
	friend class StudentArray;					// StudentArray 클래스를 friend로 받음
	// 출력 연산자 오버로딩
	friend ostream& operator<< (ostream& out, const Student&);

public:
	// 생성자 ( 기본, id, 모든 값 )
	Student();
	Student(int id);
	Student(int id, string n, Date dob, string dept_n, double GPA);
	// getter 
	int ST_ID() const { return st_id; }
	string Dept_Name() const { return dept_name; }
	Date BirthDate() const { return birthDate; }
	double GPA() const { return gpa; }

	// setter
	void SetST_ID(int id) { st_id = id; }
	void SetDept(string dp_n) { dept_name = dp_n; }
	void SetGPA(double g) { gpa = g; }

	// 연산자 오버로딩 ( 대입, 비교 ) 
	const Student& operator=(const Student& right);
	bool operator>(const Student& right) const;
	bool operator== (const Student& right) const;

private:
	int st_id;
	string dept_name;
	double gpa;
};

Student genRandStudent(int id);							// 학생 데이터 랜덤으로 생성
void genST_ids(int num_students, int* st_ids);			//  학번 데이터 랜덤 생성
#endif