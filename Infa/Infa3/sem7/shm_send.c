#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define N 100

int main(int argc, char const *argv[])
{
	char message[N] = "Hello, bro.\n";
	char * shm;
	const char filename[] = "file.txt";

	const char proj = '0';

	key_t key = 0;
	int shmid = 0;

	if ((key = ftok (filename, proj)) < 0)
	{
		printf("Can't generate key!\n");
		exit (-1);
	}

	if ((shmid = shmget (key, N * sizeof (char), 0666 | IPC_CREAT | IPC_EXCL)) < 0)
	{
		if (errno != EEXIST)
		{
			printf("Can't create shared memory!\n");
			exit (-1);
		}
		if ((shmid = shmget (key, N * sizeof (char), 0)) < 0)
		{
			printf("Can't find shared memory!\n");
			exit (-1);
		}
	}

	if ((shm = (char *) shmat (shmid, NULL, 0)) == (char *) (-1))
	{
		printf("Can't attach memory!\n");
		exit (-1);
	}

	strcpy (shm, message);

	/*if (shmdt (shm) < 0)
	{
		printf("Can't detach shared memory!\n");
		exit (-1);
	}*/

	return 0;
}