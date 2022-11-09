/*
  파일명 : "실습9_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- 탬플릿, 멀티스레드를 활용하여 Heap Priority Queue를 구성하여 이벤트를 다룬다
  프로그램 작성자 : 신대홍(2022년 11월 6일)
  최종 Update : Version 1.2.0, 2022년 11월 9일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자	  수정일			버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/11/06		v1.0.0		  최초작성
	신대홍		 2022/11/08		v1.1.0		  완성
	신대홍		 2022/11/09		v1.2.0		  Event Generate 할 때, mutex 설정을 통해 insert를 안정적으로 하게함
	신대홍		 2022/11/09		v1.2.1		  TA_Entry 생성할 떄, new로 범위를 capacity + 1하여 안정적으로 하게함
	
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
	// 필요한 변수들
	ofstream fout;
	double min_elapsed, max_elapsed;
	double avg_elapsed, total_elapsed = 0.0;
	HeapPrioQ_CS<int, Event> heapPriQ_Event(PRI_QUEUE_CAPACITY, string("HeapPriorityQueue_Event"));
	Event* pEv = NULL, * pEv_min = NULL, * pEv_max = NULL;

	// 쓰레드를 돌리기 위한 변수들
	ThrdParam thrdParam_EvGen, thrdParam_EvHan;
	mutex cs_main, cs_thrdMon;
	ThrdStatMonitor thrdMon;
	HANDLE consHadlr;
	THREAD_FLAG evThrdFlag = RUN;
	int count, numEvGen, numEvProc, num_events_PriQ;
	LARGE_INTEGER QP_freq;

	// 파일 오픈 (출력 파일) 
	fout.open(OUTPUT);
	if (fout.fail())
	{
		cout << "Error! doesn't open Output.txt !!" << endl;
		exit(-1);
	}

	consHadlr = initConsoleHandler();		// consoleHandler 초기 설정
	QueryPerformanceFrequency(&QP_freq);	// CPU 클럭 측정
	srand((unsigned int)time(NULL));						// 시드 생성

	//  ThrdMon 초기화 ( Flag를 참조하는 주소, 생성/처리된 이벤트 개수, 이벤트들의 현재 상태 초기화 )
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
	thrdParam_EvHan.pCS_main = &cs_main;			// main, thrdMon mutex 설정
	thrdParam_EvHan.pCS_thrd_mon = &cs_thrdMon;
	thrdParam_EvHan.pPriQ_Event = &heapPriQ_Event;		// 이벤트 큐의 메모리 주소( 전체를 들고오기 위함 )
	thrdParam_EvHan.maxRound = MAX_ROUND;
	thrdParam_EvHan.QP_freq = QP_freq;
	thrdParam_EvHan.pThrdMon = &thrdMon;

	thread thrd_EvProc(EventProc, &thrdParam_EvHan);
	cs_main.lock(); cout << "Thread_EvProc is created and activated . . . " << endl; cs_main.unlock();

	/* Create and Activate Thrd_EventGenerator */
	thrdMon.numEvGenerated = 0;
	thrdParam_EvGen.role = EVENT_GENERATOR;
	thrdParam_EvGen.myAddr = 0;						// EvGenerator address 
	thrdParam_EvGen.pCS_main = &cs_main;			// main, thrdMon mutex 설정
	thrdParam_EvGen.pCS_thrd_mon = &cs_thrdMon;
	thrdParam_EvGen.pPriQ_Event = &heapPriQ_Event;		// 이벤트 큐의 메모리 주소( 전체를 들고오기 위함 )
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
		gotoxy(consHadlr, 0, 0);		// (0, 0)으로 커서 좌표 이동

		// 현재 모니터링 중인 이벤트 현재 생성된 수, 처리된 수, 몇번째 round인지 출력
		cout << "Thread monitoring by main() :: " << endl;
		printf(" round(%2d): current total_Event_gen (%2d), total_Event_proc(%2d)\n",
			round, thrdMon.totalGenerated, thrdMon.totalProcessed);

		cout << "\n*********************************************\n";

		// 현재 생성된 이벤트를 보여주는 곳
		numEvGen = thrdMon.numEvGenerated;
		cout << "Event generated (current total = " << setw(2) << numEvGen << ")" << endl;
		
		count = 0;
		for (int ev = 0; ev < numEvGen; ev++)
		{
			// 이벤트를 받아오고, 만약 이벤트를 받아오는데 성공했다면 출력
			pEv = &thrdMon.EvGenerated[ev];
			if (pEv != NULL)
			{
				cout << *pEv << " ";
				if ((ev + 1) % EVENT_PER_LINE == 0)		// 한 줄당 출력하는 이벤트 수는 정해져있음
					cout << endl;
			}
		}
		cout << endl;

		cout << "\n*********************************************\n";
		num_events_PriQ = heapPriQ_Event.size();
		printf("Event currently in Priority Queue (%d) : \n", num_events_PriQ);
		heapPriQ_Event.fprint(cout);					// 수정이 필요한 곳

		cout << "\n\n*********************************************\n";
		numEvProc = thrdMon.totalProcessed;
		cout << "Event processed (current total = " << setw(2) << numEvProc << ")" << endl;

		count = 0;
		total_elapsed = 0.0;							// 처음 생성한 이벤트의 시간 ~ 마지막으로 처리된 이벤트 시간
		for (int ev = 0; ev < numEvProc; ev++)
		{
			// 처리된 이벤트 출력
			pEv = &thrdMon.EvProcessed[ev];
			if (pEv != NULL)
			{
				pEv->PrintEv_Proc();
				cout << " ";
				if ((ev + 1) % EVENT_PER_LINE == 0)		// 한 줄당 출력하는 이벤트 수는 정해져있음
					cout << endl;
			}
			// 만약 ev가 처음이라면( 0이라면 )
			if (ev == 0)
			{
				// 최대시간이 걸린, 최소시간이 걸린 이벤트를 초기화함
				min_elapsed = max_elapsed = total_elapsed = pEv->EvElaspedTime();	
				pEv_min = pEv_max = pEv;
			}
			else
			{
				// 생성-처리까지 최소/최대로 걸린 이벤트 선정
				if (min_elapsed > pEv->EvElaspedTime())
				{
					min_elapsed = pEv->EvElaspedTime(); pEv_min = pEv;
				}
				if (max_elapsed < pEv->EvElaspedTime())
				{
					max_elapsed = pEv->EvElaspedTime(); pEv_max = pEv;
				}
				// 총 걸린 시간을 측정
				total_elapsed += pEv->EvElaspedTime();
			}
		}
		cout << endl;

		// 만약 처리된 이벤트가 존재한다면, 최소시간, 최대시간이 걸린 Event를 찾는다.
		if (numEvProc > 0)
		{
			// 최소시간, 최대시간, 평균시간을 출력함
			cout << "numEventProcessed = " << numEvProc << endl;
			printf("min_elapsed time = %8.2lf[ms]; ", min_elapsed);
			cout << *pEv_min << endl;
			printf("max_elapsed time = %8.2lf[ms]; ", max_elapsed);
			cout << *pEv_max << endl;
			avg_elapsed = total_elapsed / numEvProc;
			printf("avg_elapsed time = %8.2lf[ms]; ", avg_elapsed);
		}
		// 만약 이벤트가 전부 처리되었다면 쓰레드를 Terminate 한다.
		// 아직 덜 끝났다면 반복문을 탈출하지 않고 계속 돈다.
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

	thrd_EvGen.join();			// 쓰레드 thrd_EvGen가 TERMINATED되기를 대기하고있음
	thrd_EvProc.join();			// 쓰레드 thrd_EvProc가 TERMINATED되기를 대기하고있음
	
	fout.close();

	cout << "\nHit any key to terminated : ";
	_getch();

	return 0;
}