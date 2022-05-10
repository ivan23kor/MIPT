#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10e3

void * routine (void * arg);

int msqid = 0;
int semid = 0;

struct MyMsgBuf
{
	long mtype;
	struct info
	{
		int a;
		int b;
		int output;
		pid_t pid;
	} minfo;
};

struct sembuf mysembuf;

int main(int argc, char const *argv[])
{
	int len = 0;
	int maxlen = 0;

	pthread_t thread_id;

	struct MyMsgBuf mybuf;

	const char pathname[] = "server.c";

	key_t key = 0;

	if ((key = ftok (pathname, 0)) < 0)
	{
		printf("Server: Can't generate key!\n");
		exit (-1);
	}

	if ((msqid = msgget (key, 0666 | IPC_CREAT)) < 0)
	{
		printf("Server: Can't get msqid!\n");
		exit (-1);
	}

	if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0)
	{
        printf("Can`t get semid\n");
        exit(-1);
    }

	mysembuf.sem_op = N;
    mysembuf.sem_flg = 0;
    mysembuf.sem_num = 0;

    if (semop(semid, &mysembuf, 1) < 0)
    {
        printf("Can`t wait for condition\n");
        exit(-1);
    }

	while (1)
	{
		maxlen = sizeof (mybuf.minfo);

		if ((len = msgrcv(msqid, (struct msgbuf *)&mybuf, maxlen, 1, 0)) < 0)
	    {
	     	printf("Server: Can't receive message from queue\n");
	     	msgctl (msqid, IPC_RMID, (struct msqid_ds *)NULL);
	     	exit(-1);
	    }
	    if (mybuf.minfo.pid == -1)
	    	break;

	    mysembuf.sem_op = -1;
	    mysembuf.sem_flg = 0;
	    mysembuf.sem_num = 0;

	    if (semop(semid , &mysembuf , 1) < 0)
	    {
	        printf("Can`t wait for condition\n");
	        exit(-1);
	    }

	    if (pthread_create (&thread_id, (const pthread_attr_t *) NULL, routine, &mybuf) != 0)
	    {
	    	printf("Can not process the client with pid = %d.\n", mybuf.minfo.pid);
	    }
	}

	sleep(1);
	pthread_join (thread_id, (void **) NULL);
	
	msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
	semctl(semid, IPC_RMID, 0);

	return 0;
}

void * routine (void * arg)
{
	struct MyMsgBuf mybuf = *(struct MyMsgBuf *)arg;
	int len = sizeof (mybuf.minfo);

	mybuf.minfo.output = (mybuf.minfo.a) * (mybuf.minfo.b);
	mybuf.mtype = mybuf.minfo.pid;

	sleep (1);
	if ((msgsnd (msqid, (struct msgbuf*)&mybuf, len, 0)) < 0)
	{
		printf("Server: Can't send message to queue\n");
	    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
	    exit(-1);
	}

	mysembuf.sem_op = 1;
	mysembuf.sem_flg = 0;
	mysembuf.sem_num = 0;

	if (semop(semid, &mysembuf, 1) < 0)
	{
	    printf("Can`t wait for condition\n");
	    exit(-1);
	}
}