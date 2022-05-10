#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define N 7

typedef int pid_t;

int main () {
	int i = 0;
	pid_t pid = 0;

	printf("pid = %d, ppid = %d\n", getpid (), getppid ());

	for (i; i < N; i++) {
		pid = fork ();
		sleep(1);
		if (pid == 0) {
			sleep (1);
			printf("pid = %d, ppid = %d\n", getpid (), getppid ());
			exit (pid);
		}
	}

	return 0;
}