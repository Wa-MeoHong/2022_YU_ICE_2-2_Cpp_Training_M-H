#include "Shape.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. name�� �μ��� �޴� constructor
		3. ��� ���ڸ� �޴� constructor				*/

Shape::Shape()
{
	px = py = 0;								// ��ǥ�� ���� (0, 0)
	angle = 0.0;								// ���� 0.0���� �ʱ�ȭ
	name = "no_name";							// �̸��� ����
	line_color = brush_color = RGB_BLACK;		// ����Ʈ �ʱⰪ�� ���������� ����
}
Shape::Shape(string name)
{
	px = py = 0;								// ��ǥ�� ���� (0, 0)
	angle = 0.0;								// ���� 0.0���� �ʱ�ȭ
	NameSet(name);								// �̸� ����
	line_color = brush_color = RGB_BLACK;		// ����Ʈ �ʱⰪ�� ���������� ����
}
Shape::Shape(int px, int py, double angle, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	: angle(angle), line_color(ln_clr), brush_color(br_clr), pen_thickness(pen_thick)
{
	// �������� function initializer�� ó���� 
	set_pX(px);									// ��ǥ ����
	set_pY(py);	
	NameSet(name);								// �̸� ����
}

/*				destructor ( �Ҹ��� )				*/
Shape::~Shape()
{
	// cout << "Shape class terminated!" << endl;
}

/*				member functions ( ��� �Լ��� )
		1. draw(ConsolePixelFrame cp_frame)
		  (virtual�� �����Ͽ���, sub-class���� �����ǿ뵵�� ����)
		2. fprint(ostream&) const ( ��� �Լ� )				*/
void Shape::draw()
{
	//draw
}
void Shape::draw(ConsolePixelFrame cp_frame)
{
	/* virtual function that will be late-binded to sub-class's draw() */
}
void Shape::fprint(ostream& out) const
{
	// ��� ���� : ��ǥ - ���� - ����(��, �귯��)
	out << "pos (" << setw(3) << this->pX() << ", " << setw(3) << this->pY() << "), ";
	out << "line_color(";	printRGB(out, line_color); out << "), ";
	out << "brush_color("; printRGB(out, brush_color); out << ")";
}

/*				operator Overloading ( ������ �����ε� )
		1. ���� ������ ( = )
		2. ��� ������ ( << )										*/
Shape& Shape::operator=(const Shape& s)
{
	this->px = s.pX(); this->py = s.pY();
	this->angle = s.angle;
	this->NameSet(s.Name());
	line_color = s.line_color;
	brush_color = s.brush_color;

	return *this;
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& out, const Shape s)
{
	out << s.Name() << ": ";	s.fprint(out);

	return out;
	// TODO: ���⿡ return ���� �����մϴ�.
}
