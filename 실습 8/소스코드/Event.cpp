#include "Event.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. 모든 인자를 받는 constructor				*/
Event::Event()
{
	event_no = 0;
	event_title = string("NULL");
	ev_gen_addr = 0;
	ev_han_addr = 0;
	event_pri = 1;
	eventStatus = GENERATED;
}
Event::Event(int ev_id, int ev_pri, string title, int gen_addr)
	: event_no(ev_id), event_pri(ev_pri), event_title(title)
{
	SetEvGenAddr(gen_addr);
	SetEvHandlerAddr(0);
	eventStatus = GENERATED;
}

/*				destructor ( 소멸자 )				*/	
Event::~Event()
{
	// Event Destruct
}

/*			member function	( 멤버 함수 )			
		1. printEvent(ostr) ( 이벤트 출력 함수 )
													*/	
void Event::printEvent(ostream& ostr) const
{
	ostr << "Event(" <<
		"no: " << setw(4) << this->EvNo() << "; " <<
		"pri: " << setw(4) << this->EvPri() << "; " <<
		"gen: " << setw(4) << this->ev_gen_addr << "; " <<
		"title: " << setw(8) << this->event_title << ")";
}

/*			operator overloading ( 연산자 오버로딩 )		
		1. operator<<(ostr, Ev) ( 출력 연산자 오버로딩 )		*/	
ostream& operator<<(ostream& ostr, const Event& Ev)
{
	Ev.printEvent(ostr);
	return ostr;

}
