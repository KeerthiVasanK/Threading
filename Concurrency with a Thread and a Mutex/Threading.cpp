/*
 * Threading.cpp
 *
 *  Created on: May 24, 2018
 *  Author: Keerthi Vasan K
 */

#include <iostream>
#include <pthread.h>

pthread_mutex_t lock;

void* Hello(void*)
{
	std::cout<<"\n Hello World";

	for(int i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&lock);
		std::cout<<"\n Executing spawned thread line "<<i;
		pthread_mutex_unlock(&lock);
	}

	std::cout<<"\n Murder for a jar of red rum";

	pthread_exit(NULL);
}

int main()
{
	pthread_t thread;

	lock = PTHREAD_DEFAULT_MUTEX_INITIALIZER;

	pthread_create(&thread, NULL, Hello, NULL);

	for(int i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&lock);
		std::cout<<"\n Executing main thread line "<<i;
		pthread_mutex_unlock(&lock);
	}

	std::cout<<"\n Murder for a jar of red rum";

	pthread_join(thread, NULL);

	return 0;
}
