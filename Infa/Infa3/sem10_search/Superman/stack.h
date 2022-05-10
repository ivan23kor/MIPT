#ifndef _STACKH_
#define _STACKH_

typedef struct stack
{
    int *data; //the stack itself
    int top; //number of elements in stack (type of int because needed for hysteresis)
    int max_size; //maximum number of elements in stack (for now)
} stack;

int stack_ctor (struct stack *stack1); 
int stack_push (struct stack *stack1, int x);
int stack_pop (struct stack *stack1);
int stack_isempty (struct stack *stack1); //checks whether stack is empty (1 if empty, 0 otherwise)
int stack_dump (struct stack *stack1);
int stack_dtor (struct stack *stack1);

#endif