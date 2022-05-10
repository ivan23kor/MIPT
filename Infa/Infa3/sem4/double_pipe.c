#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define N 2

int main(int argc, char const *argv[])
{
	int if_child = 0;
	int check = 0;

	int p_c[2];
	int c_p[2];
	int input[N];
	input[0] = 50;
	input[1] = 7;
	int output[N];

	pipe (p_c);
	pipe (c_p);

	if ((p_c < 0) || (c_p < 0))
	{
		printf("Couldn't create pipe!\n");
		return -1;
	}

	if_child = fork ();
	if (if_child < 0)
	{
		printf("Couldn't fork process\n");
		return -1;
	}
	else if (if_child > 0)
	{
		close (p_c[0]);
		close (c_p[1]);
	}
	else
	{
		close (p_c[1]);
		close (c_p[0]);
	}

	if (if_child > 0)
	{
		check = write (p_c[1], input, N * sizeof (int));
		if (check != N * sizeof (int))
		{
			printf("%d\n", check);
			return 2;
		}
		printf("Parent (pid = %d). Just sent two numbers (%d and %d) to my child whose pid is %d.\n", getpid (), *input, input[1], if_child);
	}

	if (if_child == 0)
	{
		check = read (p_c[0], output, N * sizeof (int));
		if (check != N * sizeof (int))
		{
			printf("%d\n", check);
			return 2;
		}
		printf("Child (pid = %d). Just got two numbers (%d and %d) from my Dad (pid = %d).\n", getpid (), *input, input[1], getppid ());
		output[0] += output[1];
		check = write (c_p[1], output, sizeof (int));
		if (check != sizeof (int))
		{
			printf("%d\n", check);
			return 2;
		}
		printf("Child (pid = %d). Just sent the sum (%d) to my Dad (pid = %d).\n", getpid (), *input + input[1], getppid ());
	}
	if (if_child > 0)
	{
		check = read (c_p[0], input, sizeof (int));
		if (check != sizeof (int))
		{
			printf("%d\n", check);
			return 2;
		}
		printf("Parent (pid = %d). Just got hte sum from my son. The sum is %d\n", getpid (), *input);
	}

	return 0;
}