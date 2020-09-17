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

#ifndef _LAB1_HEADER_H
#define _LAB1_HEADER_H


typedef struct process {
	char process;
	int arrival_time;
	int service_time;

} process;

typedef struct ChainNode {
	char data;
	struct ChainNode *link;

} ChainNode;

typedef struct Queue {
	char process[6];
} Queue;

typedef struct LinkedQueue {
	ChainNode *front;
	ChainNode *rear;
	int count;
} LinkedQueue;

process pr[5];
struct Queue q;
LinkedQueue *q1;
LinkedQueue *q2;
LinkedQueue *q3;
LinkedQueue *q4;

void initWorkload();
void execute_RR();
void queueShare(struct process p, int x);
void queueCheck(int i, int x);
void queueDelete();
void servicetimeCount();
void initQueue();
void push_MLFQ(LinkedQueue *queue, char push);
char pop_MLFQ(LinkedQueue *queue);
int getRandom(int min, int max);
void insert(char a[20][5], char ch, int i);
void assign(char empty1[20][5], int i);
void print(char empty2[20][5]);
void FCFS();
void RR();
void MLFQ();
void LOTTERY();


#endif /* LAB1_HEADER_H*/



