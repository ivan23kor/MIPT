#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main ()
{
	int status = 0;
	int child_count = 0;
	int i = 0;
	int if_child = 0;
	int pid = 0;

	printf ("How many children should be created?\n");
	scanf ("%d", &child_count);

	if (child_count < 0) {
		printf("Input an integer >= 0 next time.\n");
		return 1;
	}

	printf ("Parent. pid = %d, ppid = %d\n", getpid (), getppid ());

	for (i; i < child_count; i++) {
		if (if_child == 0) {
			pid = getpid ();
			if_child = fork ();
			if (if_child == 0)
				printf("Child #%d created. pid = %d, ppid = %d\n", i + 1, getpid (), getppid ());
		}
		else
			wait (&status);
	}


	return 0;
}