#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

int main ()
{
	FILE* binary = fopen ("CPU.txt", "rb");

	double arg = 0.0;
	double num = 0.0;
	double stack[N];

	int sp = 0;
	int i = 0;

	while (fread (&num, sizeof (double), 1, binary) != 0)
	{
		if (num == 1)
		{
			fread (&arg, sizeof (double), 1, binary);
			stack[sp] = arg;
			sp++;
		}
		else if (num == 2)
		{
			sp--;
		}
	}

	fclose (binary);
	for (i = 0; i <= sp; i++)
	{
		printf ("%d ", (int)stack[i]);
	}
	printf ("\n");

	return 0;
}