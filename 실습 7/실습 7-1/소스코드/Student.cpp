#include "Student.h"

Student::Student()
{
	// 디폴트 생성자. 0으로 초기화함
	st_id = 0;
	gpa = 0;
}

Student::Student(int s_id, string n, int reg, string country, double GPA)
	: Person(n)
{
	// 모든 인자를 대입함
	set_ST_id(s_id);
	set_regID(reg);
	set_Nation(country);
	set_GPA(GPA);
}

void Student::getKey(string KeyName, void* pKey)
{
	// 키를 반환 ( 문자열에 맞는 키를 반환함 )
	if (KeyName == "ST_ID")
		*(int*)pKey = this->ST_ID();
	else if (KeyName == "ST_NAME")
		*(string *)pKey = this->Name();
	else if (KeyName == "GPA")
		*(double *)pKey = this->GPA();
	else if (KeyName == "REG_ID")
		*(int*)pKey = this->RegID();
	else if (KeyName == "NATION")
		*(string *)pKey = this->Nat();
}

ostream& operator<<(ostream& ostr, const Student& st)
{
	// print form : Student [ st_id:  5555, name: Kim , gpa: 3.57 , regID:  10205, nation: Korea ]
	ostr << "Student [ "
		<< "st_id: " << setw(5) << st.ST_ID() << ", "
		<< "name: " << setw(7) << left << st.Name()  << ", "
		<< "gpa: ";
	// 부동 소수점에서 고정 소수점으로 바꾼 후, 2자리까지만 출력
	ostr.setf(ios::left);
	ostr.setf(ios::fixed);
	ostr.precision(2);
	ostr << st.GPA() << ", " << right
		<< "regID: " << setw(5) << st.RegID() << ", "
		<< "nation: " << setw(7) << st.Nat() << "]";

	return ostr;
	// TODO: 여기에 return 문을 삽입합니다.
}
