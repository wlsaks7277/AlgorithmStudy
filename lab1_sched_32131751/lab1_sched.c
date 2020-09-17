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

int zombie_q = 0;					// zombie_q 변??초기??int none = 0;						// none 변??초기??
typedef struct process {				// process 구조�??�언
	char process;					// process ?�름
	int arrival_time;				// arrival time
	int service_time;				// service time
}process;

typedef struct ChainNode {				// ChainNode 구조�??�언
	char data;					// data field
	struct ChainNode *link;				// link field
}ChainNode;

typedef struct Queue {					// Queue 구조�??�언
	char proc_name[6];				// 멤버변??process name 배열 ?�용
}Queue;

typedef struct LinkedQueue {				// LinkedQueue 구조�??�언
	ChainNode *front;				// Queue ?�일 ??	ChainNode *rear;				// Queue ?�일 ??	int count;					// node 개수
}LinkedQueue;

process pr[5];						// 구조체�???pr 배열 ?�언
Queue q;						// 구조체�???q ?�언
LinkedQueue *q1;					// 구조체�????�인???�언
LinkedQueue *q2;
LinkedQueue *q3;
LinkedQueue *q4;

void initWorkload() {					// Workload 초기??	pr[0].process = 'A';
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

void execute_RR();					// execute_RR ?�수 ?�방 ?�언
void queueShare(struct process p, int x) {		// process 구조�?p?� x�?매개변?�로 갖는 ?�수
	for (int i = 0; i < 5; i++) {			// queueShare ?�수??FCFS?� RR?�서 공동 ?�용
		if (q.proc_name[i] == '\0') {		// process name 배열 비어?�는 경우 추�?
			q.proc_name[i] = p.process;
			if (x == 0)			// FCFS??경우 x = 1 / RR??경우 x = 0
				execute_RR();				
			break;
		}
	}
}

void execute_RR() {
	if (none != 1) {				// ?��? 죽�? ?��? 경우�??�행
		int count = 0;	
		char tmp = q.proc_name[0];		// process name 첫번�?배열 tmp???�입

		for (int i = 0; i < 5; i++) {
			if (q.proc_name[i] != '\0')	// process name 배열??비어?��? ?��? 경우
				count++;		// ?�드 개수 증�?
		}

		if (tmp == 'A') {			// tmp가 A??경우
			if (pr[0].service_time == 0)	// process A??service time??0??경우
				tmp = '\0';		// tmp�?NULL�?		}
		else if (tmp == 'B') {			// tmp가 B??경우
			if (pr[1].service_time == 0)	// process B???�번�?service time??0??경우
				tmp = '\0';		// tmp�?NULL�?		}
		else if (tmp == 'C') {			// tmp가 C??경우
			if (pr[2].service_time == 0)	// process C???�번�?service time??0??경우
				tmp = '\0';		// tmp�?NULL�?		}
		else if (tmp == 'D') {			// tmp가 D??경우
			if (pr[3].service_time == 0)	// process D???�번�?service time??0??경우
				tmp = '\0';		// tmp�?NULL�?		}
		else if (tmp == 'E') {			// tmp가 E??경우
			if (pr[4].service_time == 0)	// process E???�섯번째 service time??0??경우
				tmp = '\0';		// tmp�?NULL�?		}

		for (int j = 0; j < count - 1; j++)	// ?�드 개수 - 1만큼 반복
			q.proc_name[j] = q.proc_name[j + 1];
		q.proc_name[count - 1] = tmp;
	}
	else
		none = 0;
}

void queueCheck(int i, int x) {				// 매개변??i?� x 
	zombie_q = 0;					// FCFS??경우 x = 1 / RR??경우 x = 0

	if (pr[0].arrival_time == i) {			// process A???�착?�간??i??경우
		queueShare(pr[0], x);			// queueShare ?�수 ?�행
		if (x == 0)				// x = 0??경우
			zombie_q = 1;			// zoombie_q 변?��? 1�?초기??	}
	else if (pr[1].arrival_time == i) {		// process B???�착?�간??i??경우
		queueShare(pr[1], x);
		if (x == 0)
			zombie_q = 1;
	}
	else if (pr[2].arrival_time == i) {		// process C???�착?�간??i??경우
		queueShare(pr[2], x);
		if (x == 0)
			zombie_q = 1;
	}
	else if (pr[3].arrival_time == i) {		// process D???�착?�간??i??경우
		queueShare(pr[3], x);
		if (x == 0)
			zombie_q = 1;
	}
	else if (pr[4].arrival_time == i) {		// process E???�착?�간??i??경우
		queueShare(pr[4], x);
		if (x == 0)
			zombie_q = 1;
	}
}

void queueDelete() {					// ?��? 지?�는 ?�수
	none = 1;						
	q.proc_name[0] = q.proc_name[1];
	q.proc_name[1] = q.proc_name[2];
	q.proc_name[2] = q.proc_name[3];
	q.proc_name[3] = q.proc_name[4];
}

void servicetimeCount() {
	if (q.proc_name[0] == 'A') {			// process가 A??경우
		pr[0].service_time--;			// A??service time 감소

		if (pr[0].service_time == 0)		// service time??0??경우
			queueDelete();			// queue ??��
	}
	else if (q.proc_name[0] == 'B') {		// process가 B??경우
		pr[1].service_time--;			// B??service time 감소

		if (pr[1].service_time == 0)		// service time??0??경우
			queueDelete();			// queue ??��
	}	
	else if (q.proc_name[0] == 'C') {		// process가 C??경우
		pr[2].service_time--;			// C??service time 감소

		if (pr[2].service_time == 0)		// service time??0??경우
			queueDelete();			// queue ??��
	}
	else if (q.proc_name[0] == 'D') {		// process가 D??경우
		pr[3].service_time--;			// D??service time 감소

		if (pr[3].service_time == 0)		// service time??0??경우
			queueDelete();			// queue ??��
	}
	else if (q.proc_name[0] == 'E') {		// process가 E??경우
		pr[4].service_time--;			// E??service time 감소

		if (pr[4].service_time == 0)		// service time??0??경우
			queueDelete();			// queue ??��
	}
}

void initQueue() {
	q1 = (LinkedQueue *)malloc(sizeof(Queue));	// Queue(q1) ?�성
	q1->count = 0;
	q1->front = NULL;				// q1 초기??	q1->rear = NULL;

	q2 = (LinkedQueue *)malloc(sizeof(Queue));	// Queue(q2) ?�성
	q2->count = 0; 
	q2->front = NULL;				// q2 초기??	q2->rear = NULL;

	q3 = (LinkedQueue *)malloc(sizeof(Queue));	// Queue(q3) ?�성
	q3->count = 0;
	q3->front = NULL;				// q3 초기??	q3->rear = NULL;

	q4 = (LinkedQueue *)malloc(sizeof(Queue));	// Queue(q4) ?�성
	q4->count = 0;
	q4->front = NULL;				// q4 초기??	q4->rear = NULL;
}

void push_MLFQ(LinkedQueue *queue, char push) {		// Queue Node ?�입,  push???�입??문자
	ChainNode *node = (ChainNode *)malloc(sizeof(ChainNode));	// ?�입???�요???�드 ?�성
	node->data = push;				// ?�입 ?�드???�이?��? push�??�정
	node->link = NULL;				// ?�입 ?�드??link�?NULL�??�정

	if (queue->front == 0)				// �??�인 경우
		queue->front = queue->rear = node;	// front?� rear???�로 만든 ?�드 ?�입
	else {						// �??��? ?�닐 경우
		queue->rear->link = node;		// queue ?�에 ?�로 만든 ?�드 ?�입
		queue->rear = node;			// rear??마�?�??�드�?가리키?�록
	}
	queue->count++;					// ?�드 개수 증�?
}

char pop_MLFQ(LinkedQueue *queue) {			// Queue Node ??��
	char pop;					// pop?� ??��??문자
	ChainNode *node = (ChainNode *)malloc(sizeof(ChainNode));	// ??��???�요???�드 ?�성

	if (queue->front == 0)				// �??�인 경우 종료
		return 0;

	node = queue->front;				// queue??�??�을 ?�드???�입
	pop = node->data;				// ?�드???�이?��? pop???�입
	queue->front = node->link;			// ??��???�드??link�?queue??�??�으�?	free(node);					// ?�드 반환
	queue->count--;					// ?�드 개수 감소

	return pop;					// ??��??문자 리턴
}

int getRandom(int min, int max) {			// ?�덤?�수
	int num = max - min + 1;
	return min + (rand() % num);
}

 

void insert(char a[20][5], char ch, int i) {		// 매개변??2차원 배열 a, 문자 ch, ?�간 i
	if (ch == 'A')					// 2차원 배열???�입?�는 insert ?�수
		a[i][0] = 'A';				// MLFQ ?�수?�서 ?�용
	else if (ch == 'B')
		a[i][1] = 'B';
	else if (ch == 'C')
		a[i][2] = 'C';
	else if (ch == 'D')
		a[i][3] = 'D';
	else if (ch == 'E')
		a[i][4] = 'E';
}

void assign(char empty1[20][5], int i)			// 매개변??2차원 배열 empty1, ?�간 i
{							// FCFS, RR ?�수?�서 ?�용
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

void print(char empty2[20][5])				// 매개변??2차원 배열 empty2�??�용??출력?�수
{
	for (int i = 0; i < 5; i++)
	{
		printf("%c : ", 65 + i);		// A~E까�? 출력

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
	int x = 1;					// RR과의 차이�?주기 ?�한 변??x
	char FCFS[20][5] = { 0 };			// [20][5] 2차원 배열 초기??
	for (int i = 0; i < 20; i++) {
		queueCheck(i, x);
		assign(FCFS, i);
	}
	print(FCFS);
}

void RR() {
	int x = 0;					// FCFS과의 차이�?주기 ?�한 변??x
	char RR[20][5] = { 0 };

	for (int i = 0; i < 20; i++) {
		queueCheck(i, x);					

		if (zombie_q == 0)			// zombie_q가 0??경우
			execute_RR();			// ?�시 execute_RR ?�수 ?�행
		assign(RR, i);
	}
	print(RR);
	printf("\n");
}

void MLFQ() {						// 변??a???�간???�름, c????��??문자가 무슨 문자?��? ?�악
	int a = 0, c = 0, sum = 0;			// sum?� MLFQ?�서 모든 ?�의 ?�드 개수
	int b;						// b??구조�?변??pr???�덱??	char ch;					// ch??pop ?�수?�서 ??��???�이??	char MLFQ[20][5];				// MLFQ 2차원 배열 ?�적 ?�당

	for (a = 0; a < 20; a++) {			// ?�간???�름
		for (b = 0; b < 5; b++)
			if (a == pr[b].arrival_time)	// a?� ?�착 ?�간??같�? process�?찾음
				push_MLFQ(q1, pr[b].process);		// q1???�입

		sum = q1->count + q2->count + q3->count + q4->count;
																// ?�직 b가 ?�어?��? ?��? ?�황?�서 q1???�났�??�문??q2�?가?�하??a�?																// q1???��??�키�??�해 모든 queue???�드 개수�?카운??
		if (sum == 1) {				// queue ?�체??process가 ?�나 ?�는 경우
			if (q4->count == 1) {		// q4 ?�드???�이?��? ?�는 경우
				ch = pop_MLFQ(q4);	// q4???�이?��? ??�� ??ch???�입
				push_MLFQ(q1, ch);	// ??��???�이?��? q1???�??			}
			else if (q3->count == 1) {	// q2 ?�드???�이?��? ?�는 경우
				ch = pop_MLFQ(q3);	// q3???�이?��? ??�� ??ch???�입
				push_MLFQ(q1, ch);	// ?�입???�이?��? q1???�??			}
			else if (q2->count == 1) {	// q1 ?�드???�이?��? ?�는 경우
				ch = pop_MLFQ(q2);	// q2???�이?��? ??�� ??ch???�입
				push_MLFQ(q1, ch);	// ?�입???�이?��? q1???�??			}
		}

		if (q1->count != 0) {			// q1 ?�색
			ch = pop_MLFQ(q1);		// q1??queue?�서 ?�일 먼�? ?�어???�드 ??��
			insert(MLFQ, ch, a);		// ?�입

			for (c = 0; c < 5; c++)		// 변??c�??�용????��??문자가 무슨 문자?��? ?�아??				if (ch == pr[c].process) {
					pr[c].service_time--;		// ?�당 process??service time 1 감소

					if (pr[c].service_time != 0)	// service time???�아?�는 경우
						push_MLFQ(q2, pr[c].process);	// ?�음 queueu???�입
				}
		}
		else if (q2->count != 0) {		// q2 ?�색
			ch = pop_MLFQ(q2);		// q2??queue?�서 ?�일 먼�? ?�어???�드 ??��
			insert(MLFQ, ch, a);		// ?�입

			for (c = 0; c < 5; c++)
				if (ch == pr[c].process) {
					pr[c].service_time--;
					
					if (pr[c].service_time != 0)
						push_MLFQ(q3, pr[c].process);
				}
		}
		else if (q3->count != 0) {		// q3 ?�색
			ch = pop_MLFQ(q3);		// q3??queue?�서 ?�일 먼�? ?�어???�드 ??��
			insert(MLFQ, ch, a);		// ?�입

			for (c = 0; c < 5; c++)
				if (ch == pr[c].process) {
					pr[c].service_time--;

					if (pr[c].service_time != 0)
						push_MLFQ(q4, pr[c].process);
				}
		}
		else {					// q4 ?�색
			ch = pop_MLFQ(q4);		// q4??queue?�서 ?�일 먼�? ?�어???�드 ??��
			insert(MLFQ, ch, a);		// ??��

			for (c = 0; c < 5; c++)
				if (ch == pr[c].process) {
					pr[c].service_time--;

					if (pr[c].service_time != 0)
						push_MLFQ(q4, pr[c].process);
				}
		}
	}
	print(MLFQ);					// 2차원 배열 MLFQ 출력
	printf("\n");
}

void LOTTERY() {
	int arr[20];					// ?�덤?�수 ?�언???�한 배열
	int min, max, x, y;			
	char LOTTERY[20][2];				// LOTTERY 2차원 배열 ?�적 ?�당

	srand(time(NULL));				// ?�수 출력??srand ?�수
	printf("LOTTERY 최솟�? 최댓�??�력 : ");
	scanf("%d %d", &min, &max);
	printf("LOTTERY 비율 ?�력 : ");
	scanf("%d %d", &x, &y);
	printf("?? ");

	for (int i = 0; i < 20; i++) {
		arr[i] = getRandom(min, max);		// ?�덤?�수 getRandom ?�행

		if (arr[i] < 10)			// 출력?�는 ?�자?�을 2글?�로 맞추�??�함
			printf("0");
		printf("%d  ", arr[i]);
	}
	printf("\n");

	for (int j = 0; j < 2; j++) {			// A?� B????		printf("%c :", 65 + j);			// ASCII code A, B 출력

		for (int i = 0; i < 20; i++) {				// LOTTERY 20�??�행
			if (arr[i] <= x && j == 0) 			// LOTTERY A 출력
				LOTTERY[i][j] = printf(" ?? ");
			else if (arr[i] > x && j == 1)			// LOTTERY B 출력
				LOTTERY[i][j] = printf(" ?? ");
			else						// A??값이??B??값이 비어?�으�?빈칸 출력
				LOTTERY[i][j] = printf(" ?? ");
		}
		printf("\n");
	}
} 
