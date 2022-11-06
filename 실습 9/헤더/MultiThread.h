#ifndef MULTI_THREAD
#define MULTI_THREAD

#include <thread>
#include <mutex>
#include <string>
#include "HeapPrioQ.h"
#include "Event.h"
#include "SimParam.h"

using namespace std;

enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };		// ���� enum 
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };	// thread flag enum

/* ThreadStatusMonitor ( ������ ���� ����� ����ü ) */
typedef struct _ThreadStatusMonitor
{
	int numEvGenerated;				// ������ �̺�Ʈ�� ����
	int nuMEvProcessed;				// ó���� �̺�Ʈ�� ����
	int totalGenerated;				// �� ������ �̺�Ʈ ����
	int totalProcessed;				// �� ó���� �̺�Ʈ ����

	Event EvGenerated[TOTAL_NUM_EVENTS];		// ������ �̺�Ʈ�� ��� �迭
	Event EvProcessed[TOTAL_NUM_EVENTS];		// ó���� �̺�Ʈ�� ��� �迭

	THREAD_FLAG* pFlagThreadTerminated;		// Thread�� terminated�� �Ǿ����� enum������ ����

} ThrdStatMonitor;

/* ThreadParameter_Event ( ������ ���� ������ ����ü ) */
typedef struct _ThreadParameter_Event
{
	mutex* pCS_main;				// main���� ���� mutex
	mutex* pCS_thrd_mon;			// thread Monitor���� ���� mutex
	HeapPrioQueue<int, Event>* pPriQ_Event;		// Heap Queue�� �ּ�
	FILE* fout;						// ����ϴ� ���� ������
	ROLE role;						// �̺�Ʈ ó������ ����
	int myAddr;						// �ּ�
	int maxRound;					// ���� �� ���� Round�� �����ֳ�
	int targetEventGen;				// ���� Ÿ���� �� ���ʷ�����
	LARGE_INTEGER QP_freq;			// CPU�� Ŭ��
	ThrdStatMonitor* pThrdMon;		// ������ ����� ������
} ThrdParam;

void EventGen(ThrdParam* pParam);					// �̺�Ʈ ���ʷ����� ������ �Լ�
void EventProc(ThrdParam* pParam);					// �̺�Ʈ ���μ��� ������ �Լ�
#endif // !MULTI_THREAD
