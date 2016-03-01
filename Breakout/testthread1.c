#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NLOOP 5000

int 		counter;	/* This is incremented by the threads. */
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void * doit(void * vptr);

int main(int argc, char ** argv)
{
	counter = 0;

	pthread_t	tidA, tidB;

	pthread_create(&tidA, NULL, &doit, NULL);
	pthread_create(&tidB, NULL, &doit, NULL);

	/* Wait for both threads to terminate */
	pthread_join(tidA, NULL);
	pthread_join(tidB, NULL);
	
	exit(0);
}

void * doit(void * vptr)
{
	int	i, val;
	for (i = 0; i < NLOOP; i++)
	{
		val = counter;
		printf("%d: %d\n", (int) pthread_self(), val + 1);
		counter = val + 1;
	}

	return NULL;
}
