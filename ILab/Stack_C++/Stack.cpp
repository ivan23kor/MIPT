#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include "Stack.h" //class CStack & functions

#define INIT_SIZE 10 //initial size of stack
#define EXTEND 5 //amount of reallocated memory (in elements) when extending

int CStack::stack_count = 0; //initializing stack_count

CStack::CStack(int new_size) //stack constructor
{
	assert (data = new double[INIT_SIZE]);
	ptr = 0;
	size = new_size;
	stack_count++;
}

CStack::~CStack()
{
	delete data;
}

void CStack::push (double x) //adds x to the stack
{
	assert (this);
	if (ptr == size - 1) //checks for free space in the stack
	{
		size += EXTEND; //increases the size of the stack for 5 more elements
		assert (data = (double *)realloc (data, size * sizeof (double))); //allocates more memory
	}
	data[ptr] = x; //adds x to the top of the stack
	ptr++;
}

double CStack::pop () //takes away the top element of the stack and returns its value
{
	assert (this);
	assert (!(this->is_empty ()));
	
	ptr--;
	return data[ptr];
}

int CStack::is_empty () //checks if the stack is empty
{
	assert (this);

	if (ptr == 0)
		return 1;
	else
		return 0;
}

void CStack::dump () //prints the stack onto the screen
{
	assert (this);
	if (this->is_empty ())
		std::cout << "The stack is empty\n";
	else
	{
		std::cout << "The stack contains: ";
		for (unsigned i = 0; i < ptr; i++)
			std::cout << data[i] << " ";
		std::cout << "(oldest to newest)\n";
	}

	return;
}