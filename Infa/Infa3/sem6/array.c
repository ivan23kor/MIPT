#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define INC 10e7

int a[3] = {};

void * routine (void * arg);

int main(int argc, char const *argv[])
{
	pthread_t thread1_id = 0; 
	pthread_t thread2_id = 0;
	int result1 = 0;
	int result2 = 0;
	int arg1[2];
	int arg2[2];

	arg1[0] = 0;
	arg1[1] = 1;
	arg2[0] = 0;
	arg2[1] = 2;

	result1 = pthread_create (&thread1_id, (pthread_attr_t *)NULL, routine, arg1);

	if (result1)
	{
		printf("Could'not create thread. Result = %d\n", result1);
		exit (-1);
	}

	printf("Thread 1 was created. ID = %u\n", (unsigned int)thread1_id);

	result2 = pthread_create (&thread2_id, (pthread_attr_t *)NULL, routine, arg2);

	if (result2)
	{
		printf("Could'not create thread. Result = %d\n", result2);
		exit (-1);
	}

	printf("Thread 2 was created. ID = %u\n", (unsigned int)thread2_id);

	pthread_join (thread1_id, (void **)NULL);
	pthread_join (thread2_id, (void **)NULL);

	printf("a[0] = %d, a[1] = %d, a[2] = %d\n", a[0], a[1], a[2]);

	return 0;
}

void * routine (void * arg)
{
	int i = 0;
	int first = *(int *)arg;
	int second = *((int *)arg + 1);

	for (i = 0; i < INC; ++i)
	{
		a[first]++;
		a[second]++;
	}

	return NULL;
}