//This particular application allows you to search a poem by a line in that poem

#include "Poem.h"

char is_name (char * str);
void poem_print (int start_line, int end_line, FILE * file);

int main ()
{
	int index = -1;               // start counter
	int length = 0;               // current length of buffer
	int current_line = 1;         // line counter
	int current_start = 1;        // the line where the current poem starts
	int current_hash = 0;         // the return of the hash function for the current line

	char testing[20] = "SCARLET";
	char answer[N];               // the answer to the question "Search another?" is stored here
	char buffer[N];
	int start[3 * MAX_HASH];      // numbers of starting strings are stored here
	line ** text = NULL;

	FILE * file = NULL;

	assert (file = fopen ("Poem.txt", "rb"));
	assert (text = text_ctor ());

	//adding all the strings to the hashtable
	while (fgets (buffer, N, file) != NULL)
	{
		buffer[strlen (buffer) - 1] = 0;

		//if the line is a name of a poem
		if (is_name (buffer) == 1)
		{
			index++;
			start [index] = current_line; //storing current start line
			current_start = current_line;
		}

		current_hash = hash (buffer);

		text[current_hash] = line_add (text, buffer, index); //adding

		current_line++;
	}
	index++;
	start[index] = 0;
	fseek (file, SEEK_SET, 0); //resetting the carriage to the beginning of the file

	printf ("The result of deletion is %d\n", remove_line (text, testing));

	//searching for the poem and printing an output
	answer[0] = 'Y';
	while (answer[0] == 'Y')
	{
		printf ("Input the string you want to search a poem with.\n");
		fgets (buffer, N, stdin);        //retrieving the string
		buffer[strlen (buffer) - 1] = 0; //the last symbol written - '\n' is useless

		if (search_line (text, buffer) == NULL)
			printf("Your poem could not be found.\n");
		else
		{
			index = (search_line (text, buffer))->index;
			if (start[index + 1] == 0)
				poem_print (start[index], current_line - 1, file);
			else
				poem_print (start[index], start[index + 1] - 1, file);
		}

		printf("Wanna search another poem?(Y/n)\n");
		fgets (answer, N, stdin); //retrieving the answer
	}

	assert (!fclose (file));
	text_dtor (text);

	return 0;
}

char is_name (char * str)
{
	int i = 0;
	char is_capital = 0;
	int length = strlen (str);

	for (i; i < length; i++)
		if (str[i] != ' ') //there can be empty strings in the file
			is_capital = 1;

	for (i = 0; i < length - 1; i++)
		if (((str[i] < 'A') || (str[i] > 'Z')) && (str[i] != '*') && (str[i] != ' ')) //if a name of a poem
			is_capital = 0;

	return is_capital;
}

void poem_print (int start_line, int end_line, FILE * file)
{
	char * buffer = (char *)malloc (N * sizeof (char));

	int i = 1;

	for (i; i < start_line; i++) //skipping through the lines before the poem found
		fgets (buffer, N, file);

	printf("=============================\nYour poem is:\n\n");
	for (i; i <= end_line; i++)
	{
		fgets (buffer, N, file);	//copying the next line from the file to buffer
		printf("%s", buffer);		//printing the next line on to the screen
	}
	printf ("=============================\n");
}
