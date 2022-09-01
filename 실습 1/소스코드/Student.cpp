#include "Student.h"

#define RANDOMIZE() srand(time(NULL))
#define BIG_SIZE 300
#define LINESIZE 20

void initStudentNAME(char* name);						// 이름 초기 설정 함수
void initDepartment(char* department);					// 학과 초기 설정 함수

/* 
			>>  학생 데이터 초기 설정 함수  <<
	for문으로 반복함.
	학번은 아까 생성한 bigRand를 통해 대입
	이름, 학과를 rand()를 이용해 문자열을 랜덤으로 생성하여 집어넣음
	학년도 rand()를 이용해 1~8학년까지 랜덤으로 생성해 집어넣음
	성적도 rand()를 통해 먼저 생성한 후, 먼저 10000으로 나눠 나머지를 가져온 후, 거기에 100을 나눠 0.00 ~ 99.99까지 생성
*/ 
void initStudents(Student* students, int* student_ids, int num_students)
{
	RANDOMIZE();
	for (int i = 0; i < num_students; i++)					// 학생수 만큼 반복 
	{
		students[i].st_id = student_ids[i];					// 학번
		initStudentNAME(students[i].name);					// 이름 설정
		initDepartment(students[i].department);				// 학과 설정
		students[i].grade = rand() % 8 + 1;					// 학년 설정
		students[i].GPA = ((rand() % 10000) / 100.0);		// 성적 설정
	} 
}
void initStudentNAME(char* name)					// 이름 초기 설정 함수
{
	int name_len;

	name_len = rand() % 10 + 5;						// 이름 길이 ( 5자 ~ 15자 이내 )

	for (int i = 0; i < name_len; i++)
	{
		if (i == 0)
			name[i] = rand() % 26 + 'A';				// 첫 글자는 대문자이기 때문에 65(A)부터 90(Z)까지
		else
			name[i] = rand() % 26 + 'a';				// 나머지 글자는 소문자로 
	}
	name[name_len] = '\0';							// '\0' NULL문자
}
void initDepartment(char* department)				// 학과 초기 설정 함수
{
	int depart_len;

	depart_len = rand() % 2 + 3;					// 학과 길이 ( 3자 ~ 5자 이내 )
	for (int i = 0; i < depart_len; i++)
	{
		department[i] = rand() % 26 + 'A';			// 대문자이기 때문에 65(A)부터 90(Z)까지
	}
	department[depart_len] = '\0';					// '\0' NULL문자
}

/*			>> 학생 출력 함수 <<
	1. 학생 데이터 출력
	2. 학생 데이터 출력 ( 학번만 )
	3. 학생 데이터 배열 출력 ( 학번만 )
	4. 학생 데이터 출력 ( 성적, 학번 )
	5. 학생 데이터 배열 출력 ( 성적, 학번 ) 
*/
void fprintStudent(ostream& fout, Student* pSt)
{
	// 출력형식 지정 (소수점)
	fout.setf(ios::fixed);											// 부동소수점이 아닌 고정소수점 방식 사용
	fout.setf(ios::showpoint);										// 소수점을 보이게 함
	fout.precision(2);												// 소수점 이하 2자리만 표시

	// 출력 모듈 
	fout << "Student(ID: " << setw(4) << pSt->st_id << ", ";		// 학번
	fout << "Name: " << setw(16) << pSt->name << ", ";				// 이름
	fout << "Dept: " << setw(5) << pSt->department << ", ";			// 학과
	fout << "Grade: " << pSt->grade << ", ";						// 학년
	fout << "GPA: " << setw(5) << pSt->GPA << endl;							// 성적
}

void fprintStudentID(ostream& fout, Student* pSt)				// 학번만 출력하게 하는 함수
{
	fout << setw(7) << pSt->st_id;								// 출력, 자리수를 6로 지정해, 6자리
}
void fprintBigArrayOfStudent_IDs(ostream& fout, Student* students, int size_array, int size_first_last_block)
{
	int count = 0;												// 출력할 때 필요함
	int num_lines = size_first_last_block / LINESIZE;			// 중간 생략할 시, 몇줄만 출력하게 하는가에 필요
	Student* pSt = NULL;

	/* 출력 방식
	1. num_rands(난수의 개수)에 따라 출력방식을 결정한다.
	2. BIG_SIZE보다 적을 경우, 생략없이 출력
	3. BIG_SIZE보다 많을 경우, 처음 50개 출력하고 나서 중간 생략 후, 끝에 한번더 50개 출력*/

	if (size_array < BIG_SIZE)
	{
		num_lines = size_array / LINESIZE;
	}

	for (int i = 0; i < num_lines; i++)
	{
		for (int j = 0; j < LINESIZE; j++)
		{
			pSt = &students[count];								// 출력용 변수에 배열의 값을 받아옴
			if (count == size_array)							// 전부 출력했으면 탈출
				break;
			fprintStudentID(fout, pSt);							// 출력, 자리수를 7로 지정해, 7자리
			count++;
		}
		fout << endl;											// 10개 출력 후 엔터
	}

	// 랜덤한 수가 BIG_SIZE보다 더 큰 경우, 생략 후, 출력한다.
	if (size_array >= BIG_SIZE)
	{
		fout << ". . . . . . . ." << endl;						// 생략하는 것
		count = size_array - (LINESIZE * num_lines);

		for (int i = 0; i < num_lines; i++)
		{
			for (int j = 0; j < LINESIZE; j++)
			{
				pSt = &students[count];							// 출력용 변수에 배열의 값을 받아옴
				fprintStudentID(fout, pSt);						// 출력, 자리수를 7로 지정해, 7자리
				count++;
			}
			fout << endl;										// 한줄 띄우기
		}
		fout << endl;
	}
}

void fprintStudentGPA_ID(ostream& fout, Student* pSt)				// 성적, 학번을 같이 출력해주는 함수
{
	// 출력형식 지정 (소수점)
	fout.setf(ios::fixed);											// 부동소수점이 아닌 고정소수점 방식 사용
	fout.setf(ios::showpoint);										// 소수점을 보이게 함
	fout.precision(2);												// 소수점 이하 2자리만 표시

	fout << "(" << setw(5) << pSt->GPA << ", " << setw(5) << pSt->st_id << ") ";		// 출력, 자리수를 6로 지정해, 6자리
}
void fprintBigArrayOfStudent_GPA_IDs(ostream& fout, Student* students, int size_array, int size_first_last_block)
{
	int count = 0;														// 출력할 때 필요함
	int num_lines = size_first_last_block / (LINESIZE / 2);				// 중간 생략할 시, 몇줄만 출력하게 하는가에 필요, LINESIZE가 20이라 10으로 나누고 사용
	Student* pSt = NULL;

	/* 출력 방식
	1. num_rands(난수의 개수)에 따라 출력방식을 결정한다.
	2. BIG_SIZE보다 적을 경우, 생략없이 출력
	3. BIG_SIZE보다 많을 경우, 처음 50개 출력하고 나서 중간 생략 후, 끝에 한번더 50개 출력*/

	if (size_array < BIG_SIZE)
	{
		num_lines = size_array / (LINESIZE / 2);				
	}

	for (int i = 0; i < num_lines; i++)
	{
		for (int j = 0; j < (LINESIZE / 2); j++)				// LINESIZE가 20이라 10개씩만 출력하게 함
		{
			pSt = &students[count];								// 출력용 변수에 배열의 값을 받아옴
			if (count == size_array)							// 전부 출력했으면 탈출
				break;
			fprintStudentGPA_ID(fout, pSt);						// 출력, 자리수를 7로 지정해, 7자리
			count++;
		}
		fout << endl;											// 10개 출력 후 엔터
	}

	// 랜덤한 수가 BIG_SIZE보다 더 큰 경우, 생략 후, 출력한다.
	if (size_array >= BIG_SIZE)
	{
		fout << ". . . . . . . ." << endl;						// 생략하는 것
		count = size_array - ((LINESIZE / 2) * num_lines);

		for (int i = 0; i < num_lines; i++)
		{
			for (int j = 0; j < (LINESIZE / 2); j++)
			{
				pSt = &students[count];							// 출력용 변수에 배열의 값을 받아옴
				fprintStudentGPA_ID(fout, pSt);					// 출력
				count++;
			}
			fout << endl;										// 한줄 띄우기
		}
		fout << endl;
	}
}

/*				>> 학생 정렬 및 탐색 <<
	1. 학생 데이터 정렬 ( 학번만으로 )
	2. 학생 데이터 정렬 ( 1순위: 성적(내림차순), 2순위: 학번(오름차순)
	3. 학생 데이터 이진탐색 
*/

void sortStudentsByID(Student students[], int num_students)			// 학번 오름차순으로 학생 데이터 정렬
{
	Student temp;
	int min_index = 0;												// 오름차순이므로 맨 앞이 가장 작은게 온다.
	int sort_index = 0;												// 바꿀 인덱스 번호

	/*			>>>> 학생 데이터 정렬 <<<<\
		1. 기준은 학번 오름차순으로 정렬한다.
	*/

	while (true)
	{
		if (sort_index == num_students)								// 만약 sort_index가 배열 마지막까지 도달했다면 멈춘다.
			break;
		temp = students[sort_index];								// 바꿀 데이터를 설정
		min_index = sort_index;										// 바꿀 데이터중 가장 큰 값 ( 초기값 설정 ) 

		// 탐색 
		for (int i = sort_index; i < num_students; i++)
		{
			if (temp.st_id > students[i].st_id)						// 학번이 작으면
			{
				temp = students[i];									// 해당 시, temp를 갱신, min_index도 갱신
				min_index = i;
			}
		}

		// 탐색 후, 바꾸기
		students[min_index] = students[sort_index];
		students[sort_index] = temp;
		sort_index++;
	}

}
void SS_StudentsByGPA_ID(Student* students, int num_students)		// 학생 선택 정렬
{
	Student temp;
	int max_index = 0;												// 1순위가 내림차순이기 때문에 가장 큰 값이 맨앞으로 온다
	int sort_index = 0;												// 바꿀 인덱스 번호


	/*			>>>> 학생 데이터 정렬 <<<<\
		1. 기준은 성적 내림차순으로 정렬한다.
		2. 성적이 같을경우, 학번이 빠른 순서대로 정렬한다.
	*/

	while (true)
	{
		if (sort_index == num_students)								// 만약 sort_index가 배열 마지막까지 도달했다면 멈춘다.
			break;
		temp = students[sort_index];								// 바꿀 데이터를 설정
		max_index = sort_index;										// 바꿀 데이터중 가장 큰 값 ( 초기값 설정 ) 

		// 탐색 
		for (int i = sort_index ; i < num_students; i++)
		{
			if (temp.GPA < students[i].GPA)												// 1순위 : 바꿀 데이터보다 성적이 높은가
			{
				temp = students[i];
				max_index = i;
			}
		}

		// 탐색 후, 바꾸기
		students[max_index] = students[sort_index];
		students[sort_index] = temp;
		sort_index++;
	}

	// 2순위 ( 학번 ) 
	sort_index = 0;
	while (true)
	{
		if (sort_index == num_students)								// 만약 sort_index가 배열 마지막까지 도달했다면 멈춘다.
			break;
		temp = students[sort_index];								// 바꿀 데이터를 설정
		max_index = sort_index;										// 바꿀 데이터중 가장 큰 값 ( 초기값 설정 ) 

		// 탐색 
		for (int i = sort_index; i < num_students; i++)
		{
			if (temp.GPA == students[i].GPA && temp.st_id > students[i].st_id)				// 2순위 : 바꿀 데이터보다 성적이 같고 학번이 빠른가
			{
				temp = students[i];
				max_index = i;
			}
		}

		// 탐색 후, 바꾸기
		students[max_index] = students[sort_index];
		students[sort_index] = temp;
		sort_index++;
	}

}

Student* binarySearchStudentByID(Student* students, int num_students, int st_id)	// 학생 이진 탐색
{
	int low = 0, high = num_students - 1;							// 저점, 고점 최초값 설정
	int mid;														// 중간값 설정

	if ((st_id > students[num_students - 1].st_id) || (st_id < students[0].st_id))
		return NULL;												// 값이 범위 내에 없을 경우 NULL을 반환

	while (low <= high)												// low와 high가 같을 때까지 
	{
		mid = (low + high) / 2;										// 중간값 
		if (st_id == students[mid].st_id)							// 만약 중간값과 일치하면	바로 return으로 값을 반환
			return &students[mid];
		else if (st_id < students[mid].st_id)						// 찾는 값이 중간값보다 작다면
			high = mid - 1;											// 고점을 mid - 1로 설정
		else
			low = mid + 1;											// 아니면 저점을 mid + 1로 설정
	}
}
