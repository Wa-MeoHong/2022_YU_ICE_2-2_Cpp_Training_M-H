#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

using namespace std;

class Student : public Person
{
	friend ostream& operator<< (ostream& ostr, const Student&);
public:
	Student();
	Student(int s_id, string n, int age, string country, double GPA);

	// member function
	void getKey(string KeyName, void* pKey);

	// getter 
	int ST_ID() const { return st_id; }
	double GPA() const { return gpa; }

	// setter
	void set_ST_id(int stid) { st_id = stid; }
	void set_GPA(double GPa) { gpa = GPa; }

	// operator overloading
	bool operator<(const Student& other) const { return (this->ST_ID() < other.ST_ID()); }
	bool operator<=(const Student& other) const { return (this->ST_ID() <= other.ST_ID()); }
	bool operator>(const Student& other) const { return (this->ST_ID() > other.ST_ID()); }
	bool operator>=(const Student& other) const { return (this->ST_ID() >= other.ST_ID()); }
	bool operator==(const Student& other) const { return (this->ST_ID() == other.ST_ID()); }


private:
	int st_id;
	double gpa;
};


#endif // !STUDENT_H


