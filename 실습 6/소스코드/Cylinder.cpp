#include "Cylinder.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. name�� �μ��� �޴� constructor
		3. ��� ���ڸ� �޴� constructor
		4. ����������								*/
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
	this->setRadius(r);				// ������ ����
	this->setHeight(h);				// ���� ����
}
Cylinder::Cylinder(const Cylinder& cyl)
	: Shape(cyl.pX(), cyl.pY(), cyl.angle, cyl.line_color, cyl.brush_color, cyl.pen_thickness, cyl.Name())
{
	this->setRadius(cyl.Radius());			// ������ ����
	this->setHeight(cyl.Height());			// ���� ����
}

/*				destructor ( �Ҹ��� )				*/
Cylinder::~Cylinder()
{
	// cout << "Cylinder class terminated!" << endl;
}

/*				member functions ( ��� �Լ��� )
		1. draw(ConsolePixelFrame cp_frame)
		2. fprint(ostream&) const ( ��� �Լ� )		
		3. Area() const		( ����� �ѳ��� )			*/
void Cylinder::draw(ConsolePixelFrame cp_frame)
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc = cp_frame.Console_DC();
	
	// ��ü ��, �귯�� ����
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	int cx = cp_frame.Cpfr_Px() + pX();				// �߽� ��ǥ X��ǥ
	int cy = cp_frame.Cpfr_Py() + pY();				// �߽� ��ǥ Y��ǥ
	
	// ������� �׸�
	MoveToEx(hdc, (cx - radius), (cy - height / 2), (LPPOINT)NULL);		// ���� ������� ������ �����ϱ� ���� ���� �������� �̵� 
	LineTo(hdc, (cx - radius), (cy + height / 2));						// ����� ���̸� �׸� (����)	
	MoveToEx(hdc, (cx + radius), (cy - height / 2), (LPPOINT)NULL);		// ����� ���� ������ ���� ���� ���������� �̵�
	LineTo(hdc, (cx + radius), (cy + height / 2));						// ����� ���̸� �׸� (������)
	Ellipse(hdc, (cx - radius), (cy - height / 2) - 20, (cx + radius), (cy - height / 2) + 20);	// ���� ���� �׸�
	MoveToEx(hdc, cx - radius, cy + height / 2, (LPPOINT)NULL);		// �Ʒ�������� �̵�
	ArcTo(hdc, cx - radius, cy + height / 2 - 20, cx + radius, cy + height / 2 + 20, cx - radius, cy + height / 2,
		cx + radius, cy + height / 2);								// �Ʒ����� ���� �ƴϹǷ� ��ó�� ���� �׾���

	// ��ü ����
	SelectObject(hdc, old_pen); DeleteObject(new_pen);
	SelectObject(hdc, old_brush); DeleteObject(new_brush);
}
void Cylinder::fprint(ostream& out) const
{
	out.setf(ios::showpoint); out.setf(ios::fixed);				// ���� �Ҽ��� 2�ڸ������� ���
	out.precision(2);

	this->Shape::fprint(out);
	out << ", radius (" << setw(3) << this->Radius() << "), ";
	out << "height (" << setw(3) << this->Height() << "), ";
	out << "area (" << setw(4) << this->Area() << ")";
}
double Cylinder::Area() const
{
	double round, basearea;

	round = double(2 * this->Radius()) * PI;			// �ظ� ����
	basearea = PI * pow(double(Radius()), 2);			// �ظ� ����

	return (2 * basearea) + (round * Height());
}

/*				operator Overloading ( ������ �����ε� )
		1. ���� ������ ( = )
		2. ��� ������ ( << )										*/
Cylinder& Cylinder::operator=(const Cylinder& cyl)
{
	this->Shape::operator=(cyl);
	this->setRadius(cyl.Radius());			// ������ ����
	this->setHeight(cyl.Height());			// ���� ����

	return *this;
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& out, const Cylinder& cyl)
{
	out << cyl.Name() << " : ";	cyl .fprint(out);
	return out;
	// TODO: ���⿡ return ���� �����մϴ�.
}
