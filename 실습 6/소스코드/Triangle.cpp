#include "Triangle.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. name만 인수를 받는 constructor
		3. 모든 인자를 받는 constructor
		4. 복제생성자								*/
Triangle::Triangle()
{
	base = 0;					// 밑변 초기화
	tri_height = 0;				// 높이 초기화
}
Triangle::Triangle(string name)
	: Shape(name)
{
	base = 0;				// 밑변 초기화
	tri_height = 0;			// 높이 초기화
}
Triangle::Triangle(int px, int py, int b, int h, double angle, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	: Shape(px, py, angle, ln_clr, br_clr, pen_thick, name)
{
	this->setBase(b);				// 밑변 대입
	this->setHeight(h);				// 높이 대입
}
Triangle::Triangle(const Triangle& tri)
	:Shape(tri.pX(), tri.pY(), tri.angle, tri.line_color, tri.brush_color, tri.pen_thickness, tri.Name())
{
	this->setBase(tri.Base());		// 밑변 복사
	this->setHeight(tri.Height());	// 높이 복사
}

/*				destructor ( 소멸자 )				*/
Triangle::~Triangle()
{
	// cout << "Triangle class terminated!" << endl;
}

/*				member functions ( 멤버 함수들 )
		1. draw(ConsolePixelFrame cp_frame) ( 그림 그리기 함수 )
		2. fprint(ostream&) const ( 출력 함수 )	
		3. Area() const ( 넓이 구하는 함수 )			*/
void Triangle::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;

	int fr_px, fr_py;
	fr_px = cp_frame.Cpfr_Px() + pX();				// cmd x 좌표 (중심점)
	fr_py = cp_frame.Cpfr_Py() + pY();				// cmd y 좌표 (중심점)

	POINT p[3];										// Point 구조체 변수 ( 꼭짓점) 
	p[0].x = fr_px - base / 2; p[0].y = fr_py + tri_height * 1.0 / 2.0;		// 밑변 왼쪽 좌표
	p[1].x = fr_px + base / 2; p[1].y = fr_py + tri_height * 1.0 / 2.0;		// 밑변 오른쪽 좌표
	p[2].x = fr_px; p[2].y = fr_py - tri_height * 1.0 / 2.0;				// 가장 높은 쪽에 있는 좌표 
	
	// HDC, HPEN, HBRUSH를 생성
	hdc = cp_frame.Console_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	Polygon(hdc, p, 3);					// 삼각형 그림을 그림	

	// 오브젝트 (펜, 브러시 ) delete
	SelectObject(hdc, old_pen);		DeleteObject(new_pen);
	SelectObject(hdc, old_brush);	DeleteObject(new_brush);
}
void Triangle::fprint(ostream& out) const
{
	out.setf(ios::showpoint); out.setf(ios::fixed);				// 고정 소수점 2자리까지만 출력
	out.precision(2);

	// 출력 순서 : 좌표 - 밑변, 높이 - 각도 - 색깔(선, 브러시)
	this->Shape::fprint(out);
	out << ", base (" << setw(3) << this->Base() << "), ";
	out << "height (" << setw(3) << this->Height() << "), ";
	out << "Area (" << setw(4) << this->Area() << "), ";
}
double Triangle::Area() const
{
	return ((double(Base()) * double(Height())) / 2 );
}

/*				operator Overloading ( 연산자 오버로드 )
		1. 대입 연산자 ( = )
		2. 출력 연산자 ( << )										*/
Triangle& Triangle::operator=(const Triangle& tri)
{
	this->Shape::operator=(tri);
	this->setBase(tri.Base());
	this->setHeight(tri.Height());

	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}
ostream& operator<<(ostream& out, const Triangle& tri)
{
	out << tri.Name() << " : ";	tri.fprint(out);
	return out;
	// TODO: 여기에 return 문을 삽입합니다.
}
