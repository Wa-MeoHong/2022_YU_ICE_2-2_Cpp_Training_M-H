#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// �̺�Ʈ ���� ������ �ڷ���
enum EvStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };

class Event
{
	// operator Overloading (��� ������)
	friend ostream& operator<< (ostream& ostr, const Event& Ev);

public:

	// constructor
	Event();
	Event(int ev_id, int ev_pri, string title, int gen_addr);

	// destructor
	~Event();

	// member functions
	void printEvent(ostream& ostr) const;				// �̺�Ʈ ���

	// setter ( �̺�Ʈ �ּ�, �ѹ�, �켱����, ���� ����)
	void SetEvHandlerAddr(int HanAddr) { ev_han_addr = HanAddr; }
	void SetEvGenAddr(int genAddr) { ev_gen_addr = genAddr; }
	void SetEvNo(int ev_no) { event_no = ev_no; }
	void SetEvPri(int pri) { event_pri = pri; }
	void SetEvStatus(EvStatus eventST) { eventStatus = eventST; }		

	// getter
	int EvPri() const { return event_pri; }				// �̺�Ʈ �켱���� �ѹ�
	int EvNo() const { return event_no; }				// �̺�Ʈ �ѹ� ��ȯ

	// operator overloading
	bool operator>(Event& e) { return (this->EvPri() > e.EvPri()); }		// �� ū�� ��
	bool operator<(Event& e) { return (this->EvPri() < e.EvPri()); }		// �� ������ ��

private:
	int event_no;					// �̺�Ʈ �ѹ�
	string event_title;				// �̺�Ʈ �̸�
	int ev_gen_addr;				// �̺�Ʈ �������� �ּ�
	int ev_han_addr;				// �̺�Ʈ ó������ �ּ�
	int event_pri;					// �̺�Ʈ�� �켱����
	EvStatus eventStatus;
};


#endif // !EVENT_H
