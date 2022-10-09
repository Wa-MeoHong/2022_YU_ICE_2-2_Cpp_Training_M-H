#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"

using namespace std;

class Rectang : public Shape
{
	friend ostream& operator<< (ostream&, const Rectang&);

public:
	// constructor
	Rectang();
	Rectang(string name);
	Rectang(int px, int py, int w, int l, double angle, COLORREF ln_clr, COLORREF br_clr,
		int pen_thick, string name);
	Rectang(const Rectang& rec);

	// destuctor
	~Rectang();

	//member functions
	virtual void draw(ConsolePixelFrame cp_frame);			// 도형
	void fprint(ostream&) const;							// Shape 객체 출력

	//getter
	double Area() const;
	int Width() const { return width; }
	int Length() const { return length; }

	// setter
	void setWidth(int w) { width = w; }
	void setLength(int l) { length = l; }
	
	// operator Overloading
	Rectang& operator=(const Rectang& rec);

protected:
	int width;
	int length;
};

#endif // !RECTANGLE_H
