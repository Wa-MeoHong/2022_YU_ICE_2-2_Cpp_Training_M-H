#ifndef PIXEL_DRAWING_H
#define PIXEL_DRAWING_H

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "Shape.h"
#include "Color.h"

using namespace std;

#define PS_SOLID		0
#define PS_DASH			1
#define PS_DOT			2
#define PS_DASHDOT		3
#define PS_DASHDOTDOT	4
#define PS_NULL			5
#define PS_INSIDEFRAME	6
#define PS_USERSTYLE	7
#define PS_ALTERNATE	8

#define MAX_NUM_SHAPES 100

class Shape;

class ConsolePixelFrame
{
public:
	// constructor
	ConsolePixelFrame(int org_x, int org_y);
	// destuctor
	~ConsolePixelFrame();

	//member functions
	void addShape(Shape* new_shape);		// ���� �߰��ϱ� �Լ�
	void drawShapes();						// ���� �׸��� �Լ�

	//getter
	int Cpfr_Px() { return cpfr_px; }		// cmd X ��ǥ
	int Cpfr_Py() { return cpfr_py; }		// cmd Y ��ǥ
	HDC Console_DC() { return console_DC; }	// HDC���� ��ȯ

private:
	HWND console;
	HDC console_DC;
	Shape** pShapes;
	int num_shapes;
	int capacity;
	int cpfr_px;
	int cpfr_py;
	bool isValidIndex(int sub);				// Index�� ��ȿ�� �˻�
};

#endif // !PIXEL_DRAWING_H
