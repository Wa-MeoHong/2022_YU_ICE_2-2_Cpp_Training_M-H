#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include "Person.h"

using namespace std;

class StudentArray;

class Student : public Person					// Person Ŭ������ ��ӹ���
{
	friend class StudentArray;					// StudentArray Ŭ������ friend�� ����
	// ��� ������ �����ε�
	friend ostream& operator<< (ostream& out, const Student&);

public:
	// ������ ( �⺻, id, ��� �� )
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

	// ������ �����ε� ( ����, �� ) 
	const Student& operator=(const Student& right);
	bool operator>(const Student& right) const;
	bool operator== (const Student& right) const;

private:
	int st_id;
	string dept_name;
	double gpa;
};

Student genRandStudent(int id);							// �л� ������ �������� ����
void genST_ids(int num_students, int* st_ids);			//  �й� ������ ���� ����
#endif