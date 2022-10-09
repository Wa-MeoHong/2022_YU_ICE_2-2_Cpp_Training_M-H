#ifndef STAR_H
#define STAR_H

#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"

using namespace std;

class Star : public Shape
{
	friend ostream& operator<< (ostream&, const Star&);

public:
	// constructor
	Star();
	Star(string name);
	Star(int px, int py, int r, int n_verti, double angle, COLORREF ln_clr, COLORREF br_clr,
		int pen_thick, string name);
	Star(const Star& star);

	// destuctor
	~Star();

	//member functions
	virtual void draw(ConsolePixelFrame cp_frame);			// 도형
	void fprint(ostream&) const;							// Shape 객체 출력

	//getter
	int Radius() const { return radius; };
	int NumVerti() const { return num_vertices; }

	// setter
	void setRadius(int r) { radius = r; }
	void setNumVerti(int n_verti) { num_vertices = n_verti; }
	
	// operator Overloading
	Star& operator=(const Star& star);

protected:
	int radius;
	int num_vertices;
};

#endif // !STAR_H
