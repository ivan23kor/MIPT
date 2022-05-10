#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int msqid = 0;
	int len = 0;
	int maxlen = 0;
	int semid = 0;

	pid_t pid = getpid ();

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
	} mybuf;

	struct sembuf mysembuf;

	const char pathname[] = "server.c";

	key_t key = 0;

	if ((key = ftok (pathname, 0)) < 0)
	{
		printf("Client: Can't generate key!\n");
		exit (-1);
	}

	if ((msqid = msgget (key, 0666 | IPC_CREAT)) < 0)
	{
		printf("Client: Can't get msqid!\n");
		exit (-1);
	}

	if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0)
	{
        printf("Can`t get semid\n");
        exit(-1);
    }

	switch (argc)
	{
		case 3:
			mybuf.minfo.a = atoi (argv[1]);
			mybuf.minfo.b = atoi (argv[2]);
			if ((mybuf.minfo.a == 0) && (strlen (argv[1]) != 1))
			{
				printf("Invalid input!\n");
				exit (-1);
			}
			if ((mybuf.minfo.b == 0) && (strlen (argv[2]) != 1))
			{
				printf("Invalid input!\n");
				exit (-1);
			}
		break;
		case 2:
			if (strncmp (argv[1], "exit", 4) == 0)
				pid = -1;
			else
				mybuf.minfo.a = 3;
				mybuf.minfo.b = 5;
		break;
		default:
			mybuf.minfo.a = 3;
			mybuf.minfo.b = 5;
		break;
	}

	mybuf.mtype = 1;
	mybuf.minfo.pid = pid;
	len = sizeof (mybuf.minfo);

	if ((msgsnd (msqid, (struct msgbuf*)&mybuf, len, 0)) < 0)
	{
		printf("Client: Can't send message to queue\n");
	    exit(-1);
	}

	if ((argc == 2) && (strncmp (argv[1], "exit", 4) == 0))
		return 0;

	maxlen = sizeof (mybuf.minfo);
	if ((len = msgrcv(msqid, (struct msgbuf *)&mybuf, maxlen, pid, 0)) < 0)
    {
      printf("Client: Can't receive message from queue\n");
      exit(-1);
    }

    printf("%d * %d = %d\n", mybuf.minfo.a, mybuf.minfo.b, mybuf.minfo.output);

	return 0;
}