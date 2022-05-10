#include <iostream>

template<typename U, typename V>
struct IsTheSame
{
	static const bool result = false;
};

template<typename U>
struct IsTheSame<U, U>
{
	static const bool result = true;
};

class A
{
	int x;
};

class B
{
private:
	int x;
};

class C
{
	int y;
};

int main(int argc, char const *argv[])
{
	std::cout << IsTheSame<A, C>::result << std::endl;
	
	return 0;
}
