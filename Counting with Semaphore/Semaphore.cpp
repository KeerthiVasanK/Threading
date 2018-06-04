/*
 * Counting semaphore.cpp
 *
 *  Created on: Jun 4, 2018
 *      Author: kkumara
 */

#include <iostream>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutex;

sem_t semaphore;
int nSemaphore;

void* Generator(void*)
{
	for(int i = 0; i < 17; i++)
	{
		pthread_mutex_lock(&mutex);

		if(0 == sem_post(&semaphore))
		{
			sem_getvalue(&semaphore, &nSemaphore);
			printf("\n Resistance is building bases; available resistance bases: %d", nSemaphore);
		}

		pthread_mutex_unlock(&mutex);
	}

	pthread_exit(NULL);
}

void* Destroyer(void*)
{
	for(int i = 0; i < 14; i++)
	{
		pthread_mutex_lock(&mutex);

		if(0 == sem_wait(&semaphore))
		{
			sem_getvalue(&semaphore, &nSemaphore);
			printf("\n Sith Empire razes one base; remaining resistance bases: %d", nSemaphore);
		}

		pthread_mutex_unlock(&mutex);
	}

	pthread_exit(NULL);
}

int main()
{
	pthread_t tGenerator;
	pthread_t tDestroyer;

	mutex = PTHREAD_DEFAULT_MUTEX_INITIALIZER;

	sem_init(&semaphore, 0, 0);

	pthread_create(&tGenerator, NULL, Generator, NULL);
	pthread_create(&tDestroyer, NULL, Destroyer, NULL);

	pthread_join(tGenerator, NULL);
	pthread_join(tDestroyer, NULL);

	sem_getvalue(&semaphore, &nSemaphore);
	printf("\n\n Luke Skywalker has been found; active resistance bases: %d", nSemaphore);

	sem_destroy(&semaphore);

	return 0;
}
