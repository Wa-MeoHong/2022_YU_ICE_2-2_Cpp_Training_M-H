#include "AngledArc.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. name�� �μ��� �޴� constructor
		3. ��� ���ڸ� �޴� constructor
		4. ����������								*/
AngledArc::AngledArc()
{
	radius = 0;
	start_angle = 0;
	sweep_angle = 0;
}
AngledArc::AngledArc(string name)
	: Shape(name)
{
	radius = 0;
	start_angle = 0;
	sweep_angle = 0;
}
AngledArc::AngledArc(int px, int py, int r, double angle, int start_ang, int sweep_ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	: Shape(px, py, angle, ln_clr, br_clr, pen_thick, name)
{
	this->setRadius(r);
	this->setStartAng(start_ang);
	this->setSweepAng(sweep_ang);
}
AngledArc::AngledArc(const AngledArc& arc)
	: Shape(arc.pX(), arc.pY(), arc.angle, arc.line_color, arc.brush_color, arc.pen_thickness, arc.Name())
{
	this->setRadius(arc.Radius());
	this->setStartAng(arc.StartAngle());
	this->setSweepAng(arc.SweepAngle());
}

/*				destructor ( �Ҹ��� )				*/
AngledArc::~AngledArc()
{
	// cout << "AngledArc class terminated!" << endl;
}

/*				member functions ( ��� �Լ��� )
		1. draw(ConsolePixelFrame cp_frame)
		2. fprint(ostream&) const ( ��� �Լ� )		*/
void AngledArc::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	
	int start_px, start_py;
	double start_ang_rad;
	int fr_px = cp_frame.Cpfr_Px() + pX();			// �߽��� X��ǥ
	int fr_py = cp_frame.Cpfr_Py() + pY();			// �߽��� Y��ǥ

	// HDC ��ü ����
	hdc = cp_frame.Console_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	// ó�� �׸��� ��ġ (��������) 
	start_ang_rad = start_angle * PI / 180.0;
	start_px = fr_px + radius * cos(start_ang_rad);			// �׸��� ������ġ x��ǥ
	start_py = fr_py - radius * sin(start_ang_rad);			// �׸��� ������ġ y��ǥ
	
	// �Ѹ� �׸���
	MoveToEx(hdc, fr_px, fr_py, (LPPOINT)NULL);				// �߽���ǥ�� �̵�
	LineTo(hdc, start_px, start_py);						// ���� ��ġ���� ���� �׸�
	AngleArc(hdc, fr_px, fr_py, radius, start_angle, sweep_angle);	// sweep_angle������ ���� �̵�
	LineTo(hdc, fr_px, fr_py);								// �߽���ǥ�� ���� �߱�
	
	// HDC ��ü ����
	SelectObject(hdc, old_pen);		DeleteObject(new_pen);
	SelectObject(hdc, old_brush);	DeleteObject(new_brush);
}
void AngledArc::fprint(ostream& out) const
{
	this->Shape::fprint(out);
	out << ", radius (" << setw(3) << this->Radius() << "), ";
	out << "startAngle (" << setw(3) << this->StartAngle() << "), ";
	out << "sweepAngle (" << setw(3) << this->SweepAngle() << ")";
}

/*				operator Overloading ( ������ �����ε� )
		1. ���� ������ ( = )
		2. ��� ������ ( << )										*/
AngledArc& AngledArc::operator=(const AngledArc& arc)
{
	this->Shape::operator=(arc);
	this->setStartAng(arc.StartAngle());
	this->setSweepAng(arc.SweepAngle());

	return *this;
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& out, const AngledArc& arc)
{
	out << arc.Name() << " : ";	arc.fprint(out);
	return out;
	// TODO: ���⿡ return ���� �����մϴ�.
}
