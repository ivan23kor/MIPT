#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

void split (char * string, char * delim, char *** tokens, int * count);

int main () {
	int i = 0;
	int count = 0;

	char delim[] = " ,;";
	char * string = (char *) (malloc (N * sizeof (char)));
	char ** tokens = (char **) (malloc (N * sizeof (char *)));

	for (i; i < N; i++)
		tokens[i] = (char *) (malloc (N * sizeof (char)));

	fgets (string, N, stdin);

	split (string, delim, &tokens, &count);

	i = 0;
	for (i; i < count; i++)
		printf ("%s\n", tokens[i]);

	i = 0;
	for (i; i < N; i++) {
		if (tokens[i] != NULL)
			free (tokens[i]);
	}
	free (string);
	free (tokens);

	return 0;
}

void split (char * string, char * delim, char *** tokens, int * count) {
	int i = 0;

	char * temp = NULL;

	temp = strtok (string, delim);
	if (temp)
		strcpy ((*tokens)[i], temp);

	while (temp) {
		i++;
		temp = strtok (NULL, delim);
		if (temp)
			strcpy ((*tokens)[i], temp);
	}
	*count = i;

	return;
}