#ifndef EVENT_H
#define EVENT_H

#include <iostream>	
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <process.h>

using namespace std;

#define MAX_EVENT_PRIORITY 100			// 이벤트 우선순위의 최대값
#define NUM_EVENT_GENERATOR 10			// 이벤트 제너레이터 개수 = 10

// 이벤트 상태 열거형 자료형
enum EvStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };

class Event
{
	// operator Overloading (출력 연산자)
	friend ostream& operator<<(ostream& ostr, const Event& e);
public:

	// constructor
	Event();										// default constructor
	Event(int ev_id, int ev_pri, int srcAddr);		// constructor (parameter ver)

	// getter ( 값 반환 )
	double EvElaspedTime() const { return t_elapsed_ms; }
	int EvPri() const { return event_pri; }
	int EvNo() const { return event_no; }
	LARGE_INTEGER EvGenT() const { return t_ev_gen; }
	LARGE_INTEGER EvProcT() const { return t_ev_proc; }

	// setter ( 값 설정 )
	void SetEvNo(int evNo) { event_no = evNo; }
	void SetEvPri(int evPri) { event_pri = evPri; }
	void SetEvGenAddr(int genAddr) { ev_gen_addr = genAddr; }
	void SetEvHanAddr(int hanAddr) { ev_han_addr = hanAddr; }
	void SetEvStatus(EvStatus evSt) { evstat = evSt; }
	void SetEvGenTime(LARGE_INTEGER t_gen) { t_ev_gen = t_gen; }
	void SetEvProcTime(LARGE_INTEGER t_proc) { t_ev_proc = t_proc; }
	void SetEvElapsedTime(double t_el) { t_elapsed_ms = t_el; }

	// member functions
	void PrintEv_Proc();

	// operator overloading ( < , > )
	bool operator>(Event& e) { return (event_pri > e.event_pri); }
	bool operator<(Event& e) { return (event_pri < e.event_pri); }

private:
	int event_no;			// 이벤트 넘버
	int event_pri;			// 이벤트 우선순위
	int ev_gen_addr;		// 이벤트 제너레이터 주소
	int ev_han_addr;		// 이벤트 핸들러 주소

	LARGE_INTEGER t_ev_gen;		// 이벤트 생성된 시간
	LARGE_INTEGER t_ev_proc;	// 이벤트 처리된 시간
	double t_elapsed_ms;		// 그 사이 걸린 시간
	EvStatus evstat;		// 이벤트 현재상태
	
};
Event* genRandEvent(int evt_no);

#endif // !EVENT_H
