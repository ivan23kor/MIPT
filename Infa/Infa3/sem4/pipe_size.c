#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int fd[2];
	int i = 1;

	const char byte[1] = "1";

	if (pipe (fd) < 0)
	{
		printf("Couldn't create pipe!\n");
		return -1;
	}

	for (i = 1; write (fd[1], byte, 1) == 1; i++)
		printf("%d\n", i);

	return 0;
}