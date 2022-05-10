#include <stdio.h>

int main(int argc, char const * argv[], char * envp[])
{
	int i = 0;

	for (int i = 0; i < argc; i++)
		printf("%s\n", argv[i]);

	printf ("argc = %d\n==============================\n", argc);

	i = 0;
	while (envp[i]) {
		printf("%s\n", envp[i]);
		i++;
	}

	return 0;
}