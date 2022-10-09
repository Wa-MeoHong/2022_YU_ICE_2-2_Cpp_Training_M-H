#include "Cylinder.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. name만 인수를 받는 constructor
		3. 모든 인자를 받는 constructor
		4. 복제생성자								*/
Cylinder::Cylinder()
{
	radius = 0;
	height = 0;
}
Cylinder::Cylinder(string name)
	:Shape(name)
{
	radius = 0;
	height = 0;
}
Cylinder::Cylinder(int px, int py, int r, double angle, int h, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	: Shape(px, py, angle, ln_clr, br_clr, pen_thick, name)
{
	this->setRadius(r);				// 반지름 대입
	this->setHeight(h);				// 높이 대입
}
Cylinder::Cylinder(const Cylinder& cyl)
	: Shape(cyl.pX(), cyl.pY(), cyl.angle, cyl.line_color, cyl.brush_color, cyl.pen_thickness, cyl.Name())
{
	this->setRadius(cyl.Radius());			// 반지름 대입
	this->setHeight(cyl.Height());			// 높이 대입
}

/*				destructor ( 소멸자 )				*/
Cylinder::~Cylinder()
{
	// cout << "Cylinder class terminated!" << endl;
}

/*				member functions ( 멤버 함수들 )
		1. draw(ConsolePixelFrame cp_frame)
		2. fprint(ostream&) const ( 출력 함수 )		
		3. Area() const		( 원기둥 겉넓이 )			*/
void Cylinder::draw(ConsolePixelFrame cp_frame)
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc = cp_frame.Console_DC();
	
	// 객체 펜, 브러시 생성
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	int cx = cp_frame.Cpfr_Px() + pX();				// 중심 좌표 X좌표
	int cy = cp_frame.Cpfr_Py() + pY();				// 중심 좌표 Y좌표
	
	// 원기둥을 그림
	MoveToEx(hdc, (cx - radius), (cy - height / 2), (LPPOINT)NULL);		// 먼저 원기둥의 옆면을 구현하기 위해 윗변 왼쪽으로 이동 
	LineTo(hdc, (cx - radius), (cy + height / 2));						// 원기둥 높이를 그림 (왼쪽)	
	MoveToEx(hdc, (cx + radius), (cy - height / 2), (LPPOINT)NULL);		// 원기둥 옆면 구현을 위한 윗변 오른쪽으로 이동
	LineTo(hdc, (cx + radius), (cy + height / 2));						// 원기둥 높이를 그림 (오른쪽)
	Ellipse(hdc, (cx - radius), (cy - height / 2) - 20, (cx + radius), (cy - height / 2) + 20);	// 윗면 원을 그림
	MoveToEx(hdc, cx - radius, cy + height / 2, (LPPOINT)NULL);		// 아랫면면으로 이동
	ArcTo(hdc, cx - radius, cy + height / 2 - 20, cx + radius, cy + height / 2 + 20, cx - radius, cy + height / 2,
		cx + radius, cy + height / 2);								// 아랫면은 원이 아니므로 원처럼 선을 그어줌

	// 객체 삭제
	SelectObject(hdc, old_pen); DeleteObject(new_pen);
	SelectObject(hdc, old_brush); DeleteObject(new_brush);
}
void Cylinder::fprint(ostream& out) const
{
	out.setf(ios::showpoint); out.setf(ios::fixed);				// 고정 소수점 2자리까지만 출력
	out.precision(2);

	this->Shape::fprint(out);
	out << ", radius (" << setw(3) << this->Radius() << "), ";
	out << "height (" << setw(3) << this->Height() << "), ";
	out << "area (" << setw(4) << this->Area() << ")";
}
double Cylinder::Area() const
{
	double round, basearea;

	round = double(2 * this->Radius()) * PI;			// 밑면 원주
	basearea = PI * pow(double(Radius()), 2);			// 밑면 넓이

	return (2 * basearea) + (round * Height());
}

/*				operator Overloading ( 연산자 오버로드 )
		1. 대입 연산자 ( = )
		2. 출력 연산자 ( << )										*/
Cylinder& Cylinder::operator=(const Cylinder& cyl)
{
	this->Shape::operator=(cyl);
	this->setRadius(cyl.Radius());			// 반지름 대입
	this->setHeight(cyl.Height());			// 높이 대입

	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}
ostream& operator<<(ostream& out, const Cylinder& cyl)
{
	out << cyl.Name() << " : ";	cyl .fprint(out);
	return out;
	// TODO: 여기에 return 문을 삽입합니다.
}
