#ifndef _STACKH_
#define _STACKH_

class CStack
{
	double *data;
	int ptr; //current number of elements in the stack
	int size; //max current size of the stack
public:
	CStack(int new_size); //constructor
	~CStack(); //destructor

	void push(double x);
	double pop();
	int is_empty();
	void dump();
	static int stack_count; //amount of stacks used
};

#endif