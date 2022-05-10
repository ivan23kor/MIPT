#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "exec.h"

/*
 * я обычно объявления ф-й пишу в соответствующем заголовочном файле, т.е.
 * строчку ниже на вашем месте перенес в exec.h
 */
extern void assign (FILE * input, int string_count, cmd ** commands);

int main()
{
	//Initialisation
	int string_count = 0;
	int i = 0;
	int j = 0;
	int status = 0;
	int is_child = 0;

	char * buffer = (char *) malloc (MAX_ARGS * MAX_CHARS * sizeof (char));
	cmd * commands = NULL;
	FILE * input = fopen ("input.txt", "r");
	
	//Strings counting
	while (fgets (buffer, MAX_ARGS * MAX_CHARS, input) != NULL)
		string_count++;
	fseek (input, 0, SEEK_SET);
	
	/*Allocating memory for our commands (stored in structures cmd)
	corresponding to the string_count strings read.*/
	commands = (cmd *) malloc (string_count * sizeof (cmd));
	for (i = 0; i < string_count; i++)
	{
		commands[i].arguments = (char **) malloc (MAX_ARGS * sizeof (char *));
		for (j = 0; j < MAX_ARGS; j++)
			commands[i].arguments[j] = (char *) malloc (MAX_CHARS * sizeof (char));
	}
	
	/*Running function "assign" which fills
	structure commands with the values read from the file*/
	assign (input, string_count, &commands);

	//Execution of the commands
	for (i = 0; i < string_count; i++)
	{
/*
 * обычно is_something - название для булевских переменных, значение которых 0 или 1.
 * в вашем случае это не совсем так.
 */
		is_child = fork ();
		if (is_child == 0)
		{
			sleep (commands[i].delay);
			execvp (commands[i].arguments[0], commands[i].arguments);
			exit (1);
		}
	}

	//Freeing memory and closing the file
	for (i = 0; i < string_count; i++)
	{
		for (j = 0; j < MAX_ARGS; j++)
			if (j != commands[i].argc)
				free (commands[i].arguments[j]);
		free (commands[i].arguments);
	}
	free (commands);
	free (buffer);
	
	fclose (input);

	return 0;
}
