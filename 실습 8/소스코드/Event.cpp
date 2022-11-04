#include "Event.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. ��� ���ڸ� �޴� constructor				*/
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

/*				destructor ( �Ҹ��� )				*/	
Event::~Event()
{
	// Event Destruct
}

/*			member function	( ��� �Լ� )			
		1. printEvent(ostr) ( �̺�Ʈ ��� �Լ� )
													*/	
void Event::printEvent(ostream& ostr) const
{
	ostr << "Event(" <<
		"no: " << setw(4) << this->EvNo() << "; " <<
		"pri: " << setw(4) << this->EvPri() << "; " <<
		"gen: " << setw(4) << this->ev_gen_addr << "; " <<
		"title: " << setw(8) << this->event_title << ")";
}

/*			operator overloading ( ������ �����ε� )		
		1. operator<<(ostr, Ev) ( ��� ������ �����ε� )		*/	
ostream& operator<<(ostream& ostr, const Event& Ev)
{
	Ev.printEvent(ostr);
	return ostr;

}
