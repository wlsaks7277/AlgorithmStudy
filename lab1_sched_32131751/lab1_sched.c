/* structure or header file for test  by.dkfkqldk90@naver.com  */

/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32131751
*	    Student name : Jung Jin Man
*
*   lab1_sched_types.h :
*       - lab1 header file.
*       - must contains scueduler algorithm function's declations.
*
*/

#include <aio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int zombie_q = 0;					// zombie_q ë³€??ì´ˆê¸°??int none = 0;						// none ë³€??ì´ˆê¸°??
typedef struct process {				// process êµ¬ì¡°ì²?? ì–¸
	char process;					// process ?´ë¦„
	int arrival_time;				// arrival time
	int service_time;				// service time
}process;

typedef struct ChainNode {				// ChainNode êµ¬ì¡°ì²?? ì–¸
	char data;					// data field
	struct ChainNode *link;				// link field
}ChainNode;

typedef struct Queue {					// Queue êµ¬ì¡°ì²?? ì–¸
	char proc_name[6];				// ë©¤ë²„ë³€??process name ë°°ì—´ ?¬ìš©
}Queue;

typedef struct LinkedQueue {				// LinkedQueue êµ¬ì¡°ì²?? ì–¸
	ChainNode *front;				// Queue ?œì¼ ??	ChainNode *rear;				// Queue ?œì¼ ??	int count;					// node ê°œìˆ˜
}LinkedQueue;

process pr[5];						// êµ¬ì¡°ì²´ë???pr ë°°ì—´ ? ì–¸
Queue q;						// êµ¬ì¡°ì²´ë???q ? ì–¸
LinkedQueue *q1;					// êµ¬ì¡°ì²´ë????¬ì¸??? ì–¸
LinkedQueue *q2;
LinkedQueue *q3;
LinkedQueue *q4;

void initWorkload() {					// Workload ì´ˆê¸°??	pr[0].process = 'A';
	pr[0].arrival_time = 0;
	pr[0].service_time = 3;

	pr[1].process = 'B';
	pr[1].arrival_time = 2;
	pr[1].service_time = 6;

	pr[2].process = 'C';
	pr[2].arrival_time = 4;
	pr[2].service_time = 4;

	pr[3].process = 'D';
	pr[3].arrival_time = 6;
	pr[3].service_time = 5;

	pr[4].process = 'E';
	pr[4].arrival_time = 8;
	pr[4].service_time = 2;
}

void execute_RR();					// execute_RR ?¨ìˆ˜ ?„ë°© ? ì–¸
void queueShare(struct process p, int x) {		// process êµ¬ì¡°ì²?p?€ xë¥?ë§¤ê°œë³€?˜ë¡œ ê°–ëŠ” ?¨ìˆ˜
	for (int i = 0; i < 5; i++) {			// queueShare ?¨ìˆ˜??FCFS?€ RR?ì„œ ê³µë™ ?¬ìš©
		if (q.proc_name[i] == '\0') {		// process name ë°°ì—´ ë¹„ì–´?ˆëŠ” ê²½ìš° ì¶”ê?
			q.proc_name[i] = p.process;
			if (x == 0)			// FCFS??ê²½ìš° x = 1 / RR??ê²½ìš° x = 0
				execute_RR();				
			break;
		}
	}
}

void execute_RR() {
	if (none != 1) {				// ?ê? ì£½ì? ?Šì? ê²½ìš°ë§??¤í–‰
		int count = 0;	
		char tmp = q.proc_name[0];		// process name ì²«ë²ˆì§?ë°°ì—´ tmp???½ì…

		for (int i = 0; i < 5; i++) {
			if (q.proc_name[i] != '\0')	// process name ë°°ì—´??ë¹„ì–´?ˆì? ?Šì? ê²½ìš°
				count++;		// ?¸ë“œ ê°œìˆ˜ ì¦ê?
		}

		if (tmp == 'A') {			// tmpê°€ A??ê²½ìš°
			if (pr[0].service_time == 0)	// process A??service time??0??ê²½ìš°
				tmp = '\0';		// tmpë¥?NULLë¡?		}
		else if (tmp == 'B') {			// tmpê°€ B??ê²½ìš°
			if (pr[1].service_time == 0)	// process B???ë²ˆì§?service time??0??ê²½ìš°
				tmp = '\0';		// tmpë¥?NULLë¡?		}
		else if (tmp == 'C') {			// tmpê°€ C??ê²½ìš°
			if (pr[2].service_time == 0)	// process C???¸ë²ˆì§?service time??0??ê²½ìš°
				tmp = '\0';		// tmpë¥?NULLë¡?		}
		else if (tmp == 'D') {			// tmpê°€ D??ê²½ìš°
			if (pr[3].service_time == 0)	// process D???¤ë²ˆì§?service time??0??ê²½ìš°
				tmp = '\0';		// tmpë¥?NULLë¡?		}
		else if (tmp == 'E') {			// tmpê°€ E??ê²½ìš°
			if (pr[4].service_time == 0)	// process E???¤ì„¯ë²ˆì§¸ service time??0??ê²½ìš°
				tmp = '\0';		// tmpë¥?NULLë¡?		}

		for (int j = 0; j < count - 1; j++)	// ?¸ë“œ ê°œìˆ˜ - 1ë§Œí¼ ë°˜ë³µ
			q.proc_name[j] = q.proc_name[j + 1];
		q.proc_name[count - 1] = tmp;
	}
	else
		none = 0;
}

void queueCheck(int i, int x) {				// ë§¤ê°œë³€??i?€ x 
	zombie_q = 0;					// FCFS??ê²½ìš° x = 1 / RR??ê²½ìš° x = 0

	if (pr[0].arrival_time == i) {			// process A???„ì°©?œê°„??i??ê²½ìš°
		queueShare(pr[0], x);			// queueShare ?¨ìˆ˜ ?¤í–‰
		if (x == 0)				// x = 0??ê²½ìš°
			zombie_q = 1;			// zoombie_q ë³€?˜ë? 1ë¡?ì´ˆê¸°??	}
	else if (pr[1].arrival_time == i) {		// process B???„ì°©?œê°„??i??ê²½ìš°
		queueShare(pr[1], x);
		if (x == 0)
			zombie_q = 1;
	}
	else if (pr[2].arrival_time == i) {		// process C???„ì°©?œê°„??i??ê²½ìš°
		queueShare(pr[2], x);
		if (x == 0)
			zombie_q = 1;
	}
	else if (pr[3].arrival_time == i) {		// process D???„ì°©?œê°„??i??ê²½ìš°
		queueShare(pr[3], x);
		if (x == 0)
			zombie_q = 1;
	}
	else if (pr[4].arrival_time == i) {		// process E???„ì°©?œê°„??i??ê²½ìš°
		queueShare(pr[4], x);
		if (x == 0)
			zombie_q = 1;
	}
}

void queueDelete() {					// ?ë? ì§€?°ëŠ” ?¨ìˆ˜
	none = 1;						
	q.proc_name[0] = q.proc_name[1];
	q.proc_name[1] = q.proc_name[2];
	q.proc_name[2] = q.proc_name[3];
	q.proc_name[3] = q.proc_name[4];
}

void servicetimeCount() {
	if (q.proc_name[0] == 'A') {			// processê°€ A??ê²½ìš°
		pr[0].service_time--;			// A??service time ê°ì†Œ

		if (pr[0].service_time == 0)		// service time??0??ê²½ìš°
			queueDelete();			// queue ?? œ
	}
	else if (q.proc_name[0] == 'B') {		// processê°€ B??ê²½ìš°
		pr[1].service_time--;			// B??service time ê°ì†Œ

		if (pr[1].service_time == 0)		// service time??0??ê²½ìš°
			queueDelete();			// queue ?? œ
	}	
	else if (q.proc_name[0] == 'C') {		// processê°€ C??ê²½ìš°
		pr[2].service_time--;			// C??service time ê°ì†Œ

		if (pr[2].service_time == 0)		// service time??0??ê²½ìš°
			queueDelete();			// queue ?? œ
	}
	else if (q.proc_name[0] == 'D') {		// processê°€ D??ê²½ìš°
		pr[3].service_time--;			// D??service time ê°ì†Œ

		if (pr[3].service_time == 0)		// service time??0??ê²½ìš°
			queueDelete();			// queue ?? œ
	}
	else if (q.proc_name[0] == 'E') {		// processê°€ E??ê²½ìš°
		pr[4].service_time--;			// E??service time ê°ì†Œ

		if (pr[4].service_time == 0)		// service time??0??ê²½ìš°
			queueDelete();			// queue ?? œ
	}
}

void initQueue() {
	q1 = (LinkedQueue *)malloc(sizeof(Queue));	// Queue(q1) ?ì„±
	q1->count = 0;
	q1->front = NULL;				// q1 ì´ˆê¸°??	q1->rear = NULL;

	q2 = (LinkedQueue *)malloc(sizeof(Queue));	// Queue(q2) ?ì„±
	q2->count = 0; 
	q2->front = NULL;				// q2 ì´ˆê¸°??	q2->rear = NULL;

	q3 = (LinkedQueue *)malloc(sizeof(Queue));	// Queue(q3) ?ì„±
	q3->count = 0;
	q3->front = NULL;				// q3 ì´ˆê¸°??	q3->rear = NULL;

	q4 = (LinkedQueue *)malloc(sizeof(Queue));	// Queue(q4) ?ì„±
	q4->count = 0;
	q4->front = NULL;				// q4 ì´ˆê¸°??	q4->rear = NULL;
}

void push_MLFQ(LinkedQueue *queue, char push) {		// Queue Node ?½ì…,  push???½ì…??ë¬¸ì
	ChainNode *node = (ChainNode *)malloc(sizeof(ChainNode));	// ?½ì…???„ìš”???¸ë“œ ?ì„±
	node->data = push;				// ?½ì… ?¸ë“œ???°ì´?°ë? pushë¡??¤ì •
	node->link = NULL;				// ?½ì… ?¸ë“œ??linkë¥?NULLë¡??¤ì •

	if (queue->front == 0)				// ë¹??ì¸ ê²½ìš°
		queue->front = queue->rear = node;	// front?€ rear???ˆë¡œ ë§Œë“  ?¸ë“œ ?½ì…
	else {						// ë¹??ê? ?„ë‹ ê²½ìš°
		queue->rear->link = node;		// queue ?ì— ?ˆë¡œ ë§Œë“  ?¸ë“œ ?½ì…
		queue->rear = node;			// rear??ë§ˆì?ë§??¸ë“œë¥?ê°€ë¦¬í‚¤?„ë¡
	}
	queue->count++;					// ?¸ë“œ ê°œìˆ˜ ì¦ê?
}

char pop_MLFQ(LinkedQueue *queue) {			// Queue Node ?? œ
	char pop;					// pop?€ ?? œ??ë¬¸ì
	ChainNode *node = (ChainNode *)malloc(sizeof(ChainNode));	// ?? œ???„ìš”???¸ë“œ ?ì„±

	if (queue->front == 0)				// ë¹??ì¸ ê²½ìš° ì¢…ë£Œ
		return 0;

	node = queue->front;				// queue??ë§??ì„ ?¸ë“œ???½ì…
	pop = node->data;				// ?¸ë“œ???°ì´?°ë? pop???½ì…
	queue->front = node->link;			// ?? œ???¸ë“œ??linkë¥?queue??ë§??ìœ¼ë¡?	free(node);					// ?¸ë“œ ë°˜í™˜
	queue->count--;					// ?¸ë“œ ê°œìˆ˜ ê°ì†Œ

	return pop;					// ?? œ??ë¬¸ì ë¦¬í„´
}

int getRandom(int min, int max) {			// ?œë¤?¨ìˆ˜
	int num = max - min + 1;
	return min + (rand() % num);
}

 

void insert(char a[20][5], char ch, int i) {		// ë§¤ê°œë³€??2ì°¨ì› ë°°ì—´ a, ë¬¸ì ch, ?œê°„ i
	if (ch == 'A')					// 2ì°¨ì› ë°°ì—´???½ì…?˜ëŠ” insert ?¨ìˆ˜
		a[i][0] = 'A';				// MLFQ ?¨ìˆ˜?ì„œ ?¬ìš©
	else if (ch == 'B')
		a[i][1] = 'B';
	else if (ch == 'C')
		a[i][2] = 'C';
	else if (ch == 'D')
		a[i][3] = 'D';
	else if (ch == 'E')
		a[i][4] = 'E';
}

void assign(char empty1[20][5], int i)			// ë§¤ê°œë³€??2ì°¨ì› ë°°ì—´ empty1, ?œê°„ i
{							// FCFS, RR ?¨ìˆ˜?ì„œ ?¬ìš©
	if (q.proc_name[0] == 'A')
		empty1[i][0] = 'A';
	else if (q.proc_name[0] == 'B')
		empty1[i][1] = 'B';
	else if (q.proc_name[0] == 'C')
		empty1[i][2] = 'C';
	else if (q.proc_name[0] == 'D')
		empty1[i][3] = 'D';
	else if (q.proc_name[0] == 'E')
		empty1[i][4] = 'E';

	servicetimeCount();
}

void print(char empty2[20][5])				// ë§¤ê°œë³€??2ì°¨ì› ë°°ì—´ empty2ë¥??´ìš©??ì¶œë ¥?¨ìˆ˜
{
	for (int i = 0; i < 5; i++)
	{
		printf("%c : ", 65 + i);		// A~Eê¹Œì? ì¶œë ¥

		for (int j = 0; j < 20; j++)
		{
			if (empty2[j][i] == 'A')
				printf("??");
			else if (empty2[j][i] == 'B')
				printf("??");
			else if (empty2[j][i] == 'C')
				printf("??");
			else if (empty2[j][i] == 'D')
				printf("??");
			else if (empty2[j][i] == 'E')
				printf("??");
			else
				printf("??");
		}
		printf("\n");
	}
	printf("\n");
}

void FCFS() {
	int x = 1;					// RRê³¼ì˜ ì°¨ì´ë¥?ì£¼ê¸° ?„í•œ ë³€??x
	char FCFS[20][5] = { 0 };			// [20][5] 2ì°¨ì› ë°°ì—´ ì´ˆê¸°??
	for (int i = 0; i < 20; i++) {
		queueCheck(i, x);
		assign(FCFS, i);
	}
	print(FCFS);
}

void RR() {
	int x = 0;					// FCFSê³¼ì˜ ì°¨ì´ë¥?ì£¼ê¸° ?„í•œ ë³€??x
	char RR[20][5] = { 0 };

	for (int i = 0; i < 20; i++) {
		queueCheck(i, x);					

		if (zombie_q == 0)			// zombie_qê°€ 0??ê²½ìš°
			execute_RR();			// ?¤ì‹œ execute_RR ?¨ìˆ˜ ?¤í–‰
		assign(RR, i);
	}
	print(RR);
	printf("\n");
}

void MLFQ() {						// ë³€??a???œê°„???ë¦„, c???? œ??ë¬¸ìê°€ ë¬´ìŠ¨ ë¬¸ì?¸ì? ?Œì•…
	int a = 0, c = 0, sum = 0;			// sum?€ MLFQ?ì„œ ëª¨ë“  ?ì˜ ?¸ë“œ ê°œìˆ˜
	int b;						// b??êµ¬ì¡°ì²?ë³€??pr???¸ë±??	char ch;					// ch??pop ?¨ìˆ˜?ì„œ ?? œ???°ì´??	char MLFQ[20][5];				// MLFQ 2ì°¨ì› ë°°ì—´ ?•ì  ? ë‹¹

	for (a = 0; a < 20; a++) {			// ?œê°„???ë¦„
		for (b = 0; b < 5; b++)
			if (a == pr[b].arrival_time)	// a?€ ?„ì°© ?œê°„??ê°™ì? processë¥?ì°¾ìŒ
				push_MLFQ(q1, pr[b].process);		// q1???½ì…

		sum = q1->count + q2->count + q3->count + q4->count;
																// ?„ì§ bê°€ ?¤ì–´?¤ì? ?Šì? ?í™©?ì„œ q1???ë‚¬ê¸??Œë¬¸??q2ë¡?ê°€?¼í•˜??aë¥?																// q1??? ì??œí‚¤ê¸??„í•´ ëª¨ë“  queue???¸ë“œ ê°œìˆ˜ë¥?ì¹´ìš´??
		if (sum == 1) {				// queue ?„ì²´??processê°€ ?˜ë‚˜ ?ˆëŠ” ê²½ìš°
			if (q4->count == 1) {		// q4 ?¸ë“œ???°ì´?°ê? ?ˆëŠ” ê²½ìš°
				ch = pop_MLFQ(q4);	// q4???°ì´?°ë? ?? œ ??ch???½ì…
				push_MLFQ(q1, ch);	// ?? œ???°ì´?°ë? q1???€??			}
			else if (q3->count == 1) {	// q2 ?¸ë“œ???°ì´?°ê? ?ˆëŠ” ê²½ìš°
				ch = pop_MLFQ(q3);	// q3???°ì´?°ë? ?? œ ??ch???½ì…
				push_MLFQ(q1, ch);	// ?½ì…???°ì´?°ë? q1???€??			}
			else if (q2->count == 1) {	// q1 ?¸ë“œ???°ì´?°ê? ?ˆëŠ” ê²½ìš°
				ch = pop_MLFQ(q2);	// q2???°ì´?°ë? ?? œ ??ch???½ì…
				push_MLFQ(q1, ch);	// ?½ì…???°ì´?°ë? q1???€??			}
		}

		if (q1->count != 0) {			// q1 ?ìƒ‰
			ch = pop_MLFQ(q1);		// q1??queue?ì„œ ?œì¼ ë¨¼ì? ?¤ì–´???¸ë“œ ?? œ
			insert(MLFQ, ch, a);		// ?½ì…

			for (c = 0; c < 5; c++)		// ë³€??cë¥??´ìš©???? œ??ë¬¸ìê°€ ë¬´ìŠ¨ ë¬¸ì?¸ì? ?Œì•„??				if (ch == pr[c].process) {
					pr[c].service_time--;		// ?´ë‹¹ process??service time 1 ê°ì†Œ

					if (pr[c].service_time != 0)	// service time???¨ì•„?ˆëŠ” ê²½ìš°
						push_MLFQ(q2, pr[c].process);	// ?¤ìŒ queueu???½ì…
				}
		}
		else if (q2->count != 0) {		// q2 ?ìƒ‰
			ch = pop_MLFQ(q2);		// q2??queue?ì„œ ?œì¼ ë¨¼ì? ?¤ì–´???¸ë“œ ?? œ
			insert(MLFQ, ch, a);		// ?½ì…

			for (c = 0; c < 5; c++)
				if (ch == pr[c].process) {
					pr[c].service_time--;
					
					if (pr[c].service_time != 0)
						push_MLFQ(q3, pr[c].process);
				}
		}
		else if (q3->count != 0) {		// q3 ?ìƒ‰
			ch = pop_MLFQ(q3);		// q3??queue?ì„œ ?œì¼ ë¨¼ì? ?¤ì–´???¸ë“œ ?? œ
			insert(MLFQ, ch, a);		// ?½ì…

			for (c = 0; c < 5; c++)
				if (ch == pr[c].process) {
					pr[c].service_time--;

					if (pr[c].service_time != 0)
						push_MLFQ(q4, pr[c].process);
				}
		}
		else {					// q4 ?ìƒ‰
			ch = pop_MLFQ(q4);		// q4??queue?ì„œ ?œì¼ ë¨¼ì? ?¤ì–´???¸ë“œ ?? œ
			insert(MLFQ, ch, a);		// ?? œ

			for (c = 0; c < 5; c++)
				if (ch == pr[c].process) {
					pr[c].service_time--;

					if (pr[c].service_time != 0)
						push_MLFQ(q4, pr[c].process);
				}
		}
	}
	print(MLFQ);					// 2ì°¨ì› ë°°ì—´ MLFQ ì¶œë ¥
	printf("\n");
}

void LOTTERY() {
	int arr[20];					// ?œë¤?¨ìˆ˜ ? ì–¸???„í•œ ë°°ì—´
	int min, max, x, y;			
	char LOTTERY[20][2];				// LOTTERY 2ì°¨ì› ë°°ì—´ ?•ì  ? ë‹¹

	srand(time(NULL));				// ?œìˆ˜ ì¶œë ¥??srand ?¨ìˆ˜
	printf("LOTTERY ìµœì†Ÿê°? ìµœëŒ“ê°??…ë ¥ : ");
	scanf("%d %d", &min, &max);
	printf("LOTTERY ë¹„ìœ¨ ?…ë ¥ : ");
	scanf("%d %d", &x, &y);
	printf("?? ");

	for (int i = 0; i < 20; i++) {
		arr[i] = getRandom(min, max);		// ?œë¤?¨ìˆ˜ getRandom ?¤í–‰

		if (arr[i] < 10)			// ì¶œë ¥?˜ëŠ” ?«ì?¤ì„ 2ê¸€?ë¡œ ë§ì¶”ê¸??„í•¨
			printf("0");
		printf("%d  ", arr[i]);
	}
	printf("\n");

	for (int j = 0; j < 2; j++) {			// A?€ B????		printf("%c :", 65 + j);			// ASCII code A, B ì¶œë ¥

		for (int i = 0; i < 20; i++) {				// LOTTERY 20ë²??˜í–‰
			if (arr[i] <= x && j == 0) 			// LOTTERY A ì¶œë ¥
				LOTTERY[i][j] = printf(" ?? ");
			else if (arr[i] > x && j == 1)			// LOTTERY B ì¶œë ¥
				LOTTERY[i][j] = printf(" ?? ");
			else						// A??ê°’ì´??B??ê°’ì´ ë¹„ì–´?ˆìœ¼ë©?ë¹ˆì¹¸ ì¶œë ¥
				LOTTERY[i][j] = printf(" ?? ");
		}
		printf("\n");
	}
} 
