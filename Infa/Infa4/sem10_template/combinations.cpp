#include <iostream>

template <int n, int k>
struct C
{
	enum
	{
		result = C<n - 1, k - 1>::result + C<n - 1, k>::result
	};
};

template<>
struct C<0, 0>
{
	static const int result = 1;
};

template<int k>
struct C<k, 0>
{
	static const int result = 1;
};

template<int n>
struct C<n, n>
{
	static const int result = 1;
};

int main(int argc, char const *argv[])
{
	std::cout << C<2, 5>::result << std::endl;
	return 0;
}
