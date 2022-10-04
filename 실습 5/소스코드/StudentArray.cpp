#include "StudentArray.h"

// ��� ������ �����ε�

ostream& operator<<(ostream& out, const StudentArray& Sa)
{
    // �迭 ��� �� �⺻ ����
    out << "StudentArray (size : " << Sa.SIZE() << ")" << endl;

    // �迭 ������ ���
    for (int i = 0; i < Sa.SIZE(); i++)
        out << Sa.students[i];

    return out;                     // ostream ��ȯ
}

/*                     ������, �Ҹ���
        1. ������( size���� �Ű������� ���� )
        2. ������( �迭 ���� )
        3. �Ҹ���                                     */
StudentArray::StudentArray(int size)                // ������( constructor )
{
    num_students = size;
    students = new Student[size];                   // ���� �Ҵ�
}
StudentArray::StudentArray(const StudentArray& obj) // ������( �迭 ���� )
{
    this->num_students = obj.num_students;          // �迭 ���� ����
    this->students = new Student[this->num_students];   // �迭 �����Ҵ�

    for (int i = 0; i < this->SIZE(); i++)
    {
        this->students[i] = obj.students[i];            // �迭 ����
    }
}
StudentArray::~StudentArray()                   // �Ҹ���( destuctor )
{
    delete[] students;                          // �迭 �����Ҵ� ����
}

/*                      ���� ���� �Լ�
        �������� �Լ��� ���� �� ����
        1. ���Ͽ� ���� ����
        2. �̸� ����
        3. �й� ����
        4. ���� ����
        5. ������ ������ ������ �� ����
                                                        */
void StudentArray::sortByBirthDate()                            // ���Ͽ� ���� ����
{
    Student min_Std; int Index_min;                     // �ٲ� student����, �ε��� ��ȣ 

    for (int round = 0; round < this->SIZE() - 1; round++)
    {
        Index_min = round;                              // �ּҰ� ����
        min_Std = this->students[round];

        for (int i = round + 1; i < this->SIZE(); round++)
        {
            if (min_Std.BirthDate() > this->students[i].BirthDate())    // ������ �� �����ٸ�
            {
                Index_min = i;                          // �ּҰ����� ����
                min_Std = this->students[i];
            }
        }

        // ���� �� ����

        if (Index_min != round)
        {
            this->students[Index_min] = this->students[round];
            this->students[round] = min_Std;
        }
    }
}
void StudentArray::sortByName()                                 // �̸��� ���� ����                    
{
    Student min_Std; int Index_min;

    for (int round = 0; round < this->SIZE() - 1; round++)
    {
        Index_min = round;
        min_Std = this->students[round];

        for (int i = round + 1; i < this->SIZE(); round++)
        {
            if (min_Std.Name().compare(this->students->Name()) < 0)     // �л��� �̸����� ����
            {
                Index_min = i;
                min_Std = this->students[i];
            }
        }
        // ���� ��, ����
        if (Index_min != round)
        {
            this->students[Index_min] = this->students[round];
            this->students[round] = min_Std;
        }
    }
}
void StudentArray::sortByST_ID()                                // �й��� ���� ����
{
    Student min_Std; int Index_min;

    for (int round = 0; round < this->SIZE() - 1; round++)
    {
        Index_min = round;
        min_Std = this->students[round];

        for (int i = round + 1; i < this->SIZE(); round++)
        {
            if (min_Std.ST_ID() > this->students[i].ST_ID())        // ���̵� �� ������
            {
                Index_min = i;
                min_Std = this->students[i];
            }
        }
        // ���� �� ���� 
        if (Index_min != round)
        {
            this->students[Index_min] = this->students[round];
            this->students[round] = min_Std;
        }
    }
}
void StudentArray::sortByGPA()                                  // ������ ���� ����
{
    Student min_Std; int Index_min;

    for (int round = 0; round < this->SIZE() - 1; round++)
    {
        Index_min = round;
        min_Std = this->students[round];

        for (int i = round + 1; i < this->SIZE(); round++)
        {
            if (min_Std.GPA() > this->students[i].GPA())       // ������ �� ������
            {
                Index_min = i;
                min_Std = this->students[i];
            }
        }

        // ���� �� ����
        if (Index_min != round)
        {
            this->students[Index_min] = this->students[round];
            this->students[round] = min_Std;
        }
    }
}
void StudentArray::SelectSort(int sel)                          //���ؿ� ���� �������� ���� 
{
    Student min_Std; int Index_min;
    int comparetemp;

    for (int round = 0; round < this->SIZE() - 1; round++)
    {
        Index_min = round;
        min_Std = this->students[round];

        for (int i = round + 1; i < this->SIZE(); i++)
        {
            // ������ ������ ���� �� ����. sel�� ���� �޾ƿ���, comparetemp�� ��´�
            // 1. ����, 2. �̸�, 3. GPA, 4. ����
            switch (sel)
            {
            case 1:
            {
                comparetemp = (min_Std.ST_ID() > this->students[i].ST_ID());
                break;
            }
            case 2:
            {
                comparetemp = (min_Std.Name().compare(this->students[i].Name()) > 0);
                break;
            }
            case 3:
            {
                comparetemp = (min_Std.GPA() > this->students[i].GPA());
                break;
            }
            case 4:
            {
                comparetemp = (min_Std.BirthDate() > this->students[i].BirthDate());
                break;
            }
            }

            if (comparetemp)
            {
                Index_min = i;
                min_Std = this->students[i];
            }
        }
        // ���� �� ����
        if (Index_min != round)
        {
            this->students[Index_min] = this->students[round];
            this->students[round] = min_Std;
        }
    }
}

Student& StudentArray::operator[] (int sub)                     // �л� �迭 �ε��� �� ��ȯ
{
    if (isValidIndex(sub))                                      // �ε�����ȣ�� ��ȿ����
        return students[sub];
    else
        cout << "Error : Subscript out of range.\n"; exit(0);
}
bool StudentArray::isValidIndex(int index) const                // �ε��� ��ȣ�� ��ȿ�Ѱ�
{
    if (index < 0 || index >= this->SIZE())                     // �ε��� ��ȣ�� ����ٸ� false
        return false;
    else
        return true;                                            // �ƴϸ� true
}