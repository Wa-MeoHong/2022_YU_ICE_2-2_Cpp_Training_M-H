#include "Circle.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. name만 인수를 받는 constructor
		3. 모든 인자를 받는 constructor				
		4. 복제생성자								*/
Circle::Circle()
{
	setRadius(0);
}
Circle::Circle(string name)
	: Shape(name)
{
	setRadius(0);
}
Circle::Circle(int px, int py, int r, double angle, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	: Shape(px, py, angle, ln_clr, br_clr, pen_thick, name)
{
	setRadius(r);
}
Circle::Circle(const Circle& cir)
	: Shape(cir.pX(), cir.pY(), cir.angle, cir.line_color, cir.brush_color, cir.pen_thickness, cir.Name())
{
	setRadius(cir.Radius());
}

/*				destructor ( 소멸자 )				*/
Circle::~Circle()
{
	// cout << "Circle class terminated!" << endl;
}

/*				member functions ( 멤버 함수들 )
		1. draw(ConsolePixelFrame cp_frame) ( 그림 그리기 함수 )
		2. fprint(ostream&) const ( 출력 함수 )				
		3. Area() const			( 넓이 구하는 함수)*/
void Circle::draw(ConsolePixelFrame cp_frame)
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc;
	int fr_px, fr_py;							// 중심점

	fr_px = cp_frame.Cpfr_Px() + pX();			// 중심 X좌표
	fr_py = cp_frame.Cpfr_Py() + pY();			// 중심 Y좌표
	hdc = cp_frame.Console_DC();				// HDC 객체

	// 펜, 브러시 생성
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	
	// 원을 그림
	Ellipse(hdc, fr_px - radius, fr_py - radius, fr_px + radius, fr_py + radius);
	
	// HDC객체 삭제
	SelectObject(hdc, old_pen);		DeleteObject(new_pen);
	SelectObject(hdc, old_brush);	DeleteObject(new_brush);
}
void Circle::fprint(ostream& out) const
{
	out.setf(ios::showpoint); out.setf(ios::fixed);				// 고정 소수점 2자리까지만 출력
	out.precision(2);

	// 출력 순서 : 좌표 - 반지름 - 각도 - 색깔(선, 브러시)
	this->Shape::fprint(out);
	out << ", radius (" << setw(3) << this->Radius() << "), ";
	out << ", area (" << setw(4) << this->Area() << ")";
}
double Circle::Area() const
{
	return (PI * pow(double(Radius()), 2));
}

/*				operator Overloading ( 연산자 오버로드 )
		1. 대입 연산자 ( = )
		2. 출력 연산자 ( << )										*/
Circle& Circle::operator=(const Circle& cir)
{
	this->Shape::operator=(cir);
	this->setRadius(cir.Radius());

	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}
ostream& operator<<(ostream& out, const Circle& cir)
{
	out << cir.Name() << " : ";	cir.fprint(out);
	return out;
	// TODO: 여기에 return 문을 삽입합니다.
}
