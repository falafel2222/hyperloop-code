// Written by OpenLoop Hyperloop Team, August 2016


#include "libBBB.h"
#include <pthread.h>
#include <semaphore.h>


void *blinky1Func(void *arg) {
	while(1)
	{
		setUsrLedValue(USR1, ON);
		usleep(2000000);
		setUsrLedValue(USR1, OFF);
		usleep(2000000);
	}
}

void *blinky2Func(void *arg) {
	while(1)
	{
		setUsrLedValue(USR3, ON);
		usleep(1000000);
		setUsrLedValue(USR3, OFF);
		usleep(1000000);
	}
}

int main()
{
	
	pthread_t blinky1;
	pthread_create(&blinky1, NULL, blinky1Func, NULL);

	pthread_t blinky2;
	pthread_create(&blinky2, NULL, blinky2Func, NULL);
	
	while(1) {}

	return 0;
}

