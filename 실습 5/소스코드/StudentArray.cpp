#include "StudentArray.h"

// 출력 연산자 오버로딩

ostream& operator<<(ostream& out, const StudentArray& Sa)
{
    // 배열 출력 전 기본 정보
    out << "StudentArray (size : " << Sa.SIZE() << ")" << endl;

    // 배열 데이터 출력
    for (int i = 0; i < Sa.SIZE(); i++)
        out << Sa.students[i];

    return out;                     // ostream 반환
}

/*                     생성자, 소멸자
        1. 생성자( size만을 매개변수로 받음 )
        2. 생성자( 배열 복사 )
        3. 소멸자                                     */
StudentArray::StudentArray(int size)                // 생성자( constructor )
{
    num_students = size;
    students = new Student[size];                   // 동적 할당
}
StudentArray::StudentArray(const StudentArray& obj) // 생성자( 배열 복사 )
{
    this->num_students = obj.num_students;          // 배열 개수 복사
    this->students = new Student[this->num_students];   // 배열 동적할당

    for (int i = 0; i < this->SIZE(); i++)
    {
        this->students[i] = obj.students[i];            // 배열 복사
    }
}
StudentArray::~StudentArray()                   // 소멸자( destuctor )
{
    delete[] students;                          // 배열 동적할당 해제
}

/*                      선택 정렬 함수
        선택정렬 함수는 거의 다 같음
        1. 생일에 따른 정렬
        2. 이름 기준
        3. 학번 기준
        4. 학점 기준
        5. 정렬의 기준을 설정할 수 있음
                                                        */
void StudentArray::sortByBirthDate()                            // 생일에 따른 정렬
{
    Student min_Std; int Index_min;                     // 바꿀 student변수, 인덱스 번호 

    for (int round = 0; round < this->SIZE() - 1; round++)
    {
        Index_min = round;                              // 최소값 갱신
        min_Std = this->students[round];

        for (int i = round + 1; i < this->SIZE(); round++)
        {
            if (min_Std.BirthDate() > this->students[i].BirthDate())    // 생일이 더 빠르다면
            {
                Index_min = i;                          // 최소값으로 갱신
                min_Std = this->students[i];
            }
        }

        // 선정 후 스왑

        if (Index_min != round)
        {
            this->students[Index_min] = this->students[round];
            this->students[round] = min_Std;
        }
    }
}
void StudentArray::sortByName()                                 // 이름에 대해 정렬                    
{
    Student min_Std; int Index_min;

    for (int round = 0; round < this->SIZE() - 1; round++)
    {
        Index_min = round;
        min_Std = this->students[round];

        for (int i = round + 1; i < this->SIZE(); round++)
        {
            if (min_Std.Name().compare(this->students->Name()) < 0)     // 학생의 이름으로 정렬
            {
                Index_min = i;
                min_Std = this->students[i];
            }
        }
        // 선정 후, 스왑
        if (Index_min != round)
        {
            this->students[Index_min] = this->students[round];
            this->students[round] = min_Std;
        }
    }
}
void StudentArray::sortByST_ID()                                // 학번에 따른 정렬
{
    Student min_Std; int Index_min;

    for (int round = 0; round < this->SIZE() - 1; round++)
    {
        Index_min = round;
        min_Std = this->students[round];

        for (int i = round + 1; i < this->SIZE(); round++)
        {
            if (min_Std.ST_ID() > this->students[i].ST_ID())        // 아이디가 더 빠른가
            {
                Index_min = i;
                min_Std = this->students[i];
            }
        }
        // 선정 후 스왑 
        if (Index_min != round)
        {
            this->students[Index_min] = this->students[round];
            this->students[round] = min_Std;
        }
    }
}
void StudentArray::sortByGPA()                                  // 학점에 따른 정렬
{
    Student min_Std; int Index_min;

    for (int round = 0; round < this->SIZE() - 1; round++)
    {
        Index_min = round;
        min_Std = this->students[round];

        for (int i = round + 1; i < this->SIZE(); round++)
        {
            if (min_Std.GPA() > this->students[i].GPA())       // 학점이 더 작은가
            {
                Index_min = i;
                min_Std = this->students[i];
            }
        }

        // 선정 후 스왑
        if (Index_min != round)
        {
            this->students[Index_min] = this->students[round];
            this->students[round] = min_Std;
        }
    }
}
void StudentArray::SelectSort(int sel)                          //기준에 따라 선택정렬 가능 
{
    Student min_Std; int Index_min;
    int comparetemp;

    for (int round = 0; round < this->SIZE() - 1; round++)
    {
        Index_min = round;
        min_Std = this->students[round];

        for (int i = round + 1; i < this->SIZE(); i++)
        {
            // 정렬의 기준을 정할 수 있음. sel을 통해 받아오고, comparetemp에 담는담
            // 1. 학점, 2. 이름, 3. GPA, 4. 생일
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
        // 선정 후 스왑
        if (Index_min != round)
        {
            this->students[Index_min] = this->students[round];
            this->students[round] = min_Std;
        }
    }
}

Student& StudentArray::operator[] (int sub)                     // 학생 배열 인덱스 값 반환
{
    if (isValidIndex(sub))                                      // 인덱스번호가 유효한지
        return students[sub];
    else
        cout << "Error : Subscript out of range.\n"; exit(0);
}
bool StudentArray::isValidIndex(int index) const                // 인덱스 번호가 유효한가
{
    if (index < 0 || index >= this->SIZE())                     // 인덱스 번호가 벗어난다면 false
        return false;
    else
        return true;                                            // 아니면 true
}