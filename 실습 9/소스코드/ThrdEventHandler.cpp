/* Thread_EventHandler cpp file */

#include <Windows.h>
#include "HeapPrioQ.h"
#include "MultiThread.h"
#include "Event.h"
#include "SimParam.h"

using namespace std;
using std::this_thread::sleep_for;

void EventProc(ThrdParam* pParam)					// 이벤트 프로세싱 쓰레드 함수
{
	// pParam의 변수들을 좀더 쉽게 쓰기 위해 지역변수화
	HeapPrioQueue<int, Event>* pPriQ_Ev = pParam->pPriQ_Event;
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int targetGen = pParam->targetEventGen;
	LARGE_INTEGER QP_freq = pParam->QP_freq;
	ThrdStatMonitor* pThrdMon = pParam->pThrdMon;

	// 쓰일 변수들 
	T_Entry<int, Event> *pEntry;
	Event ev;

	int ev_no = 0, ev_pri = 0;
	int ev_gen_count = 0;
	int num_Ev_processed = 0;
	LARGE_INTEGER t_gen, t_proc;
	LONGLONG t_diff;
	double elapsed_time = 0.0;

	for (int round = 0; round < maxRound; round++)
	{
		// 만약 쓰레드 상태가 TERMINATED라면 이 반복문을 탈출
		if (*pThrdMon->pFlagThreadTerminated == TERMINATE)
		{
			// TERMINATE 상태라면 모든 쓰레드에 걸린 mutex를 전부 언락시킨후 반복문을 탈출한다.
			break;
		}

		if (!(pPriQ_Ev->isEmpty()))
		{
			//pParam->pCS_main->lock();
			pEntry = pPriQ_Ev->removeHeapMin();
			//pParam->pCS_main->unlock();

			ev = pEntry->Val();

			pParam->pCS_thrd_mon->lock();
			ev.SetEvHanAddr(myAddr);

			// 처리된 시간, 생성-처리까지 걸린 시간(elapsed_time) 산출 후 저장
			QueryPerformanceCounter(&t_proc);
			ev.SetEvProcTime(t_proc);					// 이벤트에 저장
			t_gen = ev.EvGenT();
			t_diff = t_proc.QuadPart - t_gen.QuadPart;		// 처리된 시간 - 생성된 시간
			elapsed_time = ((double)t_diff / QP_freq.QuadPart) * Milli;		// freq과 나누어 초로 환산한후, ms로 환산한다.
			ev.SetEvElapsedTime(elapsed_time);				// 저장

			// 처리된 이벤트를 배열에 넣고, 개수 최신화
			pThrdMon->EvProcessed[pThrdMon->totalProcessed] = ev;
			pThrdMon->nuMEvProcessed++;	pThrdMon->totalProcessed++;
			pParam->pCS_thrd_mon->unlock();
		}
		sleep_for(std::chrono::milliseconds(100 + rand() % 100));	// == <windows.h> sleep(100 + rand() % 100)
	}
}