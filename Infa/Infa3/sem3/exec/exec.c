#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "exec.h"

/*
 * название файла не очень понятное. ф-и, описанные здесь, с "запуском" никак не связаны.
 */

/*
 * Мой компилятор писал предупреждение, т.к. вы вторым параметром предавали константную строку, а в сигнатуре ф-и 
 * const не было. Т.е. вы неявно снимаете константность. Лучше так не делать.
 */
void split (char * string, const char * delim, char *** tokens, int * count)
{
	int i = 0;

	char * temp = NULL;

	temp = strtok (string, delim);
	if (temp)
		strcpy ((*tokens)[i], temp);
	
	while (temp) {
		i++;
		temp = strtok (NULL, delim);
		if (temp)
			strcpy ((*tokens)[i], temp);
	}
	*count = i;
}

void assign (FILE * input, int string_count, cmd ** commands)
{
  int i = 0;
  int j = 0;
  int count = 0;

  char * buffer = (char *) malloc (MAX_ARGS * MAX_CHARS * sizeof (char));
  char ** tokens = (char **) malloc (MAX_ARGS * sizeof (char *));
  for (i = 0; i < MAX_ARGS; i++)
    tokens[i] = (char *) malloc (MAX_CHARS * sizeof (char));
/*
 * явно размер строчки можно не указывать. лучше так и делать, т.к. если в будущем захотите добавить новый разделитель, то надо будет 
 * изменить не один, а два символа.
 */
  const char delim[] = " ";

  for (i = 0; i < string_count; i++)
  {
    fgets (buffer, MAX_ARGS * MAX_CHARS, input);
/*
 * Я поменял местами ф-и assign и split, т.к. assign использует split -> split должны быть объявлена раньше.
 * Можете почитать про объявление и определение в языке С/С++ - это не одно и то же.
 */
    split (buffer, delim, &tokens, &count);

    (*commands)[i].delay = atof (tokens[count - 1]);
    (*commands)[i].argc = count - 1;
    for (j = 0; j < count - 1; j++)
      strcpy ((*commands)[i].arguments[j], tokens[j]);
    free ((*commands)[i].arguments[j]);
    (*commands)[i].arguments[j] = NULL;
  }

  free (buffer);
  for (i = 0; i < MAX_ARGS; i++)
    free (tokens[i]);
  free (tokens);
}
