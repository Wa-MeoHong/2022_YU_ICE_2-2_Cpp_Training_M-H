#ifndef CYLINDER_H
#define CYLINDER_H

#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"

using namespace std;

class Cylinder : public Shape
{
	friend ostream& operator<< (ostream&, const Cylinder&);

public:
	// constructor
	Cylinder();
	Cylinder(string name);
	Cylinder(int px, int py, int r, double angle, int h, COLORREF ln_clr, COLORREF br_clr,
		int pen_thick, string name);
	Cylinder(const Cylinder& cyl);

	// destuctor
	~Cylinder();

	// member functions
	virtual void draw(ConsolePixelFrame cp_frame);			// 도형
	void fprint(ostream&) const;							// Shape 객체 출력

	// getter
	double Area() const;
	int Radius() const { return radius; }
	int Height() const { return height; }

	// setter
	void setRadius(int r) { radius = r; }
	void setHeight(int h) { height = h; }

	// operator Overloading
	Cylinder& operator=(const Cylinder& cyl);
protected:
	int radius;
	int height;
};

#endif // !CYLINDER_H