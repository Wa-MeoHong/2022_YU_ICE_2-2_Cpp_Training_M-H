#ifndef ANGLEDARC_H
#define ANGLEDARC_H

#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"

using namespace std;

class AngledArc : public Shape
{
	friend ostream& operator<< (ostream&, const AngledArc&);

public:
	// constructor
	AngledArc();
	AngledArc(string name);
	AngledArc(int px, int py, int r, double angle, int start_ang, int sweep_ang, COLORREF ln_clr, COLORREF br_clr,
		int pen_thick, string name);
	AngledArc(const AngledArc& arc);

	// destuctor
	~AngledArc();

	// member functions
	virtual void draw(ConsolePixelFrame cp_frame);			// 도형
	void fprint(ostream&) const;							// Shape 객체 출력

	// getter
	int Radius() const { return radius; }
	int StartAngle() const { return start_angle; }
	int SweepAngle() const { return sweep_angle; }
	
	// setter
	void setRadius(int r) { radius = r; }
	void setStartAng(int start_ang) { start_angle = start_ang; }
	void setSweepAng(int sweep_ang) { sweep_angle = sweep_ang; }
	
	// operator Overloading
	AngledArc& operator=(const AngledArc& arc);

protected:
	int radius;
	int start_angle;
	int sweep_angle;
};

#endif // !ANGLEDARC_H
