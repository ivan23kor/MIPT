#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

#define EPSILON 10e-10
#define N 1
#define COUNT 10000000
#define MOD 10

float average[N] = {};
float dispersion[N] = {};
float array[COUNT];

int ratio = COUNT / N;

void * routine (void * arg);

int main(int argc, char const *argv[])
{
	pthread_t thread_id[N] = {0};

	float avg = 0.0;
	float disp = 0.0;

	float start_time = 0.0;
	float end_time = 0.0;
	int i = 0;
	int result = 0;
	int borders[N];

	for (i = 0; i < N; ++i)
		borders[i] = i;

	for (i = 0; i < COUNT; ++i)
		array[i] = (random ()) % MOD;

	start_time = clock ();
	for (i = 0; i < N; ++i)
	{
		result = pthread_create (&thread_id[i], (pthread_attr_t *) NULL, routine, &borders[i]);
		if (result)
		{
			printf("Couldn't create thread. Result = %d\n", result);
			exit (-1);
		}
	}
	for (i = 0; i < N; ++i)
		pthread_join(thread_id[i] , (void **) NULL);

	for (i = 0; i < N; ++i)
	{
		avg += average[i];
		disp += (dispersion[i]) * (dispersion[i]);
	}

	avg /= N;
	disp /= N;
	disp = sqrt (disp);
	end_time = clock ();
/*
 * про clock и ускорение написал всем в рассылку
 */

	printf("%d threads: average = %.3f, dispersion = %.3f.\n", N, avg, disp);
	if ((start_time > EPSILON - 1) && (end_time > EPSILON - 1))
		printf("It took %.5f seconds to compute.\n", (end_time - start_time) / CLOCKS_PER_SEC);

	return 0;
}

void * routine (void * arg)
{
	float sum = 0.0;
	float avg = 0.0;
	float disp = 0.0;
	int from = ratio * (*(int *)arg);
	int to = ratio * (*(int *)arg + 1);

/*
 * Старайтесь избегать обращения к внешним переменным.
 * Я бы, например, сделал так.
 * struct Task
 * {
 *   int start;
 *   int end;
 *   double* array;
 *   int index;  
 * };
 * Т.е. каждая нить получит структурку с полным описанием того, что ей надо сделать.
 * "Наружу" лезть за дополнительной информацией ей не надо.
 */
	if (to > COUNT)
		to = COUNT;

	for (int i = from; i < to; ++i)
		sum += array[i];

	avg = sum / (to - from);
	average[*(int *)arg] = avg;

	for (int i = from; i < to; ++i)
		disp += (array[i] - avg) * (array[i] - avg);

	disp *= N;
	disp /= COUNT;
	dispersion[*(int *)arg] = sqrt (disp);

	return NULL;
}
