#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"

using namespace std;

class Circle : public Shape
{
	friend ostream& operator<< (ostream&, const Circle&);

public:
	// constructor
	Circle();
	Circle(string name);
	Circle(int px, int py, int r, double angle, COLORREF ln_clr, COLORREF br_clr,
		int pen_thick, string name);
	Circle(const Circle& cir);

	// destuctor
	~Circle();

	// member functions
	virtual void draw(ConsolePixelFrame cp_frame);			// 도형
	void fprint(ostream&) const;							// Shape 객체 출력

	// getter
	double Area() const;
	int Radius() const { return radius; }

	// setter
	void setRadius(int r) { radius = r; }

	// operator Overloading
	Circle& operator=(const Circle& cir);

protected:
	int radius;
};

#endif // !CIRCLE_H