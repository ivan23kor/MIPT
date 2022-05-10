#include <iostream>
#include "string.hpp"
#include <new>
#include <cstdlib>

#define DEFAULT_SIZE 15
#define DEFAULT_CHAR 100

String::String(  )
{
	size = DEFAULT_SIZE;
	str = new char[size];

	int i = 0;
	for (i = 0; i < size; ++i)
		str[i] = DEFAULT_CHAR;
	str[i] = 0;
}

String::String( int size_, char c )
{
	size = size_;
	str = new char[size];

	int i = 0;
	for (i = 0; i < size; ++i)
		str[i] = c;
	str[i] = 0;
}

String::String( const char* s )
{
	int length_temp = 0;
	while ( s[length_temp] != 0 )
		length_temp++;

	size = length_temp;
	str = new char[size];

	int i = 0;
	for (i = 0; i < size; ++i)
		str[i] = s[i];
	str[i] = 0;
}

String::~String(  )
{
	size = 0;
	delete []str;
}

String& String::operator=( String other )
{
	this->swap( other );
	std::cout << "print" << std::endl;

	return *(this);
}

bool String::operator==( String other ) const
{
	if ( size != other.size )
		return false;
	for (int i = 0; i < size; ++i)
		if ( str[i] != other.str[i] )
			return false;
	return true;
}

bool String::operator!=( String other ) const
{
	if ( size != other.size )
		return true;

	for (int i = 0; i < size; ++i)
		if ( str[i] != other.str[i] )
			return true;
	return false;
}

char String::operator[]( int index ) const
{
	return str[index];
}

char String::operator[]( int index )
{
	return DEFAULT_CHAR;
}

int String::length(  ) const
{
	int length_temp = 0;
	while ( str[length_temp] != 0 )
		length_temp++;	
	return length_temp;
}

void String::swap( String other )
{
	int temp_int = size;
	size = other.size;
	other.size = temp_int;

	str = (char*)realloc( str, size * sizeof(char) );
	str = other.str;
}