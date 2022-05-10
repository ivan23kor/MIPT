#include <string.h>
#include "stack.c"
#include <assert.h>
#define CMD_DEF(name, num, argc, code)\
        case num:\
            switch (argc)\
            {\
                case 2:\
                    fread (&val1, sizeof (double), 1, input);\
                    fread (&val2, sizeof (double), 1, input);\
                    code\
                    break;\
                case 1:\
                    fread (&val1, sizeof (double), 1, input);\
                    if (num == CALL_num)\
                        fread (&val2, sizeof (double), 1, input);\
                    code\
                    break;\
                case 0:\
                    code\
                    break;\
                default: break;\
            }\
            break;      

#define N 4
#define CALL_num 23

int main()
{
    double cmd = 0; //for numbers of commands
    double cmp = 0.0;
    double val1 = 0.0; //for 1st argument
    double val2 = 0.0; //for 2nd argument
    double *reg; //registers
    assert (reg = (double *) calloc (N, sizeof (double)));

    FILE *input;

    struct stack *asmstack;
    assert (asmstack = (struct stack *) malloc (sizeof (struct stack)));
    stack_ctor (asmstack);

    struct stack *call_stack;
    assert (call_stack = (struct stack *) malloc (sizeof (struct stack)));
    stack_ctor (call_stack);

    input = fopen ("CPU.txt", "rb");

    while (fread (&cmd, sizeof (double), 1, input) != 0)
    {
        switch ((int)cmd)
        {
            #include "cmd_list.h"

            default: break;
        }
    }

    fclose (input);

    stack_dtor (asmstack);
    stack_dtor (call_stack);
    free (reg);

    return 0;
}