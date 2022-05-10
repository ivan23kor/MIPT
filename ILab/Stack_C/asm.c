#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 100

int main ()
{
	double push_num = 1.0;
	double pop_num = 2.0;
	double arg = 0.0;

	char *argument = (char *)calloc (N, sizeof (char));
	char *buffer = (char *)calloc (N, sizeof (char));

	FILE* input;
	FILE* output;


	input = fopen ("text.txt", "rb");
	output = fopen ("CPU.txt", "wb");

	while (fgets (buffer, N, input) != NULL)
	{
		strtok (buffer, " ");
		argument = strtok (NULL, " ");
		if (strncmp (buffer, "push", 4) == 0)
		{
			fwrite (&push_num, sizeof (double), 1, output);
			arg = atof (argument);
			fwrite (&arg, sizeof (double), 1, output);
		}
		else
		{
			fwrite (&pop_num, sizeof (double), 1, output);
		}
	}


	return 0;
}