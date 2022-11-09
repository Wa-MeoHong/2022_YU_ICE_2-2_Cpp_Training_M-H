/* Thread_EventGenerator cpp file */

#include <Windows.h>
#include "HeapPrioQ.h"
#include "MultiThread.h"
#include "Event.h"
#include "SimParam.h"

using namespace std;
using std::this_thread::sleep_for;

void EventGen(ThrdParam* pParam)					// �̺�Ʈ ���ʷ����� ������ �Լ�
{
	// pParam�� �������� �� �� ���� �������� ��������ȭ ��Ŵ
	HeapPrioQueue<int, Event>* pPriQ_Ev = pParam->pPriQ_Event;
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int targetGen = pParam->targetEventGen;
	LARGE_INTEGER QP_freq = pParam->QP_freq;
	ThrdStatMonitor* pThrdMon = pParam->pThrdMon;

	// ���� ������ 
	T_Entry<int, Event> entry_event;
	Event ev;

	int ev_no = 0;
	int ev_pri = 0;
	int ev_gen_count = 0;
	int ev_handler_addr = 0;
	LARGE_INTEGER t_gen;

	// MaxRound���� �� ������ Ȥ��, �����尡 Terminated�� ����¢
	for (int round = 0; round < maxRound; round++)
	{
		if (ev_gen_count >= targetGen)
		{
			// ���� ������ ���°� TERMINATED��� �� �ݺ����� Ż��
			if (*pThrdMon->pFlagThreadTerminated == TERMINATE)
				// TERMINATE ���¶�� ��� �����忡 �ɸ� mutex�� ���� �����Ų�� �ݺ����� Ż���Ѵ�.		
			{
				break;
			}
			else
			{
				// if ((pParam->pCS_thrd_mon->try_lock()))
				//	pParam->pCS_thrd_mon->unlock();
				sleep_for(std::chrono::milliseconds(50));	// == <windows.h> sleep(500)
				continue;									// TERMINATED�� �� ������ for���� �ݺ��Ѵ�.
			}
		}
		
		ev_no = ev_gen_count + NUM_EVENTS_PER_GEN * myAddr;	// ev_no = ���ʷ������� �ּҿ� ���� ������
		ev_pri = targetGen - ev_gen_count - 1;				// ev_pri = �ֱٿ� ������ ���� �켱������ �� ����
		
		// �̺�Ʈ�� �⺻���� ������ ����
		ev.SetEvNo(ev_no);	ev.SetEvPri(ev_pri);			// ev_no, ev_pri, EvGenAddr, EvHanAddr ����
		ev.SetEvGenAddr(myAddr);	ev.SetEvHanAddr(-1);
		
		// �̺�Ʈ�� Generate �� �ð��� ����
		QueryPerformanceCounter(&t_gen);
		ev.SetEvGenTime(t_gen);
		ev.SetEvStatus(GENERATED);
	
		entry_event.SetKey(ev.EvPri());
		entry_event.SetVal(ev);


		// ���� �̺�Ʈ�� ť�� ���� �� ���� ��Ȳ�� �ȴٸ�(insert ��ȯ���� NULL�̶��)
		// ť�� ����á�ٴ� �޼����� ���, ������� ���� �����Ƿ� While�� ��� �ݺ���Ų��.

		do
		{
			pParam->pCS_main->lock();					// mutex�� ���� �����带 ���
			if (pPriQ_Ev->insert(entry_event) != NULL)
			{
				pParam->pCS_main->unlock();					// �ٽ� ���
				break;
			}
			cout << "PriQ_Event is Full, waiting . . . " << endl;
			pParam->pCS_main->unlock();
			sleep_for(std::chrono::milliseconds(100));	// == <windows.h> sleep(100)
		}while (pEv == NULL);								// �ϴ� ���� �ݺ��غ���

		pParam->pCS_main->lock();					// mutex�� ���� �����带 ���
		// while���� ���� �ʾ����� ���������� �̺�Ʈ�� ����־��ٴ� �޼����� ����Ѵ�.
		cout << "Successfully inserted into Prio_Ev " << endl;
		pParam->pCS_main->unlock();

		// Thread Monitoring Parameter�� �ֽ�ȭ�Ѵ�.
		pParam->pCS_thrd_mon->lock();
		pThrdMon->EvGenerated[pThrdMon->totalGenerated] = ev;		// ������ �̺�Ʈ�� �������
		pThrdMon->numEvGenerated++; pThrdMon->totalGenerated++;		// �� ������ �̺�Ʈ ������ ����
		pParam->pCS_thrd_mon->unlock();

		ev_gen_count++;
		sleep_for(std::chrono::milliseconds(10));	// == <windows.h> sleep(10)
	}
}