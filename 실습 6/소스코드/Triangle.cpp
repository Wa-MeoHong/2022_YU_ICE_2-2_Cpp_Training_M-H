#include "Triangle.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. name�� �μ��� �޴� constructor
		3. ��� ���ڸ� �޴� constructor
		4. ����������								*/
Triangle::Triangle()
{
	base = 0;					// �غ� �ʱ�ȭ
	tri_height = 0;				// ���� �ʱ�ȭ
}
Triangle::Triangle(string name)
	: Shape(name)
{
	base = 0;				// �غ� �ʱ�ȭ
	tri_height = 0;			// ���� �ʱ�ȭ
}
Triangle::Triangle(int px, int py, int b, int h, double angle, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	: Shape(px, py, angle, ln_clr, br_clr, pen_thick, name)
{
	this->setBase(b);				// �غ� ����
	this->setHeight(h);				// ���� ����
}
Triangle::Triangle(const Triangle& tri)
	:Shape(tri.pX(), tri.pY(), tri.angle, tri.line_color, tri.brush_color, tri.pen_thickness, tri.Name())
{
	this->setBase(tri.Base());		// �غ� ����
	this->setHeight(tri.Height());	// ���� ����
}

/*				destructor ( �Ҹ��� )				*/
Triangle::~Triangle()
{
	// cout << "Triangle class terminated!" << endl;
}

/*				member functions ( ��� �Լ��� )
		1. draw(ConsolePixelFrame cp_frame) ( �׸� �׸��� �Լ� )
		2. fprint(ostream&) const ( ��� �Լ� )	
		3. Area() const ( ���� ���ϴ� �Լ� )			*/
void Triangle::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;

	int fr_px, fr_py;
	fr_px = cp_frame.Cpfr_Px() + pX();				// cmd x ��ǥ (�߽���)
	fr_py = cp_frame.Cpfr_Py() + pY();				// cmd y ��ǥ (�߽���)

	POINT p[3];										// Point ����ü ���� ( ������) 
	p[0].x = fr_px - base / 2; p[0].y = fr_py + tri_height * 1.0 / 2.0;		// �غ� ���� ��ǥ
	p[1].x = fr_px + base / 2; p[1].y = fr_py + tri_height * 1.0 / 2.0;		// �غ� ������ ��ǥ
	p[2].x = fr_px; p[2].y = fr_py - tri_height * 1.0 / 2.0;				// ���� ���� �ʿ� �ִ� ��ǥ 
	
	// HDC, HPEN, HBRUSH�� ����
	hdc = cp_frame.Console_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	Polygon(hdc, p, 3);					// �ﰢ�� �׸��� �׸�	

	// ������Ʈ (��, �귯�� ) delete
	SelectObject(hdc, old_pen);		DeleteObject(new_pen);
	SelectObject(hdc, old_brush);	DeleteObject(new_brush);
}
void Triangle::fprint(ostream& out) const
{
	out.setf(ios::showpoint); out.setf(ios::fixed);				// ���� �Ҽ��� 2�ڸ������� ���
	out.precision(2);

	// ��� ���� : ��ǥ - �غ�, ���� - ���� - ����(��, �귯��)
	this->Shape::fprint(out);
	out << ", base (" << setw(3) << this->Base() << "), ";
	out << "height (" << setw(3) << this->Height() << "), ";
	out << "Area (" << setw(4) << this->Area() << "), ";
}
double Triangle::Area() const
{
	return ((double(Base()) * double(Height())) / 2 );
}

/*				operator Overloading ( ������ �����ε� )
		1. ���� ������ ( = )
		2. ��� ������ ( << )										*/
Triangle& Triangle::operator=(const Triangle& tri)
{
	this->Shape::operator=(tri);
	this->setBase(tri.Base());
	this->setHeight(tri.Height());

	return *this;
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& out, const Triangle& tri)
{
	out << tri.Name() << " : ";	tri.fprint(out);
	return out;
	// TODO: ���⿡ return ���� �����մϴ�.
}
