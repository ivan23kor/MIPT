#include "Vector.h"

int main()
{
	CVector <float>* v = new CVector <float> [5];

	v[0][0] = 1;
	v[0][1] = 0;
	v[0][2] = 0;
	v[1][0] = 1;
	v[1][1] = 1;
	v[1][2] = 0;
	v[2][0] = 1;
	v[2][1] = 2;
	v[2][2] = 3;
	v[3][0] = 1;
	v[3][1] = 2;
	v[3][2] = 3;

	std::cout << (v[0] ^ v[1]);
	std::cout << "===============\n";

	return 0;
}