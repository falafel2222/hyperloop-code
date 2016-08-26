// Written by OpenLoop Hyperloop Team, August 2016

#include "libBBB.h"
#include <sched.h>

#define SCHED_DEADLINE 6

// methods of pod control
const int TEST_MODE = 1;
const int PUSHER_PHASE = 2;
const int COASTING_PHASE = 3;
const int BRAKING_PHASE = 4;

pthread_mutex_t sensorDataMutex;
pthread_mutex_t statesMutex;
pthread_mutex_t plantCommandMutex;
pthread_mutex_t podPhaseMutex;
pthread_mutex_t emergencyFlagMutex;

double states[10];
double IMUData[6];
double distanceSensorData[8];
double photoElectricData[9];


// emergency control flags from command point
int forcedBreak;
int forcedEmergencyBreak;
int forcedLateralCorrect;


void *kalmanFunction(void *arg) {
	while(1) {
		pthread_mutex_lock(&sensorDataMutex);
		pthread_mutex_unlock(&sensorDataMutex);

		// Kalman code goes here
		int i = 0;
		for (i = 1; i < 200000000; i++) {}

		
		pthread_mutex_lock(&statesMutex);
		pthread_mutex_unlock(&statesMutex);

	}
}

void *photoElectricFunction(void *arg) {
	while(1) {
		// get photoElectric data
		// calculate stuff
		pthread_mutex_lock(&sensorDataMutex);
		pthread_mutex_unlock(&sensorDataMutex);


	}
}

void *distanceSensorFunction(void *arg) {
	while(1) {
		// get distance sensor data
		// calculate stuff
		pthread_mutex_lock(&sensorDataMutex);
		pthread_mutex_unlock(&sensorDataMutex);

	}
}

void *imuDataFunction(void *arg) {
	while(1) {
		// get IMU data
		pthread_mutex_lock(&sensorDataMutex);
		pthread_mutex_unlock(&sensorDataMutex);
	}
}

void *lateralControlFunction(void *arg) {
	while(1) {
		printf("lateral control function being called");
		fflush(stdout);
		pthread_mutex_lock(&emergencyFlagMutex);
		pthread_mutex_unlock(&emergencyFlagMutex);

		pthread_mutex_lock(&statesMutex);
		pthread_mutex_unlock(&statesMutex);

		// determine lateral control plan

	}
}

void *brakingFunction(void *arg) {
	while(1) {
		pthread_mutex_lock(&emergencyFlagMutex);
		pthread_mutex_unlock(&emergencyFlagMutex);

		pthread_mutex_lock(&statesMutex);
		pthread_mutex_unlock(&statesMutex);

		// determine braking

	}
}

void *DataDisplayFunction(void *arg) {
	while(1) {

		pthread_mutex_lock(&sensorDataMutex);
		// display shit
		pthread_mutex_unlock(&sensorDataMutex);

		pthread_mutex_lock(&statesMutex);
		// display shit
		pthread_mutex_unlock(&statesMutex);

	}
}

void setScheduling(pthread_t taskID, int period, int deadline, int runtime) {
	// times are all in nanoseconds
	struct sched_attr sp;
	sp.sched_policy = SCHED_RR;
    sp.sched_priority = 0;
    sp.sched_period = period;
    sp.sched_deadline = deadline;
    sp.sched_runtime = runtime;
    int ret = sched_setattr(taskID, &sp, 0);
	if (ret != 0) {
		printf(stderr, "sched_setattr "
			     "returned %d", ret);
//		exit(EXIT_FAILURE);
	}
}

int main()
{
	pthread_mutex_init(&sensorDataMutex, NULL);
	pthread_mutex_init(&statesMutex, NULL);
	pthread_mutex_init(&podPhaseMutex, NULL);
	pthread_mutex_init(&plantCommandMutex, NULL);
	pthread_mutex_init(&emergencyFlagMutex, NULL);

	pthread_t kalman;
	pthread_t photoElectric;
	pthread_t imu;
	pthread_t distance;
	pthread_t braking;
	pthread_t lateralControl;
	pthread_t dataDisplay;

	pthread_create(&kalman, NULL, kalmanFunction, NULL);
	pthread_create(&photoElectric, NULL, photoElectricFunction, NULL);
	pthread_create(&imu, NULL, imuDataFunction, NULL);
	pthread_create(&distance, NULL, distanceSensorFunction, NULL);
	pthread_create(&braking, NULL, brakingFunction, NULL);
	pthread_create(&lateralControl, NULL, lateralControlFunction, NULL);
	pthread_create(&dataDisplay, NULL, DataDisplayFunction, NULL);

	setScheduling(kalman, 1000, 1000, 500);
	setScheduling(photoElectric, 200, 200, 20);
	setScheduling(imu, 1000, 1000, 20);
	setScheduling(distance, 5000, 5000, 100);
	setScheduling(braking, 10000, 10000, 30);
	setScheduling(lateralControl, 20000, 20000, 100);
	setScheduling(dataDisplay, 10000, 10000, 100);

	while(1) {
 
	}

	return 0;
}
