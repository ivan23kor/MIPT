#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "line.h"
#include "stack.h"

#define MAX_LENGTH 100

int main(int argc, char const *argv[])
{
	int search_type = 0;
	int n = 0;
	int ** matrix = NULL;

	char buffer[MAX_LENGTH];
	const char input_name[] = "matrix.txt";

	/*printf("Input 1 for DFS, 2 for BFS.\n");
	scanf ("%d", &search_type);
	if (search_type == 1)

	else
*/

	FILE * input = fopen (input_name, "rb");

	fgets (buffer, MAX_LENGTH, input);

	n = atoi (buffer);
	if (((n == 0) && (buffer[0] != 0)) || (strlen (buffer) > 2))
	{
		printf("Input correct size of the matrix!\n");
		return -1;
	}

	matrix = (int **)malloc (n * sizeof (int *));
	for (int i = 0; i < n; ++i)
	{
		matrix[i] = (int *)malloc (n * sizeof (int));
		
		for (int j = 0; j < n; ++j)
		{
			scanf ("%d", &matrix[i][j]);
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	fclose (input);
	for (int i = 0; i < n; ++i)
		free (matrix[i]);
	free (matrix);

	return 0;
}