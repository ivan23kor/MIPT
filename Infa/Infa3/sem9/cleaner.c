#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define MAX_SPLIT 2
#define MAX_NAME 20
#define TABLE_LIMIT 1
#define MICROSECONDS 1e6
#define SPEED 1

struct MyMsgBuf
{
	long mtype;
	struct info
	{
		float delay;				//cleaning time
		char name[MAX_NAME];		//item name
	} minfo;
};

int semid = 0;

void split (char * string, char * delim, char *** tokens, int * count);		//used for getting delay and name
void sem_inc (int n);				//increase semaphore
void sem_dec (int n);				//decrease semaphore

int main(int argc, char const *argv[])
{
	char ** tokens = (char **) malloc (MAX_SPLIT * sizeof (char *));
	for (int i = 0; i < MAX_SPLIT; ++i)
		tokens[i] = (char *) malloc (MAX_NAME * sizeof (char));
	char * buffer = (char *) malloc (MAX_NAME * sizeof (char));
	char delim[] = ":";
	const char end_work[] = "Good job!";
	const char dirty_name[] = "dirty.txt";
	const char pathname[] = "cleaner.c";

	int split_count = 0;
	int msqid = 0;

	size_t msgsz = 0;

	key_t key = 0;

	struct MyMsgBuf item;
	item.mtype = 1;

	//Dirty items come here
	FILE * dirty = fopen (dirty_name, "r");
	if (dirty == NULL)
	{
		printf("I can't find the table with dirty items!\n");
		return -1;
	}

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

    sem_inc (TABLE_LIMIT);		//TABLE_LIMIT items can be waiting for wiping

	while (1)
	{
		//Waiting for new items
		if (fgets (buffer, MAX_NAME, dirty) != NULL)
		{
			//End of work signal
			if (strncmp (buffer, end_work, strlen (end_work)) == 0)
				break;

			split (buffer, delim, &tokens, &split_count);
			if (split_count == 2)
			{
				strcpy (item.minfo.name, tokens[0]);
				item.minfo.delay = atof (tokens[1]);

				if (item.minfo.delay != 0.0)
				{
					usleep ((int)(MICROSECONDS * item.minfo.delay / SPEED));	//"Cleaning" an item

					sem_dec (1);

					//Passing a clean but wet item to the wiper
					msgsz = sizeof (item.minfo);
					if ((msgsnd (msqid, (struct msgbuf *)&item, msgsz, 0)) < 0)
					{
						printf("Can't send message to queue\n");
					    exit(-1);
					}
					printf ("%s is on the table to be wiped.\n", item.minfo.name);
				}
			}
		}
	}

	item.mtype = 2;
	if ((msgsnd (msqid, (struct msgbuf *)&item, msgsz, 0)) < 0)
	{
		printf("Can't send message to queue\n");
	    exit(-1);
	}

	free (buffer);
	fclose (dirty);
	for (int i = 0; i < MAX_SPLIT; ++i)
		free (tokens[i]);
	free (tokens);

 	return 0;
}

void split (char * string, char * delim, char *** tokens, int * count)
{
	int i = 0;

	char * temp = NULL;

	temp = strtok (string, delim);
	if (temp)
		strcpy ((*tokens)[i], temp);

	while (temp) {
		i++;
		if (i == MAX_SPLIT)
		{
			*count = i;
			return ;
		}
		temp = strtok (NULL, delim);
		if (temp)
			strcpy ((*tokens)[i], temp);
	}
	*count = i;
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

void sem_dec (int n)
{
	struct sembuf mybuf;

	mybuf.sem_op = -n;
    mybuf.sem_flg = 0;
    mybuf.sem_num = 0;

    if (semop(semid, &mybuf, 1) < 0)
    {
        printf("Can`t wait for condition\n");
        exit(-1);
    }
}