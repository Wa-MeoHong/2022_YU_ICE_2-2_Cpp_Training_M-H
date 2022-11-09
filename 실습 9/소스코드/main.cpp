/*
  ���ϸ� : "�ǽ�9_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- ���ø�, ��Ƽ�����带 Ȱ���Ͽ� Heap Priority Queue�� �����Ͽ� �̺�Ʈ�� �ٷ��
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 11�� 6��)
  ���� Update : Version 1.2.0, 2022�� 11�� 9��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������	  ������			����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/11/06		v1.0.0		  �����ۼ�
	�Ŵ�ȫ		 2022/11/08		v1.1.0		  �ϼ�
	�Ŵ�ȫ		 2022/11/09		v1.2.0		  Event Generate �� ��, mutex ������ ���� insert�� ���������� �ϰ���
	�Ŵ�ȫ		 2022/11/09		v1.2.1		  TA_Entry ������ ��, new�� ������ capacity + 1�Ͽ� ���������� �ϰ���
	
===========================================================================================================
*/

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <mutex>
#include <thread>

#include "MultiThread.h"
#include "HeapPrioQ.h"
#include "Event.h"
#include "ConsoleDisplay.h"
#include "SimParam.h"

#include <time.h>
#include <conio.h>

using namespace std;
using std::this_thread::sleep_for;

#define OUTPUT "output.txt"

int main(void)
{
	// �ʿ��� ������
	ofstream fout;
	double min_elapsed, max_elapsed;
	double avg_elapsed, total_elapsed = 0.0;
	HeapPrioQ_CS<int, Event> heapPriQ_Event(PRI_QUEUE_CAPACITY, string("HeapPriorityQueue_Event"));
	Event* pEv = NULL, * pEv_min = NULL, * pEv_max = NULL;

	// �����带 ������ ���� ������
	ThrdParam thrdParam_EvGen, thrdParam_EvHan;
	mutex cs_main, cs_thrdMon;
	ThrdStatMonitor thrdMon;
	HANDLE consHadlr;
	THREAD_FLAG evThrdFlag = RUN;
	int count, numEvGen, numEvProc, num_events_PriQ;
	LARGE_INTEGER QP_freq;

	// ���� ���� (��� ����) 
	fout.open(OUTPUT);
	if (fout.fail())
	{
		cout << "Error! doesn't open Output.txt !!" << endl;
		exit(-1);
	}

	consHadlr = initConsoleHandler();		// consoleHandler �ʱ� ����
	QueryPerformanceFrequency(&QP_freq);	// CPU Ŭ�� ����
	srand((unsigned int)time(NULL));						// �õ� ����

	//  ThrdMon �ʱ�ȭ ( Flag�� �����ϴ� �ּ�, ����/ó���� �̺�Ʈ ����, �̺�Ʈ���� ���� ���� �ʱ�ȭ )
	thrdMon.pFlagThreadTerminated = &evThrdFlag;
	thrdMon.totalGenerated = 0; thrdMon.totalProcessed = 0;
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.EvGenerated[ev].SetEvNo(-1);
		thrdMon.EvGenerated[ev].SetEvPri(-1);
	}

	/* Create and Activate Thrd_EventHandler */
	thrdMon.nuMEvProcessed = 0;
	thrdParam_EvHan.role = EVENT_HANDLER;
	thrdParam_EvHan.myAddr = 1;						// EvHandler address 
	thrdParam_EvHan.pCS_main = &cs_main;			// main, thrdMon mutex ����
	thrdParam_EvHan.pCS_thrd_mon = &cs_thrdMon;
	thrdParam_EvHan.pPriQ_Event = &heapPriQ_Event;		// �̺�Ʈ ť�� �޸� �ּ�( ��ü�� ������ ���� )
	thrdParam_EvHan.maxRound = MAX_ROUND;
	thrdParam_EvHan.QP_freq = QP_freq;
	thrdParam_EvHan.pThrdMon = &thrdMon;

	thread thrd_EvProc(EventProc, &thrdParam_EvHan);
	cs_main.lock(); cout << "Thread_EvProc is created and activated . . . " << endl; cs_main.unlock();

	/* Create and Activate Thrd_EventGenerator */
	thrdMon.numEvGenerated = 0;
	thrdParam_EvGen.role = EVENT_GENERATOR;
	thrdParam_EvGen.myAddr = 0;						// EvGenerator address 
	thrdParam_EvGen.pCS_main = &cs_main;			// main, thrdMon mutex ����
	thrdParam_EvGen.pCS_thrd_mon = &cs_thrdMon;
	thrdParam_EvGen.pPriQ_Event = &heapPriQ_Event;		// �̺�Ʈ ť�� �޸� �ּ�( ��ü�� ������ ���� )
	thrdParam_EvGen.targetEventGen = NUM_EVENTS_PER_GEN;
	thrdParam_EvGen.maxRound = MAX_ROUND;
	thrdParam_EvGen.QP_freq = QP_freq;
	thrdParam_EvGen.pThrdMon = &thrdMon;

	thread thrd_EvGen(EventGen, &thrdParam_EvGen);
	cs_main.lock(); cout << "Thread_EvGen is created and activated . . . " << endl; cs_main.unlock();

	for (int round = 0; round < MAX_ROUND; round++)
	{
		cs_main.lock();
		cls(consHadlr);		// clear CMD screen
		gotoxy(consHadlr, 0, 0);		// (0, 0)���� Ŀ�� ��ǥ �̵�

		// ���� ����͸� ���� �̺�Ʈ ���� ������ ��, ó���� ��, ���° round���� ���
		cout << "Thread monitoring by main() :: " << endl;
		printf(" round(%2d): current total_Event_gen (%2d), total_Event_proc(%2d)\n",
			round, thrdMon.totalGenerated, thrdMon.totalProcessed);

		cout << "\n*********************************************\n";

		// ���� ������ �̺�Ʈ�� �����ִ� ��
		numEvGen = thrdMon.numEvGenerated;
		cout << "Event generated (current total = " << setw(2) << numEvGen << ")" << endl;
		
		count = 0;
		for (int ev = 0; ev < numEvGen; ev++)
		{
			// �̺�Ʈ�� �޾ƿ���, ���� �̺�Ʈ�� �޾ƿ��µ� �����ߴٸ� ���
			pEv = &thrdMon.EvGenerated[ev];
			if (pEv != NULL)
			{
				cout << *pEv << " ";
				if ((ev + 1) % EVENT_PER_LINE == 0)		// �� �ٴ� ����ϴ� �̺�Ʈ ���� ����������
					cout << endl;
			}
		}
		cout << endl;

		cout << "\n*********************************************\n";
		num_events_PriQ = heapPriQ_Event.size();
		printf("Event currently in Priority Queue (%d) : \n", num_events_PriQ);
		heapPriQ_Event.fprint(cout);					// ������ �ʿ��� ��

		cout << "\n\n*********************************************\n";
		numEvProc = thrdMon.totalProcessed;
		cout << "Event processed (current total = " << setw(2) << numEvProc << ")" << endl;

		count = 0;
		total_elapsed = 0.0;							// ó�� ������ �̺�Ʈ�� �ð� ~ ���������� ó���� �̺�Ʈ �ð�
		for (int ev = 0; ev < numEvProc; ev++)
		{
			// ó���� �̺�Ʈ ���
			pEv = &thrdMon.EvProcessed[ev];
			if (pEv != NULL)
			{
				pEv->PrintEv_Proc();
				cout << " ";
				if ((ev + 1) % EVENT_PER_LINE == 0)		// �� �ٴ� ����ϴ� �̺�Ʈ ���� ����������
					cout << endl;
			}
			// ���� ev�� ó���̶��( 0�̶�� )
			if (ev == 0)
			{
				// �ִ�ð��� �ɸ�, �ּҽð��� �ɸ� �̺�Ʈ�� �ʱ�ȭ��
				min_elapsed = max_elapsed = total_elapsed = pEv->EvElaspedTime();	
				pEv_min = pEv_max = pEv;
			}
			else
			{
				// ����-ó������ �ּ�/�ִ�� �ɸ� �̺�Ʈ ����
				if (min_elapsed > pEv->EvElaspedTime())
				{
					min_elapsed = pEv->EvElaspedTime(); pEv_min = pEv;
				}
				if (max_elapsed < pEv->EvElaspedTime())
				{
					max_elapsed = pEv->EvElaspedTime(); pEv_max = pEv;
				}
				// �� �ɸ� �ð��� ����
				total_elapsed += pEv->EvElaspedTime();
			}
		}
		cout << endl;

		// ���� ó���� �̺�Ʈ�� �����Ѵٸ�, �ּҽð�, �ִ�ð��� �ɸ� Event�� ã�´�.
		if (numEvProc > 0)
		{
			// �ּҽð�, �ִ�ð�, ��սð��� �����
			cout << "numEventProcessed = " << numEvProc << endl;
			printf("min_elapsed time = %8.2lf[ms]; ", min_elapsed);
			cout << *pEv_min << endl;
			printf("max_elapsed time = %8.2lf[ms]; ", max_elapsed);
			cout << *pEv_max << endl;
			avg_elapsed = total_elapsed / numEvProc;
			printf("avg_elapsed time = %8.2lf[ms]; ", avg_elapsed);
		}
		// ���� �̺�Ʈ�� ���� ó���Ǿ��ٸ� �����带 Terminate �Ѵ�.
		// ���� �� �����ٸ� �ݺ����� Ż������ �ʰ� ��� ����.
		if (numEvProc >= TOTAL_NUM_EVENTS)
		{
			evThrdFlag = TERMINATE;
			cs_main.unlock();
			//sleep_for(std::chrono::milliseconds(0));	// == <windows.h> sleep(500);
			break;
		}
		cs_main.unlock();
		Sleep(100);
	}

	thrd_EvGen.join();			// ������ thrd_EvGen�� TERMINATED�Ǳ⸦ ����ϰ�����
	thrd_EvProc.join();			// ������ thrd_EvProc�� TERMINATED�Ǳ⸦ ����ϰ�����
	
	fout.close();

	cout << "\nHit any key to terminated : ";
	_getch();

	return 0;
}