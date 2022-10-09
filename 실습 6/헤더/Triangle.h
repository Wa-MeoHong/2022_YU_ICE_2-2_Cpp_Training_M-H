#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"

using namespace std;

class Triangle : public Shape
{
	friend ostream& operator<< (ostream&, const Triangle&);

public:
	// constructor
	Triangle();
	Triangle(string name);
	Triangle(int px, int py, int b, int h, double angle, COLORREF ln_clr, COLORREF br_clr,
		int pen_thick, string name);
	Triangle(const Triangle& tri);

	// destuctor
	~Triangle();

	//member functions
	virtual void draw(ConsolePixelFrame cp_frame);			// 도형
	void fprint(ostream&) const;							// Shape 객체 출력

	//getter
	double Area() const;
	int Base() const { return base; }
	int Height() const { return tri_height; }

	// setter
	void setBase(int b) { base = b; }
	void setHeight (int h) { tri_height = h; }

	// operator Overloading
	Triangle& operator=(const Triangle& tri);

protected:
	int base;
	int tri_height;
};

#endif // !TRIANGLE_H
