#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define N 10

int main(int argc, char const *argv[])
{
	int i = 0;
	int fd;

	const char enter[1] = "\n";
	char * buffer = (char *) malloc (N * sizeof (char));

	fd = open ("input.txt", O_RDONLY | O_CREAT, 0666);
	if (fd < 0)
	{
		printf("ERROR!\n");
		return 1;
	}

	while (read (fd, buffer, N) == N)
	{
		write (1, buffer, N);
		write (1, enter, 1);
	}

	return 0;
}