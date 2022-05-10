#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SEM_COUNT 2

void increase (int semnum, int semid);
void decrease (int semnum, int semid);

int main(int argc, char const *argv[])
{
	int child = 0;
	int semid = 0;
	int fd[2] = {0, 0};
	int a = 1;
	int b = 2;
	int answer1 = 0;
	int answer2 = 0;

	key_t key;

	const char filename[] = "one_pipe.txt";

    if ((key = ftok (filename , 0)) < 0) {
        printf("Can`t generate key\n");
        exit(-1);
    }

    if ((semid = semget(key , SEM_COUNT, 0666 | IPC_CREAT)) < 0) {
        printf("Can`t get semid\n");
        exit(-1);
    }

    increase (1, semid);

    if (pipe (fd) < 0)
	{
		printf("Couldn't create pipe!\n");
		return -1;
	}

    child = fork ();

    if (child == 0)
    {
    	while (1)
	    {
	    	sleep (1);
	    	write (fd[0], &a, sizeof (int));
	    	write (fd[0], &b, sizeof (int));
	    	printf("1)Just sent numbers %d %d\n", a, b);

			decrease (0, semid);
			sleep(1);
	        read (fd[0], &answer1, sizeof (int));
			printf("1)Just got number %d\n", answer1);
			sleep(1);
			increase (1, semid);
	    }	
    }
    else
    {
    	while (1)
	    {
	    	decrease (1, semid);
	    	sleep(1);
	    	read (fd[1], &a, sizeof (int));
	    	read (fd[1], &b, sizeof (int));
			printf("2)Just got numbers %d %d\n", a, b);

	        answer2 = a + b;
	        sleep(1);
	    	write (fd[1], &answer2, sizeof (int));
	    	printf("2)Just sent number %d\n", answer2);
	    	sleep(1);
	    	increase (0, semid);
	    }
    }

    semctl (semid, IPC_RMID, 0);
    close (fd[0]);
    close (fd[1]);

	return 0;
}

void increase (int semnum, int semid)
{
	struct sembuf mybuf;

	mybuf.sem_op = 1;
    mybuf.sem_flg = 0;
    mybuf.sem_num = semnum;

    if (semop (semid , &mybuf, 1) < 0)
    {
        printf("Can`t wait for condition\n");
        exit(-1);
    }
}

void decrease (int semnum, int semid)
{
	struct sembuf mybuf;

	mybuf.sem_op = -1;
    mybuf.sem_flg = 0;
    mybuf.sem_num = semnum;

    if (semop (semid , &mybuf, 1) < 0)
    {
        printf("Can`t wait for condition\n");
        exit(-1);
    }
}