#include <stdio.h>

typedef int (* MyFunc) (void * int1, void * int2);

void swap (void * int1, void * int2)
{
	int temp = *((int *)int1);
	*((int *)int1) = *((int *)int2);
	*((int *)int2) = temp;
}

void _quicksort (int first, int last, int size, void * array, MyFunc compare)
{
	int i = first;
	int j = last;
	int pivot = (*(int *)(array + size * first) + *(int *)(array + size * last) + *(int *)(array + size * ((first + last) / 2))) / 3;

	while (i < j)
	{
		while (compare (array + size * i, &pivot) < 0)
			i++;
		
		while (compare (&pivot, array + size * j) < 0)
			j--;

		if (i <= j)
		{
			swap (array + size * i, array + size * j);
			i++;
			j--;
		}
	}

	if (j > 0)
		_quicksort (0, j, size, array, compare);
	if (i < last)
		_quicksort (i, last, size, array, compare);
}

void quicksort (void * array, int count, int size, MyFunc compare)
{
	_quicksort (0, count - 1, size, array, compare);
}

int compare (void * int1, void * int2)
{
	return *((int *)int1) - *((int *)int2);	
}

int main(int argc, char const *argv[])
{
	int array[4] = {4, 3, 2, 1};

	quicksort (array, 4, sizeof (int), compare);

	for (int i = 0; i < 4; ++i)
		printf("%d ", array[i]);

	printf("\n");

	return 0;
}