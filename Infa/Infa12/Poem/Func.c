#include <math.h>
#include "Poem.h"
#include <stdio.h>

void line_dtor (line * Line);
line * add_recursive (line * temp, char * str, int index);

line ** text_ctor ()
{
	int i = 0;

	line ** text = NULL;

	assert (text = (line **)malloc (MAX_HASH * sizeof (line *))); //allocating memory for text

	for (i = 0; i < MAX_HASH; i++)
		text[i] = NULL; //initialising each text[i]

	return text;
}

line * line_ctor ()
{
	line * Line = NULL;

	assert (Line = (line *)malloc (sizeof (line)));           //allocating memory for Line

	assert (Line->str = (char *)malloc (N * sizeof (char)));  //allocating memory for Line->str
	Line->index = 0;
	Line->next = NULL;                                        //initialising Line->next

	return Line;
}

void text_dtor (line ** text)
{
	int i = 0;

	for (i; i < MAX_HASH; i++)
		if (text[i] != NULL)
			line_dtor (text[i]);

	free (text);
}

void line_dtor (line * Line)
{
	if (Line != NULL)
	{
		line_dtor (Line->next);
		free (Line->str);
		free (Line);
	}
}

int hash (char * str)
{
	int i = 0;
	int length = strlen (str);
	int hash_return = 1;
	
	for (i = 0; i < length - 1; i++)
	{
		// quirky hash calculations
		if (str[i] % 2 == 0)
			hash_return += (int)(MAX_HASH * log (MAX_HASH + str[i] - i));
		else
			hash_return = length + str[i] + i;

		hash_return = hash_return % MAX_HASH;
	}

	return hash_return;
}

line * line_add (line ** text, char * str, int index)
{
	int hash_value = hash (str);

	line * temp = line_ctor ();
	temp = text[hash_value];

	temp = add_recursive (temp, str, index); 

	return temp;
}

line * search_line (line ** text, char * str)
{
	int length = strlen (str);
	int hash_value = 0;		//hash function return
	line * temp = line_ctor ();

	str[length] = 0;		//the last symbol read by function "fgets" is '\n'

	hash_value = hash (str);

	if (text[hash_value] == NULL)	//if there are no such strings in the file
		return NULL;

	temp = text[hash_value];

	if (temp->next == NULL)		//if the only Line in the list of Lines
		return temp;
	else
	{
		while (strncmp (str, temp->str, length) != 0)
		{
			if (temp->next != NULL)
				temp = temp->next;
			else return NULL;
		}

		return temp;
	}
}

int remove_line (line ** text, char * str)
{
	int length = strlen (str);
	int hash_value = hash (str);		//hash function return

	line * temp2 = line_ctor ();
	line * temp = line_ctor ();
	
	str[length] = 0;		//the last symbol read by function "fgets" is '\n'

	if (text[hash_value] == NULL)	//if there are no such strings in the file
		return 1;

	temp = text[hash_value];
	if (temp->next == NULL)		//if the only Line in the list of Lines
	{
		free (temp->str);
		free (temp);
	}
	else if (strncmp (temp->str, str, length) == 0)
		temp = temp->next;
	else
	{
		while (strncmp (str, temp->next->str, length) != 0)
		{
			if (temp->next->next != NULL)
				temp = temp->next;
			else return 1;
		}

		free (temp->next->str);
		temp2 = temp->next;
		free (temp->next);
		temp = temp->next->next;
		free (temp2);
		return 0;
	}
}

	

line * add_recursive (line * temp, char * str, int index)
{
	if (temp == NULL)
	{
		temp = line_ctor ();
		strcpy (temp->str, str); 
		temp->index = index;
	}
	else
		temp->next = add_recursive (temp->next, str, index);

	return temp;
}
