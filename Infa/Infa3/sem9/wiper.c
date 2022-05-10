#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define MAX_NAME 20
#define MICROSECONDS 1e6
#define SPEED 1

struct MyMsgBuf
{
	long mtype;
	struct info
	{
		float delay;				//cleaning time
		char name[MAX_NAME];			//item name
	} minfo;
};

int semid = 0;

void sem_inc (int n);					//increase semaphore


int main(int argc, char const *argv[])
{
	const char pathname[] = "cleaner.c";

	int msqid = 0;

	size_t msgsz = 0;

	key_t key = 0;

	struct MyMsgBuf item;

	if ((key = ftok (pathname, 0)) < 0)
	{
		printf("Can't generate key!\n");
		return -1;
	}

	if ((msqid = msgget (key, 0666 | IPC_CREAT)) < 0)
	{
		printf("Can't get msqid!\n");
		exit (-1);
	}

	if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0)
	{
        printf("Can`t get semid\n");
        exit(-1);
    }

    while (1)
    {
    	msgsz = sizeof (item.minfo);
		if ((msgrcv(msqid, (struct msgbuf *)&item, msgsz, 0, 0)) < 0)
	    {
	      printf("Can't receive message from queue\n");
	      exit(-1);
	    }

	    if (item.mtype == 2)
	    	break;

	    usleep ((int)(MICROSECONDS * item.minfo.delay / SPEED));
	    sem_inc (1);
	    printf("%s is clean and dry!\n", item.minfo.name);
    }

	msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
	semctl(semid, IPC_RMID, 0);

	return 0;
}

void sem_inc (int n)
{
	struct sembuf mybuf;

	mybuf.sem_op = n;
    mybuf.sem_flg = 0;
    mybuf.sem_num = 0;

    if (semop(semid, &mybuf, 1) < 0)
    {
        printf("Can`t wait for condition\n");
        exit(-1);
    }
}