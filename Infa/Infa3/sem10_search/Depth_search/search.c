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

	printf("Input 1 for DFS, 2 for BFS.\n");
	scanf ("%d", &search_type);

	scanf ("%d", &n);

	matrix = (int **)malloc (n * sizeof (int *));
	for (int i = 0; i < n; ++i)
	{
		matrix[i] = (int *)malloc (n * sizeof (int));

		for (int j = 0; j < n; ++j)
			scanf ("%d", &matrix[i][j]);
	}

	if (search_type == 1)
	{

	}
	else
	{

	}

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			if (EMPTY == 1)
				printf("%d ", matrix[i][j]);
			else
			{
				
			}
			if (matrix[i][j] == 1)

		}

	for (int i = 0; i < n; ++i)
		free (matrix[i]);
	free (matrix);

	return 0;
}