#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "stack.c"

int main()
{
    int answer = 1;
    double tmp = 0.0;
    stack stack1;
    double CHECK = 7.0;

    stack_ctor (&stack1);

    while (answer != 0)
    {
        printf ("Input the command.\n");
        scanf ("%d", &answer);
        switch (answer)
        {
            case 1:
                //scanf ("%lg", &CHECK);
                stack_push (&stack1, CHECK);

                break;

            case 2:
                tmp = stack_pop (&stack1);
                printf ("The last element is %lg.\n", tmp);

                break;

            case 3:
                if (stack_isempty (&stack1) == 1)
                    printf ("The stack is empty.\n");
                else
                    printf ("The stack is not empty.\n");

                break;

            case 4:
                stack_dump (&stack1);

                break;

            case 5:
                printf ("top: %d\n", (&stack1)->top);
                printf ("data: %d\n", (&stack1)->data);
                printf ("max_size: %d\n", (&stack1)->max_size);

                break;

            case 0:
                return 0;

            default:
                printf ("You had a typo in your input.\n");
                break;
        }
    }

    stack_dtor (&stack1);

    return 0;
}



