#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define INIT_SIZE 2

int stack_ctor (stack *stack1)
{
    assert (stack1->data = (double *)calloc (INIT_SIZE, sizeof (double)));
    stack1->top = stack1->data - 1;
    stack1->max_size = stack1->data + INIT_SIZE - 1;

    return 0;
}

int stack_push (stack *stack1, double x)
{
    if (stack1->top < stack1->max_size)
        *(stack1->top + 1) = x;
    else
    {
        int max_size = 2 * (stack1->max_size - stack1->data + 1);

        assert (stack1->data = (double *)realloc (stack1->data, max_size));
        stack1->max_size = stack1->data + max_size - 1;
        assert (*(stack1->top + 1) = x);
    }

    stack1->top++;

    return 0;
}

int stack_isempty (stack *stack1)
{
    if ((stack1->top) == (stack1->data - 1))
        return 1;
    else return 0;
}

double stack_pop (stack *stack1)
{
    double temp;

    assert (stack_isempty (stack1) != 1);

    temp = stack1->max_size - stack1->data + 1;
    if ((stack1->top - stack1->data + 1) < temp / 2.0)
    {
        stack1->data = (double *)realloc (stack1->data, 3 * temp / 4);
        int add = 3 * temp / 4;
        stack1->max_size = stack1->data + add - 1;
    }

    temp = *(stack1->top);
    stack1->top = stack1->top - 1;

    return temp;
}

int stack_dump (stack *stack1)
{
    int i = 0;
    int amount;

    if (stack_isempty (stack1) != 1)
    {
        printf ("The stack contains:");
        amount = (stack1->top - stack1->data);
        for (i; i <= amount; i++)
            printf (" %lg", *(stack1->data + i));
    }
    else
        printf ("The stack is empty");

    printf (".\n");

    return 0;
}

int stack_dtor (stack *stack1)
{
    free (&stack1);

    return 0;
}
