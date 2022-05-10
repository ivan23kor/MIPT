#ifndef _STACKH_
#define _STACKH_

struct stack
{
    double *data; //the stack itself
    double top; //number of elements in stack (type of double because needed for hysteresis)
    double max_size; //maximum number of elements in stack (for now)
};

int stack_ctor (struct stack *stack1); 
int stack_push (struct stack *stack1, double x);
double stack_pop (struct stack *stack1);
int stack_isempty (struct stack *stack1); //checks whether stack is empty (1 if empty, 0 otherwise)
int stack_dump (struct stack *stack1);
int stack_dtor (struct stack *stack1);

#endif