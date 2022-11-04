#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// 이벤트 상태 열거형 자료형
enum EvStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };

class Event
{
	// operator Overloading (출력 연산자)
	friend ostream& operator<< (ostream& ostr, const Event& Ev);

public:

	// constructor
	Event();
	Event(int ev_id, int ev_pri, string title, int gen_addr);

	// destructor
	~Event();

	// member functions
	void printEvent(ostream& ostr) const;				// 이벤트 출력

	// setter ( 이벤트 주소, 넘버, 우선순위, 상태 설정)
	void SetEvHandlerAddr(int HanAddr) { ev_han_addr = HanAddr; }
	void SetEvGenAddr(int genAddr) { ev_gen_addr = genAddr; }
	void SetEvNo(int ev_no) { event_no = ev_no; }
	void SetEvPri(int pri) { event_pri = pri; }
	void SetEvStatus(EvStatus eventST) { eventStatus = eventST; }		

	// getter
	int EvPri() const { return event_pri; }				// 이벤트 우선순위 넘버
	int EvNo() const { return event_no; }				// 이벤트 넘버 반환

	// operator overloading
	bool operator>(Event& e) { return (this->EvPri() > e.EvPri()); }		// 더 큰지 비교
	bool operator<(Event& e) { return (this->EvPri() < e.EvPri()); }		// 더 작은지 비교

private:
	int event_no;					// 이벤트 넘버
	string event_title;				// 이벤트 이름
	int ev_gen_addr;				// 이벤트 생성자의 주소
	int ev_han_addr;				// 이벤트 처리자의 주소
	int event_pri;					// 이벤트의 우선순위
	EvStatus eventStatus;
};


#endif // !EVENT_H
