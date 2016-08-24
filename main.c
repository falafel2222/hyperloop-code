// Written by OpenLoop Hyperloop Team, August 2016

#include "libBBB.h"
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t ledMutex;


void *blinky1Func(void *arg) {
	while(1)
	{
		pthread_mutex_lock(&ledMutex);
		setUsrLedValue(USR1, ON);
		usleep(1000000);
		pthread_mutex_unlock();
		usleep(1000000);
	}
}

void *blinky2Func(void *arg) {
	while(1)
	{
		pthread_mutex_lock(&ledMutex);
		setUsrLedValue(USR1, OFF);
		usleep(1000000);
		pthread_mutex_unlock();
		usleep(1000000);
	}
}

int main()
{
	pthread_mutex_init(&ledMutex, NULL);

	pthread_t blinky1;
	pthread_create(&blinky1, NULL, blinky1Func, NULL);

	pthread_t blinky2;
	pthread_create(&blinky2, NULL, blinky2Func, NULL);

	while(1) {}

	pthread_mutex_destroy(&ledMutex);

	return 0;
}