#include "Event.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. 모든 인자를 받는 constructor				*/
Event::Event()
{
	// LARGE_INTEGER 변수를 제외한 모든 변수 초기화
	event_no = 0;		event_pri = 0;
	ev_gen_addr = 0;	ev_han_addr = 0;
	t_elapsed_ms = 0.0;
	evstat = GENERATED;

}
Event::Event(int ev_id, int ev_pri, int srcAddr)
{
	// event_no = ev_id, pri = ev_pri 로 설정
	// event_genAddr = srcAddr로 설정, 나머지는 0으로 초기화
	event_no = ev_id;	event_pri = ev_pri;
	ev_gen_addr = srcAddr; ev_han_addr = 0;
	t_elapsed_ms = 0.0;
	evstat = GENERATED;
}

/*				member function	( 멤버 함수 )
		1. PrintEv_Proc() ( 처리된 이벤트 출력 함수 )
		2. genRandEvent(evt_no)	( 이벤트를 랜덤한 우선순위로 생성 )	*/
void Event::PrintEv_Proc()
{
	// print format : Ev(no: xx, pri: xx, t_elapsed: xx.xx )
	cout << "Ev(no:" << setw(2) << EvNo() << ", pri: " << setw(2) << EvPri();
	cout.precision(2); cout.setf(ios::fixed);
	cout << "t_elapsed:" << setw(8) << EvElaspedTime() << ")";
}
Event* genRandEvent(int evt_no)
{
	// 변수 선언
	Event * pEv;
	int ev_prio;	int ev_gen_id;

	// 이벤트 우선순위, generator id 랜덤으로 생성
	ev_prio = rand() % MAX_EVENT_PRIORITY;
	ev_gen_id = rand() % NUM_EVENT_GENERATOR;

	// Event 객체를 동적으로 생성함
	pEv = (Event*) new Event(evt_no, ev_prio, ev_gen_id);
	return pEv;			// 반환
}

/*			operator overloading ( 연산자 오버로딩 )
		1. operator<<(ostr, Ev) ( 출력 연산자 오버로딩 )		*/	
ostream& operator<<(ostream& ostr, const Event& e)
{
	//print format : Event(pri: xxx, gen: xxx, no: xxx)

	ostr << "Event(pri: " << setw(3) << e.EvPri()
		<< ", gen: " << setw(3) << e.ev_gen_addr
		<< ", no: " << setw(3) << e.EvNo() << ")";

	return ostr;
}


