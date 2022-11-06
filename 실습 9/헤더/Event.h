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

#define MAX_EVENT_PRIORITY 100			// �̺�Ʈ �켱������ �ִ밪
#define NUM_EVENT_GENERATOR 10			// �̺�Ʈ ���ʷ����� ���� = 10

// �̺�Ʈ ���� ������ �ڷ���
enum EvStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };

class Event
{
	// operator Overloading (��� ������)
	friend ostream& operator<<(ostream& ostr, const Event& e);
public:

	// constructor
	Event();										// default constructor
	Event(int ev_id, int ev_pri, int srcAddr);		// constructor (parameter ver)

	// getter ( �� ��ȯ )
	double EvElaspedTime() const { return t_elapsed_ms; }
	int EvPri() const { return event_pri; }
	int EvNo() const { return event_no; }
	LARGE_INTEGER EvGenT() const { return t_ev_gen; }
	LARGE_INTEGER EvProcT() const { return t_ev_proc; }

	// setter ( �� ���� )
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
	int event_no;			// �̺�Ʈ �ѹ�
	int event_pri;			// �̺�Ʈ �켱����
	int ev_gen_addr;		// �̺�Ʈ ���ʷ����� �ּ�
	int ev_han_addr;		// �̺�Ʈ �ڵ鷯 �ּ�

	LARGE_INTEGER t_ev_gen;		// �̺�Ʈ ������ �ð�
	LARGE_INTEGER t_ev_proc;	// �̺�Ʈ ó���� �ð�
	double t_elapsed_ms;		// �� ���� �ɸ� �ð�
	EvStatus evstat;		// �̺�Ʈ �������
	
};
Event* genRandEvent(int evt_no);

#endif // !EVENT_H
