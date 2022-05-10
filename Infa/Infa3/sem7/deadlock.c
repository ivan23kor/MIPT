#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define SEM_COUNT 2

void * routine1 (void * arg);
void * routine2 (void * arg);
void sem_change (int semnum, int add);

int semid = 0;

int main(int argc, char const *argv[])
{
	pthread_t thread_id1 = 0;
	pthread_t thread_id2 = 0;

	int result = 0;

	key_t key;

	const char filename[] = "deadlock.txt";

    if ((key = ftok (filename , 0)) < 0) {
        printf("Can`t generate key\n");
        exit(-1);
    }

    if ((semid = semget(key, SEM_COUNT, 0666 | IPC_CREAT)) < 0) {
        printf("Can`t get semid\n");
        exit(-1);
    }

	sem_change (0, 1);
	sem_change (1, 1);

    result = pthread_create(&thread_id1, (pthread_attr_t *)NULL, routine1, NULL);

    if (result)
    {
        printf("Can`t create thread, returned value = %d\n" , result);
        exit(-1);
    }

    printf("Thread was created, thread id = %u\n" , (unsigned int)thread_id1);

	result = pthread_create(&thread_id2, (pthread_attr_t *)NULL, routine2, NULL);

    if (result)
    {
        printf("Can`t create thread, returned value = %d\n" , result);
        exit(-1);
    }

    printf("Thread was created, thread id = %u\n" , (unsigned int)thread_id2);


    pthread_join (thread_id1, NULL);
    pthread_join (thread_id2, NULL);

    semctl (semid, IPC_RMID, 0);

	return 0;
}

void * routine1 (void * arg)
{
	while (1)
	{
		printf("Going to lock sem1\n");
		sem_change (0, -1);
		printf("sem1 is locked\n");

		printf("Going to lock sem2\n");
		sem_change (1, -1);
		printf("sem2 is locked\n");

		sem_change (0, 1);
		sem_change (1, 1);
	}
}

void * routine2 (void * arg)
{
	while (1)
	{
		printf("Going to lock sem1\n");
		sem_change (1, -1);
		printf("sem1 is locked\n");

		printf("Going to lock sem2\n");
		sem_change (0, -1);
		printf("sem2 is locked\n");

		sem_change (1, 1);
		sem_change (0, 1);
	}
}

void sem_change (int semnum, int add)
{
	struct sembuf mybuf;

	mybuf.sem_op = add;
    mybuf.sem_flg = 0;
    mybuf.sem_num = semnum;

    if (semop (semid , &mybuf, 1) < 0)
    {
        printf("Can`t wait for condition\n");
        exit(-1);
    }
}