#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define CMD_DEF(name, num, argc, code)\
    if ((strncasecmp (name, command, length) == 0) && (strlen (name) == length) && (argc == arg_count))\
    {\
        switch (arg_count)\
        {\
            case 0:\
                cmd_num = num;\
                assert (fwrite (&cmd_num, sizeof (double), 1, binary));\
                ip++;\
            break;\
            case 1:\
                if (((isdigit (arg1[0]) != 0) || (arg1[0] == '-')) && (num < REG_num))\
                {\
                    cmd_num = num;\
                    assert (fwrite (&cmd_num, sizeof (double), 1, binary));\
                    tmp = atof (arg1);\
                    assert (fwrite (&tmp, sizeof (double), 1, binary));\
                    ip += 2;\
                }\
                if ((isdigit (arg1[0]) == 0) && (arg1[0] != '-') && (num >= REG_num) && (num < JUMP_num))\
                {\
                    cmd_num = num;\
                    assert (fwrite (&cmd_num, sizeof (double), 1, binary));\
                    reg1 = arg1[0] - 'a';\
                    assert (fwrite (&reg1, sizeof (double), 1, binary));\
                    ip += 2;\
                }\
                if (num == CALL_num)\
                {\
                    cmd_num = num;\
                    assert (fwrite (&cmd_num, sizeof (double), 1, binary));\
                    for (i = 0; i < count; i++)\
                    {\
                        if (strncmp (arg1, lbl[i].labelname, (int)(strlen (lbl[i].labelname))) == 0)\
                        {\
                            tmp = lbl[i].ip;\
                            assert (fwrite (&tmp, sizeof (double), 1, binary));\
                        }\
                    }\
                    ip += 3;\
                    tmp = ip;\
                    assert (fwrite (&tmp, sizeof (double), 1, binary));\
                }\
                if ((num >= JUMP_num) && (num < CALL_num))\
                {\
                    cmd_num = num;\
                    assert (fwrite (&cmd_num, sizeof (double), 1, binary));\
                    for (i = 0; i < count; i++)\
                    {\
                        if (strncmp (arg1, lbl[i].labelname, (int)(strlen (lbl[i].labelname))) == 0)\
                        {\
                            tmp = lbl[i].ip;\
                            assert (fwrite (&tmp, sizeof (double), 1, binary));\
                        }\
                    }\
                    ip += 2;\
                }\
            break;\
            case 2:\
                cmd_num = num;\
                assert (fwrite (&cmd_num, sizeof (double), 1, binary));\
                switch (num)\
                {\
                    case MOV_num:\
                        reg1 = arg1[0] - 'a';\
                        assert (fwrite (&reg1, sizeof (double), 1, binary));\
                        tmp = atof (arg2);\
                        assert (fwrite (&tmp, sizeof (double), 1, binary));\
                        ip += 3;\
                    break;\
                    case ADD_num:\
                        reg1 = arg1[0] - 'a';\
                        assert (fwrite (&reg1, sizeof (double), 1, binary));\
                        reg2 = arg2[0] - 'a';\
                        assert (fwrite (&reg2, sizeof (double), 1, binary));\
                        ip += 3;\
                    break;\
                    case CMP_num:\
                        reg1 = arg1[0] - 'a';\
                        assert (fwrite (&reg1, sizeof (double), 1, binary));\
                        tmp = atof (arg2);\
                        assert (fwrite (&tmp, sizeof (double), 1, binary));\
                        ip += 3;\
                    break;\
                }\
            break;\
        }\
    }

#define CARRIAGE_RETURN 13
#define N 30
#define L 100

#define REG_num 7
#define MOV_num 14
#define ADD_num 15
#define CMP_num 16
#define JUMP_num 17
#define CALL_num 23

struct _label
{
    char *labelname; //a name of the label
    int ip; //number of commands&arguments before the label
};
typedef struct _label label;

int my_strlen (char *str);

int main ()
{
    int count = 0; //number of labels
    int arg_count = 0; //number of arguments of a command
    int ip = 0; //number of commands&arguments before a label
    int length = 0; //length of command string
    int i = 0; //cycle parameter
    int j = 0; //cycle parameter

    char *arg1; //1st argument of a command
    assert (arg1 = (char *) malloc (N * sizeof (char)));
    char *arg2; //2nd argument of a command
    assert (arg2 = (char *) malloc (N * sizeof (char)));
    char *command;
    assert (command = (char *) malloc (N * sizeof (char)));
    
    double cmd_num = 0.0; //number of a command (as in "cmd_list.h")
    double tmp = 0.0; //used for writting arguments to the output
    double reg1 = 0.0; //1st register (for two-argument commands)
    double reg2 = 0.0; //2nd register (for two-argument commands)
    
    label *lbl; //array of labels
    lbl = (label *) malloc (L * sizeof (label));

    FILE *text; //input
    FILE *binary; //output

    assert (binary = fopen ("CPU.txt", "wb"));
    assert (text = fopen ("text.txt", "rb"));

    while (fgets (command, N, text) != NULL) //strings 146 - 167: adding labels to the array
    {
        ip++;
        command = strtok (command, " ");
        length = my_strlen (command);
        arg1 = strtok (NULL, " "); //retrieving 1st argument
        arg2 = strtok (NULL, " "); //retrieving 2nd argument
        if (arg1) ip++;
        if (arg2) ip++;
        if (strncasecmp ("CALL", command, 4) == 0) ip++; //CALL gets one argument but prints two
        if (command[length - 1] == ':')
        {
            ip--; //if label found
            lbl[i].labelname = (char *) malloc (N * sizeof (char));
            for (j = 0; j < length - 1; j++)
                lbl[i].labelname[j] = command[j];
            lbl[i].labelname[j] = 0;
            lbl[i].ip = ip;
            i++;
        }
    }
    count = i;

    assert (!fseek (text, 0, SEEK_SET)); //returning carriage to the start of file

    ip = 0;
    while (fgets (command, N, text) != NULL) //strings 172 - 185: writing commands to the output
    {
        command = strtok (command, " ");
        length = my_strlen (command);
        arg1 = strtok (NULL, " ");
        arg2 = strtok (NULL, " ");
        if (arg1) arg_count++;
        if (arg2) arg_count++;
        if (command[length - 1] != ':')
        {
            #include "cmd_list.h"
        }
        arg_count = 0;
    }

    assert (!fclose (binary));
    assert (!fclose (text));

    free (arg1);
    free (arg2);
    free (command);

    printf ("Assembly completed.\n");

    return 0;
}

int my_strlen (char *str)
{
    int k = 0;

    for (k; (str[k] != '\0') && (str[k] != '\n') && (str[k] != CARRIAGE_RETURN); k++);

    return k;
}