#include "Student.h"

using namespace std;

string genRandDept();													// �а� �ʱ� ���� �Լ�
string genRandName();													// �̸� �ʱ� ���� �Լ�
double genRandGPA();													// ���� �ʱ� �Լ�

ostream& operator<<(ostream& out, const Student& st)					// ������ �����ε� (��� ������)
{
	out << "Student[ " <<
		"st_id : " << setw(6) << st.ST_ID() <<
		", name : " << setw(8) << st.Name() <<
		", Dept : " << setw(6) << st.Dept_Name() <<
		", birth date : " << st.BirthDate();
	out.setf(ios::showpoint); out.setf(ios::fixed);						// ���� �Ҽ��� 2�ڸ������� ���
	out.precision(2);
	out << ", GPA : " << setw(6) << st.GPA() << endl;
	out.unsetf(ios::adjustfield);										// ��� ���Ĺ�� �������� ����

	return out;
}

Student genRandStudent(int id)											// �л� �ʱ� ���� �Լ�
{
	Student temp(id);													// id�� �޾� ���� id�� �����ڸ� Ʈ������

	temp.SetDept(genRandDept());										// �а� �����
	temp.nameSetting(genRandName());									// �̸� ����
	temp.BirthSetting(genRandDate());									// ���� ����
	temp.SetGPA(genRandGPA());											// ���� ����

	return temp;
}
void genST_ids(int num_students, int* st_ids)							// �й� �����Լ�
{
	int count = 0;
	int studentID;
	int* flag = NULL;
	int offset = 10000;
	int IDsize = 40000;

	flag = new int[IDsize];
	while (count < num_students)										// �߻���ų ������ŭ
	{
		studentID = (((unsigned int)rand() << 15) | rand()) % IDsize;

		if (flag[studentID] == 1)										// ���� studentID�� �̹� ���� ������� 
		{
			continue;
		}
		else
		{
			flag[studentID] = 1;										// �ƴϸ� üũ���ְ�
			st_ids[count++] = studentID + offset;						// st_ids[count]�� ���� ����������, count�� ++�Ѵ�.
		}
	}
}

/*							������
		1. ������ (�⺻ )
		2. ������ ( id�� �μ��� ����)
		3. ������ ( ��� ���� �Ű������� ���� )	 */

Student::Student()
{
	st_id = 0;
	dept_name = "";
	gpa = 0.0;
	name = "";
	birthDate = Date(1, 1, 1);								// �������Ҷ��� 1�� 1�� 1���� ù�����̶� ������ �޸���
}
Student::Student(int id)									// �й��� �Ű������� ����
{
	st_id = id;												// �й� ����, ������ �� �ʱ�ȭ
	dept_name = "";
	gpa = 0.0;
	name = "";
	birthDate = Date(1, 1, 1);
}
Student::Student(int id, string n, Date dob, string dept_n, double GPA)	// ������ (�Ű������� ����)
{
	st_id = id;
	name = n;
	birthDate = dob;
	dept_name = dept_n;
	gpa = GPA;
}

/*						������ �����ε�
		1. ���Կ����� =
		2. �񱳿����� > ( 1�� �� ū�� )
		3. �񱳿����� == (��ġ ����)				*/
const Student& Student::operator=(const Student& right)					// ���Կ����� =
{
	// this�� ��� ���� right�� ������ ����                                                                                                
	this->SetST_ID(right.ST_ID());
	this->nameSetting(right.Name());
	this->SetDept(right.Dept_Name());
	this->BirthSetting(right.BirthDate());
	this->SetGPA(right.GPA());

	return *this;
}

bool Student::operator>(const Student& right) const						// �񱳿����� >
{
	// ���� 1. �й�, 2. �̸�, 3. �а�, 4. ����, 5. ����
	if (this->ST_ID() > right.ST_ID())
		return true;
	if (this->Name().compare(right.Name()) > 0)
		return true;
	if (this->Dept_Name().compare(right.Dept_Name()) > 0)
		return true;
	if (this->BirthDate() > right.BirthDate())
		return true;
	if (this->GPA() > right.GPA())
		return true;
	return false;
}
bool Student::operator==(const Student& right) const					// �񱳿�����
{
	// �ٸ� ��� �͵� �� �ϳ��� ��ġ���� ������ false, �ƴϸ� true
	if (this->ST_ID() != right.ST_ID())
		return false;
	if (this->Name().compare(right.Name()) != 0)
		return false;
	if (this->Dept_Name().compare(right.Dept_Name()) != 0)
		return false;
	if (this->BirthDate() != right.BirthDate())
		return false;
	if (this->GPA() != right.GPA())
		return false;
	return true;
}

string genRandDept()									// �а� �ʱ� ���� �Լ�
{
	string Depttemp; char temp[2] = {};
	int depart_len;

	depart_len = rand() % 2 + 3;					// �а� ���� ( 3�� ~ 4�� �̳� )
	for (int i = 0; i < depart_len; i++)
	{
		temp[0] = rand() % 26 + 'A';				// �빮���̱� ������ 65(A)���� 90(Z)����
		temp[1] = '\0';								// '\0' NULL����

		Depttemp.append(temp);
	}

	return Depttemp;
}
string genRandName()								// �̸� �ʱ� ���� �Լ�
{
	string Nametemp;

	Nametemp = genRandString(MINLEN, MAXLEN);		// �Լ��� �ҷ� �̸��� ����

	return Nametemp;								// ��ȯ
}
double genRandGPA()
{
	double temp;

	temp = rand() % 10000;							// ������ 10000�̸��� �ڿ����� ����
	temp /= 100;									// �� ��, 100�� ���� 0.00 ~ 99.99 ������ ���ڷ� ����

	return temp;									// ��ȯ

}
