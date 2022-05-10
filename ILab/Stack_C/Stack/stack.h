#ifndef _STACKH_
#define _STACKH_
#include <stdio.h>

struct _stack
{
    double *data;
    double *top;
    double *max_size;
};

typedef _stack stack;

int stack_ctor (stack *stack1);
int stack_push (stack *stack1, double x);
double stack_pop (stack *stack1);
int stack_isempty (stack *stack1);
int stack_dump (stack *stack1);
int stack_dtor (stack *stack1);

#endif
