#include "ConsolePixelDrawing.h"

/*				constructor ( 생성자 )				*/
ConsolePixelFrame::ConsolePixelFrame(int org_x, int org_y)	
{
	console = GetConsoleWindow();
	console_DC = GetDC(console);
	pShapes= new Shape* [MAX_NUM_SHAPES];
	num_shapes = 0;
	capacity = MAX_NUM_SHAPES;

	cpfr_px = org_x;
	cpfr_py = org_y;
}

/*				destructor ( 소멸자 )			*/
ConsolePixelFrame::~ConsolePixelFrame()
{
	//delete[] shapes;

	//ReleaseDC(console, console_DC);
}

/*				member functions ( 멤버 함수들 )
		1. addShape(Shape* new_shape)		( 모양 추가 )
		2. drawShape()						( 도형 출력 함수 )						
		3. isValidIndex(int sub)			( Index 유효성 검사 )	*/
void ConsolePixelFrame::addShape(Shape* new_shape)
{
	// 만약 shapes의 개수가 capacity(배열의 용량)보다 더 많아 진다면 배열을 새롭게 만듦
	if (num_shapes >= capacity)
	{
		cout << "ConsolePixelFrame::addShape ==> Expanding capacity to "
			<< capacity * 2 << "shapes" << endl;
		Shape** old_shapes = pShapes;

		pShapes = new Shape * [capacity * 2];			// 새롭게 배열을 생성 ( capacity는 2배로 )
		if (pShapes == NULL)							// 만약 생성을 못하면 탈출
		{
			cout << "Error in expanding dynamic array for shapes capacity "
				<< capacity * 2 << "shapes" << endl;
			exit(-1);
		}

		for (int i = 0; i < num_shapes; i++)
		{
			pShapes[i] = old_shapes[i];					// 기존의 데이터를 새로운 배열에 대입
		}
		capacity = capacity * 2;						// pShapes의 데이터 (용량) 갱신
		delete[] old_shapes;							// 기존의 데이터 배열 delete
	}

	pShapes[num_shapes] = new_shape;
	num_shapes++;
}
void ConsolePixelFrame::drawShapes()
{
	cout << "Drawing " << num_shapes << " shapes : " << endl;
	if (num_shapes > 0)
	{
		for (int i = 0; i < num_shapes; i++)
			pShapes[i]->draw(*this);					// 도형 그리기
	}
}
bool ConsolePixelFrame::isValidIndex(int sub)
{
	if (sub < 0 || sub >= this->num_shapes)				// 배열인덱스 번호가 0부터 SIZE-1사이에 있는 숫자인지
	{
		cout << "Error in ConsolePixelFrame::isValidIndex : current number of shapes ("
			<< num_shapes << "), index : " << sub << ") !!" << endl;
		return false;										// 아니면 false, 맞으면 true
	}
		
	else
		return true;
}
