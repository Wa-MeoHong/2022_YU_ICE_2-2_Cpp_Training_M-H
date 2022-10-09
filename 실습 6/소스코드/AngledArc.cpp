#include "AngledArc.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. name만 인수를 받는 constructor
		3. 모든 인자를 받는 constructor
		4. 복제생성자								*/
AngledArc::AngledArc()
{
	radius = 0;
	start_angle = 0;
	sweep_angle = 0;
}
AngledArc::AngledArc(string name)
	: Shape(name)
{
	radius = 0;
	start_angle = 0;
	sweep_angle = 0;
}
AngledArc::AngledArc(int px, int py, int r, double angle, int start_ang, int sweep_ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	: Shape(px, py, angle, ln_clr, br_clr, pen_thick, name)
{
	this->setRadius(r);
	this->setStartAng(start_ang);
	this->setSweepAng(sweep_ang);
}
AngledArc::AngledArc(const AngledArc& arc)
	: Shape(arc.pX(), arc.pY(), arc.angle, arc.line_color, arc.brush_color, arc.pen_thickness, arc.Name())
{
	this->setRadius(arc.Radius());
	this->setStartAng(arc.StartAngle());
	this->setSweepAng(arc.SweepAngle());
}

/*				destructor ( 소멸자 )				*/
AngledArc::~AngledArc()
{
	// cout << "AngledArc class terminated!" << endl;
}

/*				member functions ( 멤버 함수들 )
		1. draw(ConsolePixelFrame cp_frame)
		2. fprint(ostream&) const ( 출력 함수 )		*/
void AngledArc::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	
	int start_px, start_py;
	double start_ang_rad;
	int fr_px = cp_frame.Cpfr_Px() + pX();			// 중심점 X좌표
	int fr_py = cp_frame.Cpfr_Py() + pY();			// 중심자 Y좌표

	// HDC 객체 생성
	hdc = cp_frame.Console_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	// 처음 그리는 위치 (라디안으로) 
	start_ang_rad = start_angle * PI / 180.0;
	start_px = fr_px + radius * cos(start_ang_rad);			// 그리기 시작위치 x좌표
	start_py = fr_py - radius * sin(start_ang_rad);			// 그리기 시작위치 y좌표
	
	// 팩맨 그리기
	MoveToEx(hdc, fr_px, fr_py, (LPPOINT)NULL);				// 중심좌표로 이동
	LineTo(hdc, start_px, start_py);						// 시작 위치까지 줄을 그림
	AngleArc(hdc, fr_px, fr_py, radius, start_angle, sweep_angle);	// sweep_angle점까지 원을 이동
	LineTo(hdc, fr_px, fr_py);								// 중심좌표로 선을 긋기
	
	// HDC 객체 삭제
	SelectObject(hdc, old_pen);		DeleteObject(new_pen);
	SelectObject(hdc, old_brush);	DeleteObject(new_brush);
}
void AngledArc::fprint(ostream& out) const
{
	this->Shape::fprint(out);
	out << ", radius (" << setw(3) << this->Radius() << "), ";
	out << "startAngle (" << setw(3) << this->StartAngle() << "), ";
	out << "sweepAngle (" << setw(3) << this->SweepAngle() << ")";
}

/*				operator Overloading ( 연산자 오버로드 )
		1. 대입 연산자 ( = )
		2. 출력 연산자 ( << )										*/
AngledArc& AngledArc::operator=(const AngledArc& arc)
{
	this->Shape::operator=(arc);
	this->setStartAng(arc.StartAngle());
	this->setSweepAng(arc.SweepAngle());

	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}
ostream& operator<<(ostream& out, const AngledArc& arc)
{
	out << arc.Name() << " : ";	arc.fprint(out);
	return out;
	// TODO: 여기에 return 문을 삽입합니다.
}
