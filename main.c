// Written by OpenLoop Hyperloop Team, August 2016

#include "libBBB.h"
#include <pthread.h>

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


void setPriority(pthread_t task, int priority) {
	struct sched_param sp;
    sp.sched_priority = priority;
    if(pthread_setschedparam(task, SCHED_RR, &sp)){
            fprintf(stderr,"WARNING: Failed to set stepper thread"
                    "to real-time priority\n");
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


	setPriority(kalman, 1);
	setPriority(photoElectric, 1);
	setPriority(imu, 1);
	setPriority(distance, 2);
	setPriority(braking, 2);
	setPriority(lateralControl, 3);
	setPriority(dataDisplay, 3);

	while(1) {

		usleep(1000);
	}

	pthread_mutex_destroy(&sensorDataMutex);
	pthread_mutex_destroy(&statesMutex);
	pthread_mutex_destroy(&podPhaseMutex);
	pthread_mutex_destroy(&plantCommandMutex);
	pthread_mutex_destroy(&emergencyFlagMutex);

	return 0;
}
