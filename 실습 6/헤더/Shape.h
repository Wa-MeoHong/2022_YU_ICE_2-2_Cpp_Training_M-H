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

class Shape									// Shape Å¬·¡½º ( ¸ð¾ç ) 
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
	virtual void draw();									// µµÇü ±×¸®±â ÇÔ¼ö
	virtual void draw(ConsolePixelFrame cp_frame);			// µµÇü
	void fprint(ostream&) const;							// Shape °´Ã¼ Ãâ·Â

	//getter
	int pX() const { return px; }			// X ÁÂÇ¥
	int pY() const { return py; }			// Y ÁÂÇ¥
	string Name() const { return name; }	// ÀÌ¸§
	//setter 
	void set_pX(int x) { px = x; }			// X ÁÂÇ¥ ¼³Á¤
	void set_pY(int y) { py = y; }			// Y ÁÂÇ¥ ¼³Á¤
	void NameSet(string n) { name = n; }	// ÀÌ¸§ ¼³Á¤

	// operator Overloading
	Shape& operator=(const Shape& s);

protected:
	int px;									// X ÁÂÇ¥
	int py;									// Y ÁÂÇ¥
	double angle;							// °¢µµ
	string name;							// ÀÌ¸§
	int pen_thickness;						// ÆæÀÇ ±½±â
	COLORREF line_color;					// ¼± »ö±ò
	COLORREF brush_color;					// ºê·¯½Ã ( Ã¤¿ì±â ) »ö±ò
};

#endif // !SHAPE_H
