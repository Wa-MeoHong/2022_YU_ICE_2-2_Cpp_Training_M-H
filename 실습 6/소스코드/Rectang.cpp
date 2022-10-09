#include "Rectang.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. name만 인수를 받는 constructor
		3. 모든 인자를 받는 constructor
		4. 복제생성자								*/
Rectang::Rectang()
{
	width = 0;
	length = 0;
}
Rectang::Rectang(string name)
	: Shape(name)
{
	width = 0;
	length = 0;
}
Rectang::Rectang(int px, int py, int w, int l, double angle, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	: Shape(px, py, angle, ln_clr, br_clr, pen_thick, name)
{
	this->setWidth(w);
	this->setLength(l);
}
Rectang::Rectang(const Rectang& rec)
	:Shape(rec.pX(), rec.pY(), rec.angle, rec.line_color, rec.brush_color, rec.pen_thickness, rec.Name())
{
	this->setWidth(rec.Width());
	this->setLength(rec.Length());
}

/*				destructor ( 소멸자 )				*/
Rectang::~Rectang()
{
	// cout << "Rectang class terminated!" << endl;
}

/*				member functions ( 멤버 함수들 )
		1. draw(ConsolePixelFrame cp_frame)	( 그림 그리기 함수 ) 
		2. fprint(ostream&) const ( 출력 함수 )
		3. Area() const ( 넓이 구하는 함수 )			*/
void Rectang::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;

	int fr_px, fr_py;
	fr_px = cp_frame.Cpfr_Px() + pX();				// cmd x 좌표 (중심점)
	fr_py = cp_frame.Cpfr_Py() + pY();				// cmd y 좌표 (중심점)

	POINT p[4];										// Point 구조체 변수 ( 꼭짓점) 
	p[0].x = fr_px - width / 2; p[0].y = fr_py - length / 2.0;		// 밑변 왼쪽 좌표
	p[1].x = fr_px + width / 2; p[1].y = fr_py - length / 2.0;		// 밑변 오른쪽 좌표
	p[2].x = fr_px + width / 2; p[2].y = fr_py + length / 2.0;		// 윗변 왼쪽 좌표
	p[3].x = fr_px - width / 2; p[3].y = fr_py + length / 2.0;		// 윗변 오른쪽 좌표

	// HDC, HPEN, HBRUSH를 생성
	hdc = cp_frame.Console_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	Polygon(hdc, p, 4);								// 사각형 그림을 그림	

	// 오브젝트 (펜, 브러시 ) delete
	SelectObject(hdc, old_pen);		DeleteObject(new_pen);
	SelectObject(hdc, old_brush);	DeleteObject(new_brush);
}
void Rectang::fprint(ostream& out) const
{
	out.setf(ios::showpoint); out.setf(ios::fixed);				// 고정 소수점 2자리까지만 출력
	out.precision(2);

	this->Shape::fprint(out);
	out << ", width (" << setw(3) << this->Width() << "), ";
	out << "length (" << setw(3) << this->Length() << "), ";
	out << "Area (" << setw(4) << this->Area() << "), ";
}
double Rectang::Area() const
{
	return (Width() * Length());
}

/*				operator Overloading ( 연산자 오버로드 )
		1. 대입 연산자 ( = )
		2. 출력 연산자 ( << )										*/
Rectang& Rectang::operator=(const Rectang& rec)
{
	this->Shape::operator=(rec);
	this->setWidth(rec.Width());
	this->setLength(rec.Length());

	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}
ostream& operator<<(ostream& out, const Rectang& rec)
{
	out << rec.Name() << " : ";	rec.fprint(out);
	return out;
	// TODO: 여기에 return 문을 삽입합니다.
}
