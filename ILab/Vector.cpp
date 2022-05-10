#include <iostream>
#include <assert.h>

class CVector
{
	int size;
	int *data;
public:
	int &operator[] (int index)
	{
		assert ((0 <= index) && (index < size));
		return data[index];
	}
	CVector (int new_size)
	{
		size = 10;
		data = new int[size];
	}
};

int main ()
{
	CVector v (10);

	//int m = v[2]; <=> int m = v.operator[] (2);
	/*v[2] (implies) v.data[2]; - impossible this way
	should be done so: v.operator[](2) = 7;*/
	v.operator[](2) = 17;
	std::cout << v.operator[](2) << "\n";

	return 0;
}

//namespace DV: +=, -=, +, -, length mul number, length div number, scalar mul