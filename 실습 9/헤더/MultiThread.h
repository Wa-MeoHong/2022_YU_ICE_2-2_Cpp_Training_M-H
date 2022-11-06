#ifndef MULTI_THREAD
#define MULTI_THREAD

#include <thread>
#include <mutex>
#include <string>
#include "HeapPrioQ.h"
#include "Event.h"
#include "SimParam.h"

using namespace std;

enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };		// 역할 enum 
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };	// thread flag enum

/* ThreadStatusMonitor ( 쓰레드 상태 모니터 구조체 ) */
typedef struct _ThreadStatusMonitor
{
	int numEvGenerated;				// 생성된 이벤트의 개수
	int nuMEvProcessed;				// 처리된 이벤트의 개수
	int totalGenerated;				// 총 생성된 이벤트 개수
	int totalProcessed;				// 총 처리된 이벤트 개수

	Event EvGenerated[TOTAL_NUM_EVENTS];		// 생성된 이벤트를 담는 배열
	Event EvProcessed[TOTAL_NUM_EVENTS];		// 처리된 이벤트를 담는 배열

	THREAD_FLAG* pFlagThreadTerminated;		// Thread가 terminated가 되었는지 enum변수를 들고옴

} ThrdStatMonitor;

/* ThreadParameter_Event ( 쓰레드 내의 변수들 구조체 ) */
typedef struct _ThreadParameter_Event
{
	mutex* pCS_main;				// main에서 쓰는 mutex
	mutex* pCS_thrd_mon;			// thread Monitor에서 쓰는 mutex
	HeapPrioQueue<int, Event>* pPriQ_Event;		// Heap Queue의 주소
	FILE* fout;						// 출력하는 파일 포인터
	ROLE role;						// 이벤트 처리자의 역할
	int myAddr;						// 주소
	int maxRound;					// 현재 몇 번의 Round를 돌고있나
	int targetEventGen;				// 현재 타겟이 된 제너레이터
	LARGE_INTEGER QP_freq;			// CPU의 클럭
	ThrdStatMonitor* pThrdMon;		// 쓰레드 모니터 포인터
} ThrdParam;

void EventGen(ThrdParam* pParam);					// 이벤트 제너레이팅 쓰레드 함수
void EventProc(ThrdParam* pParam);					// 이벤트 프로세싱 쓰레드 함수
#endif // !MULTI_THREAD
