#include "Circle.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. name�� �μ��� �޴� constructor
		3. ��� ���ڸ� �޴� constructor				
		4. ����������								*/
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

/*				destructor ( �Ҹ��� )				*/
Circle::~Circle()
{
	// cout << "Circle class terminated!" << endl;
}

/*				member functions ( ��� �Լ��� )
		1. draw(ConsolePixelFrame cp_frame) ( �׸� �׸��� �Լ� )
		2. fprint(ostream&) const ( ��� �Լ� )				
		3. Area() const			( ���� ���ϴ� �Լ�)*/
void Circle::draw(ConsolePixelFrame cp_frame)
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc;
	int fr_px, fr_py;							// �߽���

	fr_px = cp_frame.Cpfr_Px() + pX();			// �߽� X��ǥ
	fr_py = cp_frame.Cpfr_Py() + pY();			// �߽� Y��ǥ
	hdc = cp_frame.Console_DC();				// HDC ��ü

	// ��, �귯�� ����
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	
	// ���� �׸�
	Ellipse(hdc, fr_px - radius, fr_py - radius, fr_px + radius, fr_py + radius);
	
	// HDC��ü ����
	SelectObject(hdc, old_pen);		DeleteObject(new_pen);
	SelectObject(hdc, old_brush);	DeleteObject(new_brush);
}
void Circle::fprint(ostream& out) const
{
	out.setf(ios::showpoint); out.setf(ios::fixed);				// ���� �Ҽ��� 2�ڸ������� ���
	out.precision(2);

	// ��� ���� : ��ǥ - ������ - ���� - ����(��, �귯��)
	this->Shape::fprint(out);
	out << ", radius (" << setw(3) << this->Radius() << "), ";
	out << ", area (" << setw(4) << this->Area() << ")";
}
double Circle::Area() const
{
	return (PI * pow(double(Radius()), 2));
}

/*				operator Overloading ( ������ �����ε� )
		1. ���� ������ ( = )
		2. ��� ������ ( << )										*/
Circle& Circle::operator=(const Circle& cir)
{
	this->Shape::operator=(cir);
	this->setRadius(cir.Radius());

	return *this;
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& out, const Circle& cir)
{
	out << cir.Name() << " : ";	cir.fprint(out);
	return out;
	// TODO: ���⿡ return ���� �����մϴ�.
}
