#include "Star.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. name만 인수를 받는 constructor
		3. 모든 인자를 받는 constructor
		4. 복제생성자								*/
Star::Star()
{
	radius = 0;
	num_vertices = 0;
}
Star::Star(string name)
	: Shape(name)
{
	radius = 0;
	num_vertices = 0;
}
Star::Star(int px, int py, int r, int n_verti, double angle, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	: Shape(px, py, angle, ln_clr, br_clr, pen_thick, name)
{
	this->setRadius(r);
	this->setNumVerti(n_verti);
}
Star::Star(const Star& star)
	:Shape(star.pX(), star.pY(), star.angle, star.line_color, star.brush_color, star.pen_thickness, star.Name())
{
	this->setRadius(star.Radius());
	this->setNumVerti(star.NumVerti());
}

/*				destructor ( 소멸자 )				*/
Star::~Star()
{
	// cout << "Star class terminated!" << endl;
}

/*				member functions ( 멤버 함수들 )
		1. draw(ConsolePixelFrame cp_frame)
		2. fprint(ostream&) const ( 출력 함수 )		*/
void Star::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;

	// 포인트 객체 배열은 각도의 개수에 따라 다르게 한다.
	POINT* points = new POINT[5];
	memset(points, 0, (sizeof(POINT) * 5));	// 구조체 변수 초기화 

	int fr_px = cp_frame.Cpfr_Px() + pX();		// 중심점 X 좌표
	int fr_py = cp_frame.Cpfr_Py() + pY();		// 중심점 Y 좌표
	int x, y;
	double delta_angle = 2.0 * PI / 5.0;		// 오각형의 각도 (라디안 값) 
	double rad_angle = PI / 2.0;				// 다각도로 변경

	for (int i = 0; i < 5.0; i++, rad_angle += delta_angle)
	{
		x = fr_px + radius * cos(rad_angle);	// 꼭짓점의 X 좌표
		y = fr_py - radius * sin(rad_angle);	// 꼭짓점의 Y 좌표
		points[i].x = x; points[i].y = y;		// 꼭짓점 x, y 좌표 대입
	}

	// 객체 생성 및 초기화
	hdc = cp_frame.Console_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	// 별을 그리는 과정
	MoveToEx(hdc, points[0].x, points[0].y, NULL);		// HDC 객체를 가장 맨위(0번)으로 이동
	LineTo(hdc, points[2].x, points[2].y);				// 객체를 2번으로 이동하면서 선을 그림
	LineTo(hdc, points[4].x, points[4].y);				// 객체를 4번으로 이동하면서 선을 그림
	LineTo(hdc, points[1].x, points[1].y);				// 객체를 1번으로 이동하면서 선을 그림
	LineTo(hdc, points[3].x, points[3].y);				// 객체를 3번으로 이동하면서 선을 그림
	LineTo(hdc, points[0].x, points[0].y);				// 객체를 0번으로 이동하면서 선을 그림
	
	// HDC 객체 및 펜, 브러시 객체 삭제
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
	delete[] points;
}
void Star::fprint(ostream& out) const
{
	this->Shape::fprint(out);
	out << ", radius (" << setw(3) << this->Radius() << "), ";
	out << "num_vertices (" << setw(3) << this->NumVerti() << ")";
}

/*				operator Overloading ( 연산자 오버로드 )
		1. 대입 연산자 ( = )
		2. 출력 연산자 ( << )										*/
Star& Star::operator=(const Star& star)
{
	this->Shape::operator=(star);
	this->setRadius(star.Radius());
	this->setNumVerti(star.NumVerti());

	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}
ostream& operator<<(ostream& out, const Star& star)
{
	out << star.Name() << " : ";	star.fprint(out);
	return out;
	// TODO: 여기에 return 문을 삽입합니다.
}
