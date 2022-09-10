#include "Person.h"

void Person::setRandPersonAttribute()				// ��� �������� �Ӽ� ����
{
	char names[MAX_NAME_LEN + 1];					// �̸��� ��� �迭
	int name_len;

	birthDate.setRandDateAttributes();				// ��¥ �����ؼ� ����
	// �̸� ���� ����
	name_len = rand() % (MAX_NAME_LEN - MIN_NAME_LEN) + MIN_NAME_LEN;
	for (int i = 0; i < name_len; i++)
		names[i] = rand() % 26 + 'a';				// rand()�� ��, 26(���ĺ� ����)�� ���� ������ + �ƽ�Ű�ڵ� 'a'
	names[name_len] = '\0';							// ������ NULL ���� ����

	name = string(names);							// �迭�� ���ڿ�ȭ �� ��, ����
}


//	Person ������ ��� �Լ�
void Person::fprintPerson(ostream& fout)
{
	fout << "Person [ name: ";							// �̸� ���
	fout.setf(ios::left); fout << setw(16) << name;		// �̸��� ���� ���� ��, ĭ�� 16ĭ���� ����)
	fout.unsetf(ios::left); fout << ", birth date: ";	// ��������� ������ ���� ��, �̸� ���� �Լ��� ���
	birthDate.fprintDate(fout); fout << "]";
}