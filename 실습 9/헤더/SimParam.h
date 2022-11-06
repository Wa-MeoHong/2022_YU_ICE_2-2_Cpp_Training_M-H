// SimParam.h Simulation Parameters Defined

#ifndef SIMUL_PARAS_H
#define SIMUL_PARAS_H

#define NUM_EVENT_GENERATORS 1		// 이벤트 제너레이터 개수 ( 주소 )
#define NUM_EVENTS_PER_GEN 50		// 한 이벤트 제너레이터가 생성하는 이벤트 수
#define NUM_EVENT_HANDLERS 1		// 이벤트 핸들러 개수 ( 주소 )

// 총 이벤트 개수 = (한 제너레이터가 발생하는 이벤트 수) * (제너레이터 수)
#define TOTAL_NUM_EVENTS (NUM_EVENTS_PER_GEN * NUM_EVENT_GENERATORS)

#define PRI_QUEUE_CAPACITY 50		// PriQ의 용량 = 50
#define PLUS_INF INT_MAX			// INT_MAX = 21억 ....
#define MAX_ROUND 1000				// ROUND 최대 수 
#define EVENT_PER_LINE 5			// 한 줄당 출력하는 이벤트 수

#define Milli 1000					// milli second 
#define Micro 1000000				// micro second

#endif