#include "Person.h"

// ��� ������ �����ε�
ostream& operator<<(ostream& output, const Person& h)
{
	output << "Name : " << setw(8) << h.Name();				// �̸� ���
	output << ", BirthDate : " << h.Birth();				// ���� ���

	return output;											// ostream ���� output ��ȯ
}

Person::Person()										// person Ŭ���� ������
{
	name = "";
	birthDate = Date(1, 1, 1);
}