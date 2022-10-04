#include "Student.h"

using namespace std;

string genRandDept();													// 학과 초기 설정 함수
string genRandName();													// 이름 초기 설정 함수
double genRandGPA();													// 성적 초기 함수

ostream& operator<<(ostream& out, const Student& st)					// 연산자 오버로드 (출력 연산자)
{
	out << "Student[ " <<
		"st_id : " << setw(6) << st.ST_ID() <<
		", name : " << setw(8) << st.Name() <<
		", Dept : " << setw(6) << st.Dept_Name() <<
		", birth date : " << st.BirthDate();
	out.setf(ios::showpoint); out.setf(ios::fixed);						// 고정 소수점 2자리까지만 출력
	out.precision(2);
	out << ", GPA : " << setw(6) << st.GPA() << endl;
	out.unsetf(ios::adjustfield);										// 출력 정렬방식 포맷지정 해제

	return out;
}

Student genRandStudent(int id)											// 학생 초기 설정 함수
{
	Student temp(id);													// id를 받아 먼저 id로 생성자를 트리거함

	temp.SetDept(genRandDept());										// 학과 만들기
	temp.nameSetting(genRandName());									// 이름 생성
	temp.BirthSetting(genRandDate());									// 생일 생성
	temp.SetGPA(genRandGPA());											// 학점 생성

	return temp;
}
void genST_ids(int num_students, int* st_ids)							// 학번 생성함수
{
	int count = 0;
	int studentID;
	int* flag = NULL;
	int offset = 10000;
	int IDsize = 40000;

	flag = new int[IDsize];
	while (count < num_students)										// 발생시킬 개수만큼
	{
		studentID = (((unsigned int)rand() << 15) | rand()) % IDsize;

		if (flag[studentID] == 1)										// 만약 studentID가 이미 나온 난수라면 
		{
			continue;
		}
		else
		{
			flag[studentID] = 1;										// 아니면 체크해주고
			st_ids[count++] = studentID + offset;						// st_ids[count]에 값을 대입해준후, count를 ++한다.
		}
	}
}

/*							생성자
		1. 생성자 (기본 )
		2. 생성자 ( id를 인수로 받음)
		3. 생성자 ( 모든 값을 매개변수로 받음 )	 */

Student::Student()
{
	st_id = 0;
	dept_name = "";
	gpa = 0.0;
	name = "";
	birthDate = Date(1, 1, 1);								// 생일정할때는 1년 1월 1일이 첫시작이라 설정도 달리함
}
Student::Student(int id)									// 학번이 매개변수로 들어옴
{
	st_id = id;												// 학번 대입, 나머지 다 초기화
	dept_name = "";
	gpa = 0.0;
	name = "";
	birthDate = Date(1, 1, 1);
}
Student::Student(int id, string n, Date dob, string dept_n, double GPA)	// 생성자 (매개변수로 받음)
{
	st_id = id;
	name = n;
	birthDate = dob;
	dept_name = dept_n;
	gpa = GPA;
}

/*						연산자 오버로딩
		1. 대입연산자 =
		2. 비교연산자 > ( 1이 더 큰가 )
		3. 비교연산자 == (일치 여부)				*/
const Student& Student::operator=(const Student& right)					// 대입연산자 =
{
	// this의 모든 값을 right의 값으로 대입                                                                                                
	this->SetST_ID(right.ST_ID());
	this->nameSetting(right.Name());
	this->SetDept(right.Dept_Name());
	this->BirthSetting(right.BirthDate());
	this->SetGPA(right.GPA());

	return *this;
}

bool Student::operator>(const Student& right) const						// 비교연산자 >
{
	// 기준 1. 학번, 2. 이름, 3. 학과, 4. 생일, 5. 학점
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
bool Student::operator==(const Student& right) const					// 비교연산자
{
	// 다른 모든 것들 중 하나가 일치하지 않으면 false, 아니면 true
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

string genRandDept()									// 학과 초기 설정 함수
{
	string Depttemp; char temp[2] = {};
	int depart_len;

	depart_len = rand() % 2 + 3;					// 학과 길이 ( 3자 ~ 4자 이내 )
	for (int i = 0; i < depart_len; i++)
	{
		temp[0] = rand() % 26 + 'A';				// 대문자이기 때문에 65(A)부터 90(Z)까지
		temp[1] = '\0';								// '\0' NULL문자

		Depttemp.append(temp);
	}

	return Depttemp;
}
string genRandName()								// 이름 초기 설정 함수
{
	string Nametemp;

	Nametemp = genRandString(MINLEN, MAXLEN);		// 함수를 불러 이름을 만듦

	return Nametemp;								// 반환
}
double genRandGPA()
{
	double temp;

	temp = rand() % 10000;							// 학점을 10000미만의 자연수를 생성
	temp /= 100;									// 그 후, 100을 나눠 0.00 ~ 99.99 사이의 숫자로 만듦

	return temp;									// 반환

}
