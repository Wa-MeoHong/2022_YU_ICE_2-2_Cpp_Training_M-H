#include "ConsolePixelDrawing.h"

/*				constructor ( ������ )				*/
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

/*				destructor ( �Ҹ��� )			*/
ConsolePixelFrame::~ConsolePixelFrame()
{
	//delete[] shapes;

	//ReleaseDC(console, console_DC);
}

/*				member functions ( ��� �Լ��� )
		1. addShape(Shape* new_shape)		( ��� �߰� )
		2. drawShape()						( ���� ��� �Լ� )						
		3. isValidIndex(int sub)			( Index ��ȿ�� �˻� )	*/
void ConsolePixelFrame::addShape(Shape* new_shape)
{
	// ���� shapes�� ������ capacity(�迭�� �뷮)���� �� ���� ���ٸ� �迭�� ���Ӱ� ����
	if (num_shapes >= capacity)
	{
		cout << "ConsolePixelFrame::addShape ==> Expanding capacity to "
			<< capacity * 2 << "shapes" << endl;
		Shape** old_shapes = pShapes;

		pShapes = new Shape * [capacity * 2];			// ���Ӱ� �迭�� ���� ( capacity�� 2��� )
		if (pShapes == NULL)							// ���� ������ ���ϸ� Ż��
		{
			cout << "Error in expanding dynamic array for shapes capacity "
				<< capacity * 2 << "shapes" << endl;
			exit(-1);
		}

		for (int i = 0; i < num_shapes; i++)
		{
			pShapes[i] = old_shapes[i];					// ������ �����͸� ���ο� �迭�� ����
		}
		capacity = capacity * 2;						// pShapes�� ������ (�뷮) ����
		delete[] old_shapes;							// ������ ������ �迭 delete
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
			pShapes[i]->draw(*this);					// ���� �׸���
	}
}
bool ConsolePixelFrame::isValidIndex(int sub)
{
	if (sub < 0 || sub >= this->num_shapes)				// �迭�ε��� ��ȣ�� 0���� SIZE-1���̿� �ִ� ��������
	{
		cout << "Error in ConsolePixelFrame::isValidIndex : current number of shapes ("
			<< num_shapes << "), index : " << sub << ") !!" << endl;
		return false;										// �ƴϸ� false, ������ true
	}
		
	else
		return true;
}
