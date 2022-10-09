#include "Polygon.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. name만 인수를 받는 constructor
		3. 모든 인자를 받는 constructor
		4. 복제생성자								*/
PolyGon::PolyGon()
{
	radius = 0;						// 반지름
	num_poly = 0;					// 각의 개수
}
PolyGon::PolyGon(string name)
	: Shape(name)
{
	radius = 0;						// 반지름
	num_poly = 0;					// 각의 개수
}
PolyGon::PolyGon(int px, int py, int r, int n_poly, double angle, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	: Shape(px, py, angle, ln_clr, br_clr, pen_thick, name)
{
	this->setRadius(r);							// 반지름 대입
	this->setNumPoly(n_poly);					// 각의 개수 대입
}
PolyGon::PolyGon(const PolyGon& poly)
	:Shape(poly.pX(), poly.pY(), poly.angle, poly.line_color, poly.brush_color, poly.pen_thickness, poly.Name())
{
	this->setRadius(poly.Radius());			// 반지름 대입
	this->setNumPoly(poly.NumPoly());		// 각의 개수 대입
}

/*				destructor ( 소멸자 )				*/
PolyGon::~PolyGon()
{
	// cout << "Star class terminated!" << endl;
}

/*				member functions ( 멤버 함수들 )
		1. draw(ConsolePixelFrame cp_frame)
		2. fprint(ostream&) const ( 출력 함수 )		*/
void PolyGon::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;

	// 포인트 객체 배열은 각도의 개수에 따라 다르게 한다.
	POINT* points = new POINT[NumPoly()];
	memset(points, 0, (sizeof(POINT) * NumPoly()));	// 구조체 변수 초기화 
	double rad_angle, delta_angle;					// 라디안으로 각도 조정
	
	int fr_px = cp_frame.Cpfr_Px() + pX();			// 중심점 X 좌표
	int fr_py = cp_frame.Cpfr_Py() + pY();			// 중심점 Y 좌표
	int x, y;

	delta_angle = 2.0 * PI / NumPoly();				// 다각형의 각도 조정
	rad_angle = PI / 2.0;							// 라디안 각도
	for (int i = 0; i < NumPoly(); i++, rad_angle += delta_angle)
	{
		x = fr_px + Radius() * cos(rad_angle);			// 꼭지점 좌표 X좌표
		y = fr_py - Radius() * sin(rad_angle);			// 꼭지점 좌표 Y좌표
		points[i].x = x; points[i].y = y;				// Point 구조체 변수에 대입
	}
	
	// 그림그리기 객체 셜정
	hdc = cp_frame.Console_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	
	Polygon(hdc, points, NumPoly());				// 다각형 그림 그리기

	// 객체 삭제 및 꼭짓점 구조체 삭제
	SelectObject(hdc, old_pen);		DeleteObject(new_pen);
	SelectObject(hdc, old_brush);	DeleteObject(new_brush);
	delete[] points;
}
void PolyGon::fprint(ostream& out) const
{
	this->Shape::fprint(out);
	out << ", radius (" << setw(3) << this->Radius() << "), ";
	out << "num_poly (" << setw(3) << this->NumPoly() << ")";
}

/*				operator Overloading ( 연산자 오버로드 )
		1. 대입 연산자 ( = )
		2. 출력 연산자 ( << )										*/
PolyGon& PolyGon::operator=(const PolyGon& poly)
{
	this->Shape::operator=(poly);
	this->setRadius(poly.Radius());			// 반지름 대입
	this->setNumPoly(poly.NumPoly());		// 각의 개수 대입

	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}
ostream& operator<<(ostream& out, const PolyGon& poly)
{
	out << poly.Name() << " : ";	poly.fprint(out);
	return out;
	// TODO: 여기에 return 문을 삽입합니다.
}
