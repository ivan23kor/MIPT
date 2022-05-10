#include <signal.h>
#include <stdio.h>

void my_handler (int nsig);

int main(int argc, char const *argv[])
{
	for (int i = 1; i <= 31; ++i)
		(void)signal(i, my_handler);
	while (1);
	
	return 0;
}

void my_handler (int nsig)
{
	printf ("\n%d\n", nsig);
}