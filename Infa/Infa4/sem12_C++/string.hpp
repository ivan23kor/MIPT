#pragma once

class String
{
public:
	int size;
	char* str;

	String(  );
	String( int size_, char c );
	String( const char* s );
	~String(  );

	String& operator=( String other );
	bool operator==( String other ) const;
	bool operator!=( String other ) const;
	char operator[]( int index ) const;
	char operator[]( int index );
	int length(  ) const;

	void swap( String other );
};