#include <stdlib.h>
#include <stdio.h>

class vector
{
	int * arr;
	int bound;
public:
	vector (int len)
	{
		bound = len;
		arr = new int [len];
	}
	int & operator[] (int i)
	{
		if ((i < 0) || (i >= bound))
			throw i;
		else
			return arr[i];
	}
};

int main()
{
	int i = 0;
	vector v (7);

	try
	{
		i = 0;
		while (1)
			v[i] = i++;
	}
	catch (int i)
	{
		printf ("Exception %d\n", i);
	}
	
	return 0;
}