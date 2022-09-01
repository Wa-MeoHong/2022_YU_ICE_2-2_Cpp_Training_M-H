#include "Student.h"

#define RANDOMIZE() srand(time(NULL))
#define BIG_SIZE 300
#define LINESIZE 20

void initStudentNAME(char* name);						// �̸� �ʱ� ���� �Լ�
void initDepartment(char* department);					// �а� �ʱ� ���� �Լ�

/* 
			>>  �л� ������ �ʱ� ���� �Լ�  <<
	for������ �ݺ���.
	�й��� �Ʊ� ������ bigRand�� ���� ����
	�̸�, �а��� rand()�� �̿��� ���ڿ��� �������� �����Ͽ� �������
	�г⵵ rand()�� �̿��� 1~8�г���� �������� ������ �������
	������ rand()�� ���� ���� ������ ��, ���� 10000���� ���� �������� ������ ��, �ű⿡ 100�� ���� 0.00 ~ 99.99���� ����
*/ 
void initStudents(Student* students, int* student_ids, int num_students)
{
	RANDOMIZE();
	for (int i = 0; i < num_students; i++)					// �л��� ��ŭ �ݺ� 
	{
		students[i].st_id = student_ids[i];					// �й�
		initStudentNAME(students[i].name);					// �̸� ����
		initDepartment(students[i].department);				// �а� ����
		students[i].grade = rand() % 8 + 1;					// �г� ����
		students[i].GPA = ((rand() % 10000) / 100.0);		// ���� ����
	} 
}
void initStudentNAME(char* name)					// �̸� �ʱ� ���� �Լ�
{
	int name_len;

	name_len = rand() % 10 + 5;						// �̸� ���� ( 5�� ~ 15�� �̳� )

	for (int i = 0; i < name_len; i++)
	{
		if (i == 0)
			name[i] = rand() % 26 + 'A';				// ù ���ڴ� �빮���̱� ������ 65(A)���� 90(Z)����
		else
			name[i] = rand() % 26 + 'a';				// ������ ���ڴ� �ҹ��ڷ� 
	}
	name[name_len] = '\0';							// '\0' NULL����
}
void initDepartment(char* department)				// �а� �ʱ� ���� �Լ�
{
	int depart_len;

	depart_len = rand() % 2 + 3;					// �а� ���� ( 3�� ~ 5�� �̳� )
	for (int i = 0; i < depart_len; i++)
	{
		department[i] = rand() % 26 + 'A';			// �빮���̱� ������ 65(A)���� 90(Z)����
	}
	department[depart_len] = '\0';					// '\0' NULL����
}

/*			>> �л� ��� �Լ� <<
	1. �л� ������ ���
	2. �л� ������ ��� ( �й��� )
	3. �л� ������ �迭 ��� ( �й��� )
	4. �л� ������ ��� ( ����, �й� )
	5. �л� ������ �迭 ��� ( ����, �й� ) 
*/
void fprintStudent(ostream& fout, Student* pSt)
{
	// ������� ���� (�Ҽ���)
	fout.setf(ios::fixed);											// �ε��Ҽ����� �ƴ� �����Ҽ��� ��� ���
	fout.setf(ios::showpoint);										// �Ҽ����� ���̰� ��
	fout.precision(2);												// �Ҽ��� ���� 2�ڸ��� ǥ��

	// ��� ��� 
	fout << "Student(ID: " << setw(4) << pSt->st_id << ", ";		// �й�
	fout << "Name: " << setw(16) << pSt->name << ", ";				// �̸�
	fout << "Dept: " << setw(5) << pSt->department << ", ";			// �а�
	fout << "Grade: " << pSt->grade << ", ";						// �г�
	fout << "GPA: " << setw(5) << pSt->GPA << endl;							// ����
}

void fprintStudentID(ostream& fout, Student* pSt)				// �й��� ����ϰ� �ϴ� �Լ�
{
	fout << setw(7) << pSt->st_id;								// ���, �ڸ����� 6�� ������, 6�ڸ�
}
void fprintBigArrayOfStudent_IDs(ostream& fout, Student* students, int size_array, int size_first_last_block)
{
	int count = 0;												// ����� �� �ʿ���
	int num_lines = size_first_last_block / LINESIZE;			// �߰� ������ ��, ���ٸ� ����ϰ� �ϴ°��� �ʿ�
	Student* pSt = NULL;

	/* ��� ���
	1. num_rands(������ ����)�� ���� ��¹���� �����Ѵ�.
	2. BIG_SIZE���� ���� ���, �������� ���
	3. BIG_SIZE���� ���� ���, ó�� 50�� ����ϰ� ���� �߰� ���� ��, ���� �ѹ��� 50�� ���*/

	if (size_array < BIG_SIZE)
	{
		num_lines = size_array / LINESIZE;
	}

	for (int i = 0; i < num_lines; i++)
	{
		for (int j = 0; j < LINESIZE; j++)
		{
			pSt = &students[count];								// ��¿� ������ �迭�� ���� �޾ƿ�
			if (count == size_array)							// ���� ��������� Ż��
				break;
			fprintStudentID(fout, pSt);							// ���, �ڸ����� 7�� ������, 7�ڸ�
			count++;
		}
		fout << endl;											// 10�� ��� �� ����
	}

	// ������ ���� BIG_SIZE���� �� ū ���, ���� ��, ����Ѵ�.
	if (size_array >= BIG_SIZE)
	{
		fout << ". . . . . . . ." << endl;						// �����ϴ� ��
		count = size_array - (LINESIZE * num_lines);

		for (int i = 0; i < num_lines; i++)
		{
			for (int j = 0; j < LINESIZE; j++)
			{
				pSt = &students[count];							// ��¿� ������ �迭�� ���� �޾ƿ�
				fprintStudentID(fout, pSt);						// ���, �ڸ����� 7�� ������, 7�ڸ�
				count++;
			}
			fout << endl;										// ���� ����
		}
		fout << endl;
	}
}

void fprintStudentGPA_ID(ostream& fout, Student* pSt)				// ����, �й��� ���� ������ִ� �Լ�
{
	// ������� ���� (�Ҽ���)
	fout.setf(ios::fixed);											// �ε��Ҽ����� �ƴ� �����Ҽ��� ��� ���
	fout.setf(ios::showpoint);										// �Ҽ����� ���̰� ��
	fout.precision(2);												// �Ҽ��� ���� 2�ڸ��� ǥ��

	fout << "(" << setw(5) << pSt->GPA << ", " << setw(5) << pSt->st_id << ") ";		// ���, �ڸ����� 6�� ������, 6�ڸ�
}
void fprintBigArrayOfStudent_GPA_IDs(ostream& fout, Student* students, int size_array, int size_first_last_block)
{
	int count = 0;														// ����� �� �ʿ���
	int num_lines = size_first_last_block / (LINESIZE / 2);				// �߰� ������ ��, ���ٸ� ����ϰ� �ϴ°��� �ʿ�, LINESIZE�� 20�̶� 10���� ������ ���
	Student* pSt = NULL;

	/* ��� ���
	1. num_rands(������ ����)�� ���� ��¹���� �����Ѵ�.
	2. BIG_SIZE���� ���� ���, �������� ���
	3. BIG_SIZE���� ���� ���, ó�� 50�� ����ϰ� ���� �߰� ���� ��, ���� �ѹ��� 50�� ���*/

	if (size_array < BIG_SIZE)
	{
		num_lines = size_array / (LINESIZE / 2);				
	}

	for (int i = 0; i < num_lines; i++)
	{
		for (int j = 0; j < (LINESIZE / 2); j++)				// LINESIZE�� 20�̶� 10������ ����ϰ� ��
		{
			pSt = &students[count];								// ��¿� ������ �迭�� ���� �޾ƿ�
			if (count == size_array)							// ���� ��������� Ż��
				break;
			fprintStudentGPA_ID(fout, pSt);						// ���, �ڸ����� 7�� ������, 7�ڸ�
			count++;
		}
		fout << endl;											// 10�� ��� �� ����
	}

	// ������ ���� BIG_SIZE���� �� ū ���, ���� ��, ����Ѵ�.
	if (size_array >= BIG_SIZE)
	{
		fout << ". . . . . . . ." << endl;						// �����ϴ� ��
		count = size_array - ((LINESIZE / 2) * num_lines);

		for (int i = 0; i < num_lines; i++)
		{
			for (int j = 0; j < (LINESIZE / 2); j++)
			{
				pSt = &students[count];							// ��¿� ������ �迭�� ���� �޾ƿ�
				fprintStudentGPA_ID(fout, pSt);					// ���
				count++;
			}
			fout << endl;										// ���� ����
		}
		fout << endl;
	}
}

/*				>> �л� ���� �� Ž�� <<
	1. �л� ������ ���� ( �й������� )
	2. �л� ������ ���� ( 1����: ����(��������), 2����: �й�(��������)
	3. �л� ������ ����Ž�� 
*/

void sortStudentsByID(Student students[], int num_students)			// �й� ������������ �л� ������ ����
{
	Student temp;
	int min_index = 0;												// ���������̹Ƿ� �� ���� ���� ������ �´�.
	int sort_index = 0;												// �ٲ� �ε��� ��ȣ

	/*			>>>> �л� ������ ���� <<<<\
		1. ������ �й� ������������ �����Ѵ�.
	*/

	while (true)
	{
		if (sort_index == num_students)								// ���� sort_index�� �迭 ���������� �����ߴٸ� �����.
			break;
		temp = students[sort_index];								// �ٲ� �����͸� ����
		min_index = sort_index;										// �ٲ� �������� ���� ū �� ( �ʱⰪ ���� ) 

		// Ž�� 
		for (int i = sort_index; i < num_students; i++)
		{
			if (temp.st_id > students[i].st_id)						// �й��� ������
			{
				temp = students[i];									// �ش� ��, temp�� ����, min_index�� ����
				min_index = i;
			}
		}

		// Ž�� ��, �ٲٱ�
		students[min_index] = students[sort_index];
		students[sort_index] = temp;
		sort_index++;
	}

}
void SS_StudentsByGPA_ID(Student* students, int num_students)		// �л� ���� ����
{
	Student temp;
	int max_index = 0;												// 1������ ���������̱� ������ ���� ū ���� �Ǿ����� �´�
	int sort_index = 0;												// �ٲ� �ε��� ��ȣ


	/*			>>>> �л� ������ ���� <<<<\
		1. ������ ���� ������������ �����Ѵ�.
		2. ������ �������, �й��� ���� ������� �����Ѵ�.
	*/

	while (true)
	{
		if (sort_index == num_students)								// ���� sort_index�� �迭 ���������� �����ߴٸ� �����.
			break;
		temp = students[sort_index];								// �ٲ� �����͸� ����
		max_index = sort_index;										// �ٲ� �������� ���� ū �� ( �ʱⰪ ���� ) 

		// Ž�� 
		for (int i = sort_index ; i < num_students; i++)
		{
			if (temp.GPA < students[i].GPA)												// 1���� : �ٲ� �����ͺ��� ������ ������
			{
				temp = students[i];
				max_index = i;
			}
		}

		// Ž�� ��, �ٲٱ�
		students[max_index] = students[sort_index];
		students[sort_index] = temp;
		sort_index++;
	}

	// 2���� ( �й� ) 
	sort_index = 0;
	while (true)
	{
		if (sort_index == num_students)								// ���� sort_index�� �迭 ���������� �����ߴٸ� �����.
			break;
		temp = students[sort_index];								// �ٲ� �����͸� ����
		max_index = sort_index;										// �ٲ� �������� ���� ū �� ( �ʱⰪ ���� ) 

		// Ž�� 
		for (int i = sort_index; i < num_students; i++)
		{
			if (temp.GPA == students[i].GPA && temp.st_id > students[i].st_id)				// 2���� : �ٲ� �����ͺ��� ������ ���� �й��� ������
			{
				temp = students[i];
				max_index = i;
			}
		}

		// Ž�� ��, �ٲٱ�
		students[max_index] = students[sort_index];
		students[sort_index] = temp;
		sort_index++;
	}

}

Student* binarySearchStudentByID(Student* students, int num_students, int st_id)	// �л� ���� Ž��
{
	int low = 0, high = num_students - 1;							// ����, ���� ���ʰ� ����
	int mid;														// �߰��� ����

	if ((st_id > students[num_students - 1].st_id) || (st_id < students[0].st_id))
		return NULL;												// ���� ���� ���� ���� ��� NULL�� ��ȯ

	while (low <= high)												// low�� high�� ���� ������ 
	{
		mid = (low + high) / 2;										// �߰��� 
		if (st_id == students[mid].st_id)							// ���� �߰����� ��ġ�ϸ�	�ٷ� return���� ���� ��ȯ
			return &students[mid];
		else if (st_id < students[mid].st_id)						// ã�� ���� �߰������� �۴ٸ�
			high = mid - 1;											// ������ mid - 1�� ����
		else
			low = mid + 1;											// �ƴϸ� ������ mid + 1�� ����
	}
}
