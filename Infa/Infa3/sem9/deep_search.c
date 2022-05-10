#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char const *argv[])
{
	int n = 6;
	int ** tree = (int **)malloc (n * sizeof (int *));
	for (int i = 0; i < n; ++i)
		tree[i] = (int *)malloc (n * sizeof (int));

	stack * stack_1;
	stack_ctor (stack_1);

	printf("Please input matrix 6x6.\n");
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			scanf ("%d", &(tree[i][j]));
			if (tree[i][j] == 1)
				stack_push (stack_1, tree[i][j]);
		}



	stack_dtor (stack_1);

	return 0;
}