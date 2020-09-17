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
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>

#include "lab1_sched_types.h"


int main(int argc, char *argv[]){
	printf("-------------------------------------  FCFS  -------------------------------------\n");
	initWorkload();
	FCFS();

	printf("----------------------------------  Round Robin  ---------------------------------\n");
	initWorkload();
	RR();

	printf("-------------------------------------  MLFQ  -------------------------------------\n");
	initWorkload();
	initQueue();
	MLFQ();

	printf("------------------------------------  Lottery  -----------------------------------\n");
	LOTTERY();

	return 0;
}
