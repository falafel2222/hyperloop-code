// Written by OpenLoop Hyperloop Team, August 2016


#include "libBBB.h"
#include <pthread.h>
#include <semaphore.h>


void *blinky1Func(void *arg) {
	while(1)
	{
		setUsrLedValue(USR3, ON);
		usleep(2);
		setUsrLedValue(USR3, OFF);
		usleep(2);
	}
}

void *blinky2Func(void *arg) {
	while(1)
	{
		setUsrLedValue(USR3, ON);
		usleep(1);
		setUsrLedValue(USR3, OFF);
		usleep(1);
	}
}

void createTask(pthread_t handle, pthread_attr_t *att, 
				void * (*function), void * arg, int priority) {
	pthread_create(handle, att, function, arg);
	struct sched_param sp;
    sp.sched_priority = priority;
    if(pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp)){
            fprintf(stderr,"WARNING: Failed to set stepper thread"
                    "to real-time priority\n");
    }
}
int main()
{
	
	pthread_t blinky1;
	createTask(&blinky1, NULL, blinky1Func, NULL, 5);

	pthread_t blinky2;
	createTask(&blinky2, NULL, blinky2Func, NULL, 3);

	return 0;
}

