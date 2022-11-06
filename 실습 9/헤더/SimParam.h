// SimParam.h Simulation Parameters Defined

#ifndef SIMUL_PARAS_H
#define SIMUL_PARAS_H

#define NUM_EVENT_GENERATORS 1		// �̺�Ʈ ���ʷ����� ���� ( �ּ� )
#define NUM_EVENTS_PER_GEN 50		// �� �̺�Ʈ ���ʷ����Ͱ� �����ϴ� �̺�Ʈ ��
#define NUM_EVENT_HANDLERS 1		// �̺�Ʈ �ڵ鷯 ���� ( �ּ� )

// �� �̺�Ʈ ���� = (�� ���ʷ����Ͱ� �߻��ϴ� �̺�Ʈ ��) * (���ʷ����� ��)
#define TOTAL_NUM_EVENTS (NUM_EVENTS_PER_GEN * NUM_EVENT_GENERATORS)

#define PRI_QUEUE_CAPACITY 50		// PriQ�� �뷮 = 50
#define PLUS_INF INT_MAX			// INT_MAX = 21�� ....
#define MAX_ROUND 1000				// ROUND �ִ� �� 
#define EVENT_PER_LINE 5			// �� �ٴ� ����ϴ� �̺�Ʈ ��

#define Milli 1000					// milli second 
#define Micro 1000000				// micro second

#endif