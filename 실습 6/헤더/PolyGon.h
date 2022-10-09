#ifndef POLYGON_H
#define POLYGON_H

#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"

using namespace std;

class PolyGon : public Shape
{
	friend ostream& operator<< (ostream&, const PolyGon&);

public:
	// constructor
	PolyGon();
	PolyGon(string name);
	PolyGon(int px, int py, int r, int n_poly, double angle, COLORREF ln_clr, COLORREF br_clr,
		int pen_thick, string name);
	PolyGon(const PolyGon& poly);

	// destuctor
	~PolyGon();

	//member functions
	virtual void draw(ConsolePixelFrame cp_frame);			// 도형
	void fprint(ostream&) const;							// Shape 객체 출력

	//getter
	int Radius() const { return radius; }
	int NumPoly() const { return num_poly; }

	// setter
	void setRadius(int r) { radius = r; }
	void setNumPoly(int n_poly) { num_poly = n_poly; }

	// operator Overloading
	PolyGon& operator=(const PolyGon& poly);

protected:
	int radius;
	int num_poly;
};

#endif // !POLYGON_H