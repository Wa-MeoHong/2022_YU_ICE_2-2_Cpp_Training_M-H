#include "Event.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. ��� ���ڸ� �޴� constructor				*/
Event::Event()
{
	// LARGE_INTEGER ������ ������ ��� ���� �ʱ�ȭ
	event_no = 0;		event_pri = 0;
	ev_gen_addr = 0;	ev_han_addr = 0;
	t_elapsed_ms = 0.0;
	evstat = GENERATED;

}
Event::Event(int ev_id, int ev_pri, int srcAddr)
{
	// event_no = ev_id, pri = ev_pri �� ����
	// event_genAddr = srcAddr�� ����, �������� 0���� �ʱ�ȭ
	event_no = ev_id;	event_pri = ev_pri;
	ev_gen_addr = srcAddr; ev_han_addr = 0;
	t_elapsed_ms = 0.0;
	evstat = GENERATED;
}

/*				member function	( ��� �Լ� )
		1. PrintEv_Proc() ( ó���� �̺�Ʈ ��� �Լ� )
		2. genRandEvent(evt_no)	( �̺�Ʈ�� ������ �켱������ ���� )	*/
void Event::PrintEv_Proc()
{
	// print format : Ev(no: xx, pri: xx, t_elapsed: xx.xx )
	cout << "Ev(no:" << setw(2) << EvNo() << ", pri: " << setw(2) << EvPri();
	cout.precision(2); cout.setf(ios::fixed);
	cout << "t_elapsed:" << setw(8) << EvElaspedTime() << ")";
}
Event* genRandEvent(int evt_no)
{
	// ���� ����
	Event * pEv;
	int ev_prio;	int ev_gen_id;

	// �̺�Ʈ �켱����, generator id �������� ����
	ev_prio = rand() % MAX_EVENT_PRIORITY;
	ev_gen_id = rand() % NUM_EVENT_GENERATOR;

	// Event ��ü�� �������� ������
	pEv = (Event*) new Event(evt_no, ev_prio, ev_gen_id);
	return pEv;			// ��ȯ
}

/*			operator overloading ( ������ �����ε� )
		1. operator<<(ostr, Ev) ( ��� ������ �����ε� )		*/	
ostream& operator<<(ostream& ostr, const Event& e)
{
	//print format : Event(pri: xxx, gen: xxx, no: xxx)

	ostr << "Event(pri: " << setw(3) << e.EvPri()
		<< ", gen: " << setw(3) << e.ev_gen_addr
		<< ", no: " << setw(3) << e.EvNo() << ")";

	return ostr;
}


