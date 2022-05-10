#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define DELAY 3e5
void my_handler1 (int nsig);
void my_handler2 (int nsig);

int child = 0;

int main(int argc, char const *argv[])
{
	pid_t pid = 0;

	child = fork ();
	if (child)
	{
		(void)signal (SIGUSR2, my_handler1);
	}
	else
	{
		(void)signal (SIGUSR1, my_handler2);
	}
	if (child)
		kill (getpid (), SIGUSR2);
	while (1);

	return 0;
}

void my_handler1 (int nsig)
{
	usleep (DELAY);
	printf("RT");
	fflush (NULL);
	kill (child, SIGUSR1);
}

void my_handler2 (int nsig)
{
	usleep (2 * DELAY);
	printf(" is the champion!\n");
	kill (getppid (), SIGUSR2);
}