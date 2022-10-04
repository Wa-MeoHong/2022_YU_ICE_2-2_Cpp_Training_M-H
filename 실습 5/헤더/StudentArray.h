#ifndef STUDENTARRAY_H
#define STUDENTARRAY_H

#include "Student.h"									// Student Ŭ���� ����
#include "Person.h"										// Person Ŭ������ ���´�.

using namespace std;

class StudentArray
{
	// ������ �����ε� << (���)
	friend ostream& operator<< (ostream& out, const StudentArray&);
public:
	// constructor (������)
	StudentArray(int size);
	StudentArray(const StudentArray& obj);
	
	// destructor ( �Ҹ��� ) 
	~StudentArray();
	int SIZE() const { return num_students; }			// ������ ��ȯ
	Student& operator[](int sub);						// �迭 �ε����� �� ��ȯ
	
	/*				���� ���� �Լ���
			1. ���� ����
			2. �̸� ����
			3. �й� ����
			4. GPA(����) ����
			5. ���ÿ� ���� ������ �ٲ�
	*/
	void sortByBirthDate();
	void sortByName();
	void sortByST_ID();
	void sortByGPA();
	void SelectSort( int sel );

private:
	Student* students;									// �л� �迭
	int num_students;									// �л� ��
	bool isValidIndex(int index) const;					// �迭�� �ε��� ��ȣ ��ȿ�� �˻�
};

#endif 