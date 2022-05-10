#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_STRING 100

int fd[2];
char msg[MAX_STRING];
int client_number;

void * routine (void * arg);

int main(int argc, char const *argv[])
{
	int mode[2] = {O_RDONLY, O_WRONLY};
	int result = 0;

	pthread_t thread_id = 0;

	char * name[2] = {"fifo1.txt", "fifo2.txt"};

	if (argc != 2)
	{
		printf("Rerun with argument 1 for the first client, 2 for the second.\n");
		return 1;
	}

	client_number = atoi (argv[argc - 1]);
	if ((client_number != 1) && (client_number != 2))
	{
		printf("Input 1 or 2 as the first argument.\n");
		return 2;
	}

	if (mknod (name[0], S_IFIFO | 0666, 0) < 0)
	{
		if (errno != EEXIST)
		{
			printf("Could not create fifo!\n");
			return 3;
		}
	}
	if (mknod (name[1], S_IFIFO | 0666, 0) < 0)
	{
		if (errno != EEXIST)
		{
			printf("Could not create fifo!\n");
			return 3;
		}
	}

	if ((fd[0] = open (name[0], mode[client_number - 1])) < 0) 
	{
		printf("Could not open fifo1.\n");
		return 4;
	}
	if ((fd[1] = open (name[1], mode[2 - client_number])) < 0) 
	{
		printf("Could not open fifo2.\n");
		return 4;
	}

	result = pthread_create (&thread_id, (pthread_attr_t * )NULL, routine, NULL);
	if (result)
	{
		printf("Couldn't create thread. result = %d\n", result);
		exit (-1);
	}

	while (1)
	{
		fgets (msg, MAX_STRING, stdin);
		write (fd[2 - client_number], msg, strlen (msg) + 1);
	}

	return 0;
}

void * routine (void * arg)
{
	while (1)
	{
		read (fd[client_number - 1], msg, MAX_STRING);
		printf("%s\n", msg);
	}

	return NULL;
}