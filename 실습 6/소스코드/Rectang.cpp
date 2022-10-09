#include "Rectang.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. name�� �μ��� �޴� constructor
		3. ��� ���ڸ� �޴� constructor
		4. ����������								*/
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

/*				destructor ( �Ҹ��� )				*/
Rectang::~Rectang()
{
	// cout << "Rectang class terminated!" << endl;
}

/*				member functions ( ��� �Լ��� )
		1. draw(ConsolePixelFrame cp_frame)	( �׸� �׸��� �Լ� ) 
		2. fprint(ostream&) const ( ��� �Լ� )
		3. Area() const ( ���� ���ϴ� �Լ� )			*/
void Rectang::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;

	int fr_px, fr_py;
	fr_px = cp_frame.Cpfr_Px() + pX();				// cmd x ��ǥ (�߽���)
	fr_py = cp_frame.Cpfr_Py() + pY();				// cmd y ��ǥ (�߽���)

	POINT p[4];										// Point ����ü ���� ( ������) 
	p[0].x = fr_px - width / 2; p[0].y = fr_py - length / 2.0;		// �غ� ���� ��ǥ
	p[1].x = fr_px + width / 2; p[1].y = fr_py - length / 2.0;		// �غ� ������ ��ǥ
	p[2].x = fr_px + width / 2; p[2].y = fr_py + length / 2.0;		// ���� ���� ��ǥ
	p[3].x = fr_px - width / 2; p[3].y = fr_py + length / 2.0;		// ���� ������ ��ǥ

	// HDC, HPEN, HBRUSH�� ����
	hdc = cp_frame.Console_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	Polygon(hdc, p, 4);								// �簢�� �׸��� �׸�	

	// ������Ʈ (��, �귯�� ) delete
	SelectObject(hdc, old_pen);		DeleteObject(new_pen);
	SelectObject(hdc, old_brush);	DeleteObject(new_brush);
}
void Rectang::fprint(ostream& out) const
{
	out.setf(ios::showpoint); out.setf(ios::fixed);				// ���� �Ҽ��� 2�ڸ������� ���
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

/*				operator Overloading ( ������ �����ε� )
		1. ���� ������ ( = )
		2. ��� ������ ( << )										*/
Rectang& Rectang::operator=(const Rectang& rec)
{
	this->Shape::operator=(rec);
	this->setWidth(rec.Width());
	this->setLength(rec.Length());

	return *this;
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& out, const Rectang& rec)
{
	out << rec.Name() << " : ";	rec.fprint(out);
	return out;
	// TODO: ���⿡ return ���� �����մϴ�.
}
