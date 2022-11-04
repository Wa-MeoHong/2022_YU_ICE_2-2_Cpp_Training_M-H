/*
  ���ϸ� : "�ǽ�8_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- ���ø��� Ȱ���Ͽ� Heap Priority Queue�� �����Ͽ� �̺�Ʈ�� �ٷ��
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 11�� 2��)
  ���� Update : Version 1.0.0, 2022�� 11�� 2��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������	  ������			����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/11/02		v1.0.0		  �����ۼ�
===========================================================================================================
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Event.h"
#include "HeapPrioQ.h"

using namespace std;

#define INITIAL_CBT_CAPA 100
#define TEST_HEAP_PRIO_Q_EVENT
#define NUM_EVENTS 15
#define OUTPUT "output.txt"

int main(void)
{
	ofstream fout;
	string tName = "";
	char tmp[10];
	int priority = -1;					// �켱����
	int current_top_priority;
	int duration = 0;
	int size;
	int* pE;

	// ���� ����
	fout.open(OUTPUT);
	if (fout.fail())
	{
		cout << "Fail to open output.txt file for results !!" << endl;
		exit(-1);
	}

	Event events[NUM_EVENTS] =
	{
		//Event(int evt_no, int evt_pri, string title, int gen_addr)
		Event(0, 14, "evt_00", 0), Event(1, 13, "evt_01", 1), Event(2, 12, "evt_02", 2),
		Event(3, 11, "evt_03", 3), Event(4, 10, "evt_04", 4), Event(5, 9, "evt_05", 5),
		Event(6, 8, "evt_06", 6), Event(7, 7, "evt_07", 7), Event(8, 6, "evt_08", 8),
		Event(9, 5, "evt_09", 9), Event(10, 4, "evt_10", 10), Event(11, 3, "evt_11", 11),
		Event(12, 2, "evt_12", 12), Event(13, 1, "evt_13", 13), Event(14, 0, "evt_14", 14)
	};
	HeapPrioQueue<int, Event*> HeapPriQ_Event(INITIAL_CBT_CAPA, string("Event_Heap_Priority_Queue"));
	Event* pEv;
	T_Entry<int, Event*> entry_event, * pEntry_Event;

	// �̺�Ʈ�� ť�� ����ִ� ��
	for (int i = 0; i < NUM_EVENTS; i++)
	{
		entry_event.SetKey(events[i].EvPri());
		entry_event.SetVal(&events[i]);
		HeapPriQ_Event.insert(entry_event);
		fout << "Insert " << events[i];
		fout << " ==> Size of Heap Priority Queue : " << setw(3) << HeapPriQ_Event.size() << endl;
	}

	fout << "Final status of insertions : " << endl;
	HeapPriQ_Event.fprintCBT_byLevel(fout);			// �������� ����ϴ� �Լ�

	// �̺�Ʈ ó���ϴ� ��
	for (int i = 0; i < NUM_EVENTS; i++)
	{
		fout << "\nCurrent top priority in Heap Priority Queue : ";
		pEntry_Event = HeapPriQ_Event.HeapMin();
		fout << *pEntry_Event << endl;
		pEntry_Event = HeapPriQ_Event.removeHeapMin();
		fout << "Remove " << *pEntry_Event;
		fout << " ==> " << HeapPriQ_Event.size() << " elements remains." << endl;
		HeapPriQ_Event.fprintCBT_byLevel(fout);
		fout << endl;
	}

	fout.close();			// ���� �ݱ�
	return 0;
}


