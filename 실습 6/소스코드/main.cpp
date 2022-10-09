/*
  파일명 : "실습6_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 클래스를 생성해서 cmd에 그림을 그려보자
  프로그램 작성자 : 신대홍(2022년 10월 9일)
  최종 Update : Version 1.1.0, 2022년 10월 9일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자	  수정일			버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/10/09		v1.0.0		  최초작성
	신대홍		 2022/10/10		v1.1.0		  완성
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
	// 콘솔창 
	system("mode con:cols=110 lines=40");
	system("color F0");
	cout << "hit any key to continue ...." << endl;
	_getch();

	ConsolePixelFrame frame(50, 50);			// Console창 생성
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
