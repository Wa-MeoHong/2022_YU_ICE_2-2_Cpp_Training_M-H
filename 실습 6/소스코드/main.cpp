/*
  ���ϸ� : "�ǽ�6_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- Ŭ������ �����ؼ� cmd�� �׸��� �׷�����
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 10�� 9��)
  ���� Update : Version 1.1.0, 2022�� 10�� 9��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������	  ������			����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/10/09		v1.0.0		  �����ۼ�
	�Ŵ�ȫ		 2022/10/10		v1.1.0		  �ϼ�
===========================================================================================================
*/

#include <iostream>
#include <string>
#include <fstream>
#include "ConsolePixelDrawing.h"
#include "Shape.h"

#include "Triangle.h"
#include "Circle.h"
#include "Rectang.h"
#include "Polygon.h"
#include "Star.h"
#include "AngledArc.h"
#include "Cylinder.h"

using namespace std;

int main(void)
{
	// �ܼ�â 
	system("mode con:cols=110 lines=40");
	system("color F0");
	cout << "hit any key to continue ...." << endl;
	_getch();

	ConsolePixelFrame frame(50, 50);			// Consoleâ ����
	Circle cir(100, 200, 80, 0, RGB_BLACK, RGB_RED, 3, "Circle");
	Triangle tri(300, 200, 150, 130, 0, RGB_BLACK, RGB_YELLOW, 3, "Triangle");
	Rectang rec(500, 200, 150, 150, 0, RGB_BLACK, RGB_BLUE, 4, "Rectangle");
	PolyGon poly_5(700, 200, 80, 5, 0, RGB_BLACK, RGB_GREEN, 4, "Polygon_5");
	PolyGon poly_7(100, 400, 80, 7, 0, RGB_BLACK, RGB_MAGENTA, 4, "Polygon_7");
	Star star_5(300, 400, 80, 5, 0, RGB_BLACK, RGB_GREEN, 4, "Star_5");
	AngledArc angle_arc(500, 400, 80, 0, 45, 270, RGB_RED, RGB_BLUE, 4, "Angle_Arc");
	Cylinder cyl(700, 400, 80, 0, 100, RGB_BLUE, RGB_WHITE, 4, "Cylinder");


	frame.addShape(&cir);
	frame.addShape(&tri);
	frame.addShape(&rec);
	frame.addShape(&poly_5);
	frame.addShape(&poly_7);
	frame.addShape(&star_5);
	frame.addShape(&angle_arc);
	frame.addShape(&cyl);

	frame.drawShapes();
	cout << "hit any key to continue ...." << endl;
	_getch();

	return 0;
}
