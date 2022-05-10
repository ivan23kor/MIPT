#include <iostream>
#include "string.hpp"

int main(int argc, char const *argv[])
{
	String s1;
	String s2( "Ivan" );
	s1 = s2;
	//std::cout << "p" << std::endl;

	std::cout << s1.str << std::endl;
	
	return 0;
}