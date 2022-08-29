#ifndef STUDENT_H
#define BIGRAND_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdbool.h>
using namespace std;

#define MIN_NAME_LEN 5							// 최소 이름 길이 5
#define MAX_NAME_LEN 15							// 최대 이름 길이 5

/*
	학생 구조체 
	{
		학번(st_id)
		이름
		전공
		학년
		성적
	}
*/

typedef struct Student 
{
	int st_id;
	char name[MAX_NAME_LEN + 1];
	char department[MAX_NAME_LEN + 1];
	int grade;
	double GPA;
} Student;

/* 
					>>> 함수 목록 <<< 
	1. 학생 구조체 배열 초기 설정
	2. 학생 1명 출력, printStudnet() 함수 사용
	3. 학생 1명 출력 ( 학번만 출력 )
	4. 학생 구조체 배열 출력 ( 줄여서 ) 
	5. 학생 1명 출력 ( 성적, 학번만 출력 )
	6. 학생 구조체 배열 출력 ( 성적, 학번만 출력, 줄여서 )
	7. 학생 구조체 배열 정렬 ( 학점 내림차순 기준, 2순위는 학번 오름차순)
	8. 학생 이진 탐색 
*/

void initStudents(Student* students, int* student_ids, int num_students);			
void fprintStudent(ostream& fout, Student* pSt);
void fprintStudentID(ostream& fout, Student* pSt);
void fprintBigArrayOfStudent_IDs(ostream& fout, Student* students, int size_array, int size_first_last_block);
void fprintStudentGPA_ID(ostream& fout, Student* pSt);
void fprintBigArrayOfStudent_GPA_IDs(ostream& fout, Student* students, int size_array, int size_first_last_block);
void sortStudentsByID(Student students[], int num_students);
void SS_StudentsByGPA_ID(Student* students, int num_students);
Student* binarySearchStudentByID(Student* students, int num_students, int st_id);

#endif