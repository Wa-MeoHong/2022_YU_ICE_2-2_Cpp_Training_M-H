/* Thread_EventHandler cpp file */

#include <Windows.h>
#include "HeapPrioQ.h"
#include "MultiThread.h"
#include "Event.h"
#include "SimParam.h"

using namespace std;
using std::this_thread::sleep_for;

void EventProc(ThrdParam* pParam)					// �̺�Ʈ ���μ��� ������ �Լ�
{
	// pParam�� �������� ���� ���� ���� ���� ��������ȭ
	HeapPrioQueue<int, Event>* pPriQ_Ev = pParam->pPriQ_Event;
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int targetGen = pParam->targetEventGen;
	LARGE_INTEGER QP_freq = pParam->QP_freq;
	ThrdStatMonitor* pThrdMon = pParam->pThrdMon;

	// ���� ������ 
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
		// ���� ������ ���°� TERMINATED��� �� �ݺ����� Ż��
		if (*pThrdMon->pFlagThreadTerminated == TERMINATE)
		{
			// TERMINATE ���¶�� ��� �����忡 �ɸ� mutex�� ���� �����Ų�� �ݺ����� Ż���Ѵ�.
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

			// ó���� �ð�, ����-ó������ �ɸ� �ð�(elapsed_time) ���� �� ����
			QueryPerformanceCounter(&t_proc);
			ev.SetEvProcTime(t_proc);					// �̺�Ʈ�� ����
			t_gen = ev.EvGenT();
			t_diff = t_proc.QuadPart - t_gen.QuadPart;		// ó���� �ð� - ������ �ð�
			elapsed_time = ((double)t_diff / QP_freq.QuadPart) * Milli;		// freq�� ������ �ʷ� ȯ������, ms�� ȯ���Ѵ�.
			ev.SetEvElapsedTime(elapsed_time);				// ����

			// ó���� �̺�Ʈ�� �迭�� �ְ�, ���� �ֽ�ȭ
			pThrdMon->EvProcessed[pThrdMon->totalProcessed] = ev;
			pThrdMon->nuMEvProcessed++;	pThrdMon->totalProcessed++;
			pParam->pCS_thrd_mon->unlock();
		}
		sleep_for(std::chrono::milliseconds(100 + rand() % 100));	// == <windows.h> sleep(100 + rand() % 100)
	}
}