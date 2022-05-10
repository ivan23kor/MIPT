class CVector
{
	
};





int * pa;
int & ra;

int a = 10;
pa = &a;
ra = a;
ra = 20;
*pa
ra


namespace name_1
{
	int f(int, int)
	{

	}
};


namespace name_2
{
	int f(int, int)
	{

	}
};

name_1::f(1,2)
name_2::f(1,2)

cin
cout
to_string
min
max


int a = 1, b = 2;

int c = a+b;

class Complex
{
private:
	int x,y;
	static num;
public:
	Complex(int a, int b)
	{
		x=a;
		y=b;
		std::cout << "Ct" << std::endl;
	}
	Complex & operator+(Complex& v2)
	{
		Complex tmp(x+v2.x,y+v2.y);
		return tmp;
	}
	Complex & operator+(int v)
	{
		Complex tmp(x+v,y);
		return tmp;
	}
	Complex & operator=(Complex& v2)
	{
		x = v2.x;
		y = v2.y;
		return v2;
	}
    static int get_num()
	{
		return num;
	}
};

struct test
{
	int a : 3;
	int b : 5;
	int c : 8;
};

#include <stdint.h>

uint8_t c[100];
c[i]&0x4
c[i] = c[i] | 0x4;
c[i] = c[i] & (~0x4);
[01101100]
 11111011
 c[i]<<1;
 >>

Complex c1(1,1),c2(2,2);
Complex c3 = c1 = c2;

++
--

a++
++a

+
-
* //()
^ //
[]
++
--

a[i] = b
b = a[i]


Complex::get_num();


#include <vector>

std::vector<int> v;
v.push_back(1);
v.pop_back();
v[i] 
v.sort()
v.size()
v.empty()