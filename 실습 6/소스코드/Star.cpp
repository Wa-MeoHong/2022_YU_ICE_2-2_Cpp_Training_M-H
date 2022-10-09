#include "Star.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. name�� �μ��� �޴� constructor
		3. ��� ���ڸ� �޴� constructor
		4. ����������								*/
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

/*				destructor ( �Ҹ��� )				*/
Star::~Star()
{
	// cout << "Star class terminated!" << endl;
}

/*				member functions ( ��� �Լ��� )
		1. draw(ConsolePixelFrame cp_frame)
		2. fprint(ostream&) const ( ��� �Լ� )		*/
void Star::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;

	// ����Ʈ ��ü �迭�� ������ ������ ���� �ٸ��� �Ѵ�.
	POINT* points = new POINT[5];
	memset(points, 0, (sizeof(POINT) * 5));	// ����ü ���� �ʱ�ȭ 

	int fr_px = cp_frame.Cpfr_Px() + pX();		// �߽��� X ��ǥ
	int fr_py = cp_frame.Cpfr_Py() + pY();		// �߽��� Y ��ǥ
	int x, y;
	double delta_angle = 2.0 * PI / 5.0;		// �������� ���� (���� ��) 
	double rad_angle = PI / 2.0;				// �ٰ����� ����

	for (int i = 0; i < 5.0; i++, rad_angle += delta_angle)
	{
		x = fr_px + radius * cos(rad_angle);	// �������� X ��ǥ
		y = fr_py - radius * sin(rad_angle);	// �������� Y ��ǥ
		points[i].x = x; points[i].y = y;		// ������ x, y ��ǥ ����
	}

	// ��ü ���� �� �ʱ�ȭ
	hdc = cp_frame.Console_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	// ���� �׸��� ����
	MoveToEx(hdc, points[0].x, points[0].y, NULL);		// HDC ��ü�� ���� ����(0��)���� �̵�
	LineTo(hdc, points[2].x, points[2].y);				// ��ü�� 2������ �̵��ϸ鼭 ���� �׸�
	LineTo(hdc, points[4].x, points[4].y);				// ��ü�� 4������ �̵��ϸ鼭 ���� �׸�
	LineTo(hdc, points[1].x, points[1].y);				// ��ü�� 1������ �̵��ϸ鼭 ���� �׸�
	LineTo(hdc, points[3].x, points[3].y);				// ��ü�� 3������ �̵��ϸ鼭 ���� �׸�
	LineTo(hdc, points[0].x, points[0].y);				// ��ü�� 0������ �̵��ϸ鼭 ���� �׸�
	
	// HDC ��ü �� ��, �귯�� ��ü ����
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

/*				operator Overloading ( ������ �����ε� )
		1. ���� ������ ( = )
		2. ��� ������ ( << )										*/
Star& Star::operator=(const Star& star)
{
	this->Shape::operator=(star);
	this->setRadius(star.Radius());
	this->setNumVerti(star.NumVerti());

	return *this;
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& out, const Star& star)
{
	out << star.Name() << " : ";	star.fprint(out);
	return out;
	// TODO: ���⿡ return ���� �����մϴ�.
}
