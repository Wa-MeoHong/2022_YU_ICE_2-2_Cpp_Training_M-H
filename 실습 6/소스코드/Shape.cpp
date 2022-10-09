#include "Shape.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. name만 인수를 받는 constructor
		3. 모든 인자를 받는 constructor				*/

Shape::Shape()
{
	px = py = 0;								// 좌표는 원점 (0, 0)
	angle = 0.0;								// 각도 0.0도로 초기화
	name = "no_name";							// 이름도 없음
	line_color = brush_color = RGB_BLACK;		// 디폴트 초기값은 검은색으로 설정
}
Shape::Shape(string name)
{
	px = py = 0;								// 좌표는 원점 (0, 0)
	angle = 0.0;								// 각도 0.0도로 초기화
	NameSet(name);								// 이름 세팅
	line_color = brush_color = RGB_BLACK;		// 디폴트 초기값은 검은색으로 설정
}
Shape::Shape(int px, int py, double angle, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	: angle(angle), line_color(ln_clr), brush_color(br_clr), pen_thickness(pen_thick)
{
	// 나머지는 function initializer로 처리함 
	set_pX(px);									// 좌표 세팅
	set_pY(py);	
	NameSet(name);								// 이름 세팅
}

/*				destructor ( 소멸자 )				*/
Shape::~Shape()
{
	// cout << "Shape class terminated!" << endl;
}

/*				member functions ( 멤버 함수들 )
		1. draw(ConsolePixelFrame cp_frame)
		  (virtual로 정의하였고, sub-class에서 재정의용도로 만듦)
		2. fprint(ostream&) const ( 출력 함수 )				*/
void Shape::draw()
{
	//draw
}
void Shape::draw(ConsolePixelFrame cp_frame)
{
	/* virtual function that will be late-binded to sub-class's draw() */
}
void Shape::fprint(ostream& out) const
{
	// 출력 순서 : 좌표 - 각도 - 색깔(선, 브러시)
	out << "pos (" << setw(3) << this->pX() << ", " << setw(3) << this->pY() << "), ";
	out << "line_color(";	printRGB(out, line_color); out << "), ";
	out << "brush_color("; printRGB(out, brush_color); out << ")";
}

/*				operator Overloading ( 연산자 오버로드 )
		1. 대입 연산자 ( = )
		2. 출력 연산자 ( << )										*/
Shape& Shape::operator=(const Shape& s)
{
	this->px = s.pX(); this->py = s.pY();
	this->angle = s.angle;
	this->NameSet(s.Name());
	line_color = s.line_color;
	brush_color = s.brush_color;

	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}
ostream& operator<<(ostream& out, const Shape s)
{
	out << s.Name() << ": ";	s.fprint(out);

	return out;
	// TODO: 여기에 return 문을 삽입합니다.
}
