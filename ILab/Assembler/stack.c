#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define INIT_SIZE 6

int stack_ctor (struct stack *stack1)
{
    assert (stack1->data = (double *) malloc (INIT_SIZE * sizeof (double)));
    stack1->top = 0;
    stack1->max_size = INIT_SIZE;

    return 0;
}

int stack_push (struct stack *stack1, double x)
{
    if (stack1->top == stack1->max_size)
    {
        stack1->max_size *= 2.0; //reallocating twice more memory if not enough
        assert (stack1->data = (double *)realloc (stack1->data, ((int)(stack1->max_size)) * sizeof (double)));
    }

    (stack1->data)[(int)(stack1->top)] = x;
    stack1->top += 1.0;

    return 0;
}

int stack_isempty (struct stack *stack1)
{
    if ((int)(stack1->top))
        return 0;
    else return 1;
}

double stack_pop (struct stack *stack1)
{
    assert (stack_isempty (stack1) != 1);

    if (((stack1->top) < ((stack1->max_size) / 2.0)) && (stack1->max_size > (INIT_SIZE - 1))) //if more than a half of stack memory is not used
    {
        stack1->max_size = (int)(3 * stack1->max_size / 4); //shrink the size of stack to 75% of current
        stack1->data = (double *)realloc (stack1->data, (int)(stack1->max_size) * sizeof (double));
    }

    stack1->top -= 1.0;

    return ((stack1->data)[(int)(stack1->top)]);
}

int stack_dump (struct stack *stack1)
{
    int i = 0;

    if (stack_isempty (stack1) != 1)
    {
        printf ("The stack contains:");
            for (i; i < (stack1->top); i++)
                printf (" %.1lf", (stack1->data)[i]);
            printf (".\n");
    }
    else printf ("The stack is empty.\n");

    printf ("%d bytes are allocated for stack.\n", 8 * (int)(stack1->max_size));
    printf ("%d bytes are available in stack.\n\n", 8 * (int)(stack1->max_size - stack1->top));

    return 0;
}

int stack_dtor (struct stack *stack1)
{
    free (stack1);

    return 0;
}