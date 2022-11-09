/* Thread_EventGenerator cpp file */

#include <Windows.h>
#include "HeapPrioQ.h"
#include "MultiThread.h"
#include "Event.h"
#include "SimParam.h"

using namespace std;
using std::this_thread::sleep_for;

void EventGen(ThrdParam* pParam)					// 이벤트 제너레이팅 쓰레드 함수
{
	// pParam의 변수들을 좀 더 쉽게 쓰기위해 지역변수화 시킴
	HeapPrioQueue<int, Event>* pPriQ_Ev = pParam->pPriQ_Event;
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int targetGen = pParam->targetEventGen;
	LARGE_INTEGER QP_freq = pParam->QP_freq;
	ThrdStatMonitor* pThrdMon = pParam->pThrdMon;

	// 쓰일 변수들 
	T_Entry<int, Event> entry_event;
	Event ev;

	int ev_no = 0;
	int ev_pri = 0;
	int ev_gen_count = 0;
	int ev_handler_addr = 0;
	LARGE_INTEGER t_gen;

	// MaxRound까지 돌 때까지 혹은, 쓰레드가 Terminated될 때까짖
	for (int round = 0; round < maxRound; round++)
	{
		if (ev_gen_count >= targetGen)
		{
			// 만약 쓰레드 상태가 TERMINATED라면 이 반복문을 탈출
			if (*pThrdMon->pFlagThreadTerminated == TERMINATE)
				// TERMINATE 상태라면 모든 쓰레드에 걸린 mutex를 전부 언락시킨후 반복문을 탈출한다.		
			{
				break;
			}
			else
			{
				// if ((pParam->pCS_thrd_mon->try_lock()))
				//	pParam->pCS_thrd_mon->unlock();
				sleep_for(std::chrono::milliseconds(50));	// == <windows.h> sleep(500)
				continue;									// TERMINATED가 될 때까지 for문을 반복한다.
			}
		}
		
		ev_no = ev_gen_count + NUM_EVENTS_PER_GEN * myAddr;	// ev_no = 제너레이터의 주소에 따라 정해짐
		ev_pri = targetGen - ev_gen_count - 1;				// ev_pri = 최근에 생성된 것이 우선순위가 더 높음
		
		// 이벤트의 기본적인 정보를 설정
		ev.SetEvNo(ev_no);	ev.SetEvPri(ev_pri);			// ev_no, ev_pri, EvGenAddr, EvHanAddr 설정
		ev.SetEvGenAddr(myAddr);	ev.SetEvHanAddr(-1);
		
		// 이벤트가 Generate 된 시간을 측정
		QueryPerformanceCounter(&t_gen);
		ev.SetEvGenTime(t_gen);
		ev.SetEvStatus(GENERATED);
	
		entry_event.SetKey(ev.EvPri());
		entry_event.SetVal(ev);


		// 만약 이벤트를 큐에 넣을 수 없는 상황이 된다면(insert 반환값이 NULL이라면)
		// 큐가 가득찼다는 메세지를 출력, 쓰레드로 돌고 있으므로 While로 계속 반복시킨다.

		do
		{
			pParam->pCS_main->lock();					// mutex로 먼저 쓰레드를 잠금
			if (pPriQ_Ev->insert(entry_event) != NULL)
			{
				pParam->pCS_main->unlock();					// 다시 언락
				break;
			}
			cout << "PriQ_Event is Full, waiting . . . " << endl;
			pParam->pCS_main->unlock();
			sleep_for(std::chrono::milliseconds(100));	// == <windows.h> sleep(100)
		}while (pEv == NULL);								// 일단 먼저 반복해본다

		pParam->pCS_main->lock();					// mutex로 먼저 쓰레드를 잠금
		// while문에 들어가지 않았으면 성공적으로 이벤트를 집어넣었다는 메세지를 출력한다.
		cout << "Successfully inserted into Prio_Ev " << endl;
		pParam->pCS_main->unlock();

		// Thread Monitoring Parameter를 최신화한다.
		pParam->pCS_thrd_mon->lock();
		pThrdMon->EvGenerated[pThrdMon->totalGenerated] = ev;		// 생성된 이벤트를 집어넣음
		pThrdMon->numEvGenerated++; pThrdMon->totalGenerated++;		// 총 생성된 이벤트 개수를 갱신
		pParam->pCS_thrd_mon->unlock();

		ev_gen_count++;
		sleep_for(std::chrono::milliseconds(10));	// == <windows.h> sleep(10)
	}
}