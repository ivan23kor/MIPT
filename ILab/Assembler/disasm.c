#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define CMD_DEF(name, num, argc, code)\
    if (cmd_num == num)\
    {\
        switch (argc)\
        {\
            case 0:\
                fprintf (output, "%s\n", name);\
            break;\
            case 1:\
                assert (fread (&val1, sizeof (double), 1, input));\
                if (num < REG_num)\
                    assert (fprintf (output, "%s %.1lf\n", name, val1));\
                if ((num >= REG_num) && (num < JUMP_num))\
                {\
                    reg1[0] = (int)val1 + 'a';\
                    assert (fprintf (output, "%s %s\n", name, reg1));\
                }\
                if (num == CALL_num)\
                {\
                    assert (fprintf (output, "%s ip = %d\n", name, (int)val1));\
                    assert (fread (&val2, sizeof (double), 1, input));\
                }\
                if ((num >= JUMP_num) && (num < CALL_num))\
                    assert (fprintf (output, "%s ip = %d\n", name, (int)val1));\
            break;\
            case 2:\
                assert (fread (&val1, sizeof (double), 1, input));\
                assert (fread (&val2, sizeof (double), 1, input));\
                switch (num)\
                {\
                    case MOV_num:\
                        reg1[0] = (int)val1 + 'a';\
                        assert (fprintf (output, "%s %s %.1lf\n", name, reg1, val2));\
                    break;\
                    case ADD_num:\
                        reg1[0] = (int)val1 + 'a';\
                        reg2[0] = (int)val2 + 'a';\
                        assert (fprintf (output, "%s %s %s\n", name, reg1, reg2));\
                    break;\
                    case CMP_num:\
                        reg1[0] = (int)val1 + 'a';\
                        assert (fprintf (output, "%s %s %.1lf\n", name, reg1, val2));\
                    break;\
                }\
            break;\
        }\
    }

#define N 30

#define REG_num 7
#define MOV_num 14
#define ADD_num 15
#define CMP_num 16
#define JUMP_num 17
#define CALL_num 23

int main ()
{
    //REG_num: 'push 1' and 'push ax' have the same name, argc. the only difference is num
    //JUMP_num: similar to REG_num - 2nd argument of jumps is a label, not a register
    char *reg1;
    assert (reg1 = (char *) malloc (N * sizeof (char)));
    reg1[1] = 'x';
    reg1[2] = 0;
    char *reg2;
    assert (reg2 = (char *) malloc (N * sizeof (char)));
    reg2[1] = 'x';
    reg2[2] = 0;

    double cmd_num = 0.0; //number of a command. used for writing command num to the output
    double val1 = 0.0; //1st argument for two-argument commands
    double val2 = 0.0; //2nd argument for two-argument commands
    
    FILE *input;
    FILE *output;

    assert (input = fopen ("CPU.txt", "rb"));
    assert (output = fopen ("disasm.txt", "wb"));

    while ((fread (&cmd_num, sizeof (double), 1, input)) != 0) //retrieving next command
    {
        #include "cmd_list.h"
    }

    printf ("Disassembly completed.\n");
    
    assert (!fclose (input));
    assert (!fclose (output));

    free (reg1);
    free (reg2);

    return 0;
}