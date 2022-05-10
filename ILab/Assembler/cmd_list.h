#ifndef cmd_list
#define cmd_list

CMD_DEF("END", 0, 0, return 0;)

CMD_DEF("PUSH", 1, 1, stack_push (asmstack, val1);)

CMD_DEF("POP", 2, 0, stack_pop (asmstack);)

CMD_DEF("ADD", 3, 0, stack_push (asmstack, stack_pop (asmstack) + stack_pop (asmstack));)

CMD_DEF("SUB", 4, 0, stack_push (asmstack, stack_pop (asmstack) - stack_pop (asmstack));)

CMD_DEF("MUL", 5, 0, stack_push (asmstack, stack_pop (asmstack) * stack_pop (asmstack));)

CMD_DEF("DIV", 6, 0, stack_push (asmstack, stack_pop (asmstack) / stack_pop (asmstack));)

CMD_DEF("PRINT", 7, 1, printf ("%cx = %.1lf\n", (char)('a' + (int)val1), reg[(int)val1]);)

CMD_DEF("PRINT", 8, 0,  if (stack_isempty (asmstack) == 1)\
                        {\
                            printf ("The stack is empty.\n");\
                            return 0;\
                        }\
                        val1 = stack_pop (asmstack);\
                        stack_push (asmstack, val1);\
                        printf("The last element in stack is %.1lf.\n", val1);)

CMD_DEF("DEC", 9, 1, reg[(int)val1]--;)

CMD_DEF("INC", 10, 1, reg[(int)val1]++;)

CMD_DEF("DUMP", 11, 0, stack_dump (asmstack);)

CMD_DEF("POP", 12, 1, reg[(int)val1] = stack_pop (asmstack);)

CMD_DEF("PUSH", 13, 1, stack_push (asmstack, reg[(int)val1]);)

CMD_DEF("MOV", 14, 2, reg[(int)val1] = val2;)

CMD_DEF("ADD", 15, 2, reg[(int)val1] += reg[(int)val2];)

CMD_DEF("CMP", 16, 2, cmp = reg[(int)val1] - val2;)

CMD_DEF("JE", 17, 1, if (cmp == 0.0) fseek (input, (int)val1 * sizeof (double), SEEK_SET);)

CMD_DEF("JNE", 18, 1, if (cmp != 0.0) fseek (input, (int)val1 * sizeof (double), SEEK_SET);)

CMD_DEF("JL", 19, 1, if (cmp < 0.0) fseek (input, (int)val1 * sizeof (double), SEEK_SET);)

CMD_DEF("JG", 20, 1, if (cmp > 0.0) fseek (input, (int)val1 * sizeof (double), SEEK_SET);)

CMD_DEF("JLE", 21, 1, if (cmp <= 0.0) fseek (input, (int)val1 * sizeof (double), SEEK_SET);)

CMD_DEF("JGE", 22, 1, if (cmp >= 0.0) fseek (input, (int)val1 * sizeof (double), SEEK_SET);)

CMD_DEF("CALL", 23, 1, fseek (input, (int)val1 * sizeof (double), SEEK_SET); stack_push (call_stack, val2);)

CMD_DEF("RET", 24, 0,   if (stack_isempty (call_stack) == 0)\
                        {\
                            val1 = stack_pop (call_stack);\
                            fseek (input, (int)val1 * sizeof (double), SEEK_SET);\
                        }\
                        else\
                        {\
                            printf ("ERROR! No calls found before this ret.\n");\
                            return 0;\
                        })
#endif