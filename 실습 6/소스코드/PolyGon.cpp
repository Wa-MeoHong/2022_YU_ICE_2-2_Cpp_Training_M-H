#include "Polygon.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. name�� �μ��� �޴� constructor
		3. ��� ���ڸ� �޴� constructor
		4. ����������								*/
PolyGon::PolyGon()
{
	radius = 0;						// ������
	num_poly = 0;					// ���� ����
}
PolyGon::PolyGon(string name)
	: Shape(name)
{
	radius = 0;						// ������
	num_poly = 0;					// ���� ����
}
PolyGon::PolyGon(int px, int py, int r, int n_poly, double angle, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	: Shape(px, py, angle, ln_clr, br_clr, pen_thick, name)
{
	this->setRadius(r);							// ������ ����
	this->setNumPoly(n_poly);					// ���� ���� ����
}
PolyGon::PolyGon(const PolyGon& poly)
	:Shape(poly.pX(), poly.pY(), poly.angle, poly.line_color, poly.brush_color, poly.pen_thickness, poly.Name())
{
	this->setRadius(poly.Radius());			// ������ ����
	this->setNumPoly(poly.NumPoly());		// ���� ���� ����
}

/*				destructor ( �Ҹ��� )				*/
PolyGon::~PolyGon()
{
	// cout << "Star class terminated!" << endl;
}

/*				member functions ( ��� �Լ��� )
		1. draw(ConsolePixelFrame cp_frame)
		2. fprint(ostream&) const ( ��� �Լ� )		*/
void PolyGon::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;

	// ����Ʈ ��ü �迭�� ������ ������ ���� �ٸ��� �Ѵ�.
	POINT* points = new POINT[NumPoly()];
	memset(points, 0, (sizeof(POINT) * NumPoly()));	// ����ü ���� �ʱ�ȭ 
	double rad_angle, delta_angle;					// �������� ���� ����
	
	int fr_px = cp_frame.Cpfr_Px() + pX();			// �߽��� X ��ǥ
	int fr_py = cp_frame.Cpfr_Py() + pY();			// �߽��� Y ��ǥ
	int x, y;

	delta_angle = 2.0 * PI / NumPoly();				// �ٰ����� ���� ����
	rad_angle = PI / 2.0;							// ���� ����
	for (int i = 0; i < NumPoly(); i++, rad_angle += delta_angle)
	{
		x = fr_px + Radius() * cos(rad_angle);			// ������ ��ǥ X��ǥ
		y = fr_py - Radius() * sin(rad_angle);			// ������ ��ǥ Y��ǥ
		points[i].x = x; points[i].y = y;				// Point ����ü ������ ����
	}
	
	// �׸��׸��� ��ü ����
	hdc = cp_frame.Console_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	
	Polygon(hdc, points, NumPoly());				// �ٰ��� �׸� �׸���

	// ��ü ���� �� ������ ����ü ����
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

/*				operator Overloading ( ������ �����ε� )
		1. ���� ������ ( = )
		2. ��� ������ ( << )										*/
PolyGon& PolyGon::operator=(const PolyGon& poly)
{
	this->Shape::operator=(poly);
	this->setRadius(poly.Radius());			// ������ ����
	this->setNumPoly(poly.NumPoly());		// ���� ���� ����

	return *this;
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& out, const PolyGon& poly)
{
	out << poly.Name() << " : ";	poly.fprint(out);
	return out;
	// TODO: ���⿡ return ���� �����մϴ�.
}
