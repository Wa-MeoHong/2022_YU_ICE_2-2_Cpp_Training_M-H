#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <Windows.h>
#include <conio.h>
#include "Color.h"
#include "ConsolePixelDrawing.h"

using namespace std;
#define PI 3.14159265358979323846			// pi

class ConsolePixelFrame;

class Shape									// Shape Ŭ���� ( ��� ) 
{
	friend ostream& operator<<(ostream& out, const Shape s);
public:
	// constructor
	Shape();
	Shape(string name);
	Shape(int px, int py, double angle, COLORREF ln_clr, COLORREF br_clr,
		int pen_thick, string name);
	// destuctor
	virtual ~Shape();

	//member functions
	virtual void draw();									// ���� �׸��� �Լ�
	virtual void draw(ConsolePixelFrame cp_frame);			// ����
	void fprint(ostream&) const;							// Shape ��ü ���

	//getter
	int pX() const { return px; }			// X ��ǥ
	int pY() const { return py; }			// Y ��ǥ
	string Name() const { return name; }	// �̸�
	//setter 
	void set_pX(int x) { px = x; }			// X ��ǥ ����
	void set_pY(int y) { py = y; }			// Y ��ǥ ����
	void NameSet(string n) { name = n; }	// �̸� ����

	// operator Overloading
	Shape& operator=(const Shape& s);

protected:
	int px;									// X ��ǥ
	int py;									// Y ��ǥ
	double angle;							// ����
	string name;							// �̸�
	int pen_thickness;						// ���� ����
	COLORREF line_color;					// �� ����
	COLORREF brush_color;					// �귯�� ( ä��� ) ����
};

#endif // !SHAPE_H
