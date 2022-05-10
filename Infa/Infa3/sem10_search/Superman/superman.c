#include <unistd.h>
#include <string.h>
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include "config.h"

#define MY_IF(i, j)\
if ((strings[i][j] != '#') && (strings[i][j] != 'S') && (visited[i * length + j] != 1))\
	stack_push (stack_1, i * length + j);
#define DESTROY()\
	fclose (input);\
	free (visited);\
	free (path);\
	for (i = 0; i < strings_count; ++i)\
		free (strings[i]);\
	free (strings);

void push_neighbours (stack * stack_1, int position);
int my_strlen (char * buffer); //does not include '\n'
int abs (int x);

/*
 * непонятные названия переменных. что за длина? что за количество строк? если вас покинула фанатазия, то нужно
 * хотя бы комментарии к переменным писать
 */
//input file contains strings_count strings of length symbols each - walls, paths, Superman and the treasure
int length = 0;
int strings_count = 0;
int * visited = NULL;
int * path = NULL;
char ** strings = NULL;

int main(int argc, char const *argv[])
{
	int i = 0;
  /*
   * старайтесь придерживаться одного стиля именования переменных: superman_position
   */
	int superman_position = 0;
	int $_position = 0;
	int one_superman = 0;
	int one_$ = 0;
	int path_index = 0;
	int correct_thread = 0;

  /*
   * stack_1 ? серьезно? родители же не называют детей сын1, дочь2 ... :)
   */
	stack stack_1[1];
	stack_ctor (stack_1);

	FILE * input = NULL;
	input = fopen ("input.txt", "ra");
  
/*
 * Если у вас ф-я больше чем 0.5 экрана, то с большой вероятностью её можно разбить на более мелкии ф-и.
 * Так лучше и делать. Например, считывание можно вынести в отдельную ф-ю.
 */
	char buffer[MAX_LENGTH];
	//Retrieve strings
	while (fgets (buffer, MAX_LENGTH, input) != NULL)
	{
		if (strings_count == 0)
			length = my_strlen (buffer);
		strings_count++;
		if (length != my_strlen (buffer))
		{
			printf("Invalid input at string %d!", strings_count);
			DESTROY()
			return -1;
		}
		else
			length = my_strlen (buffer);
	}
	
	//Allocation
	path = (int *)calloc (strings_count * length, sizeof(int));
	visited = (int *)calloc (strings_count * length, sizeof(int));
	strings = (char **)malloc (strings_count * sizeof (char *));
	for (i = 0; i < strings_count; ++i)
		strings[i] = (char *)malloc (MAX_LENGTH * sizeof (char));

	fseek (input, SEEK_SET, 0);
	for (int i = 0; i < strings_count; ++i)
		fgets (strings[i], MAX_LENGTH, input);

	//Retrieve 'S' and '$' positions
	for (int i = 0; i < strings_count; ++i)
		for (int j = 0; j < length; ++j)
		{
			if (strings[i][j] == 'S')
			{
				one_superman++;
				Superman_position = i * length + j;
			}
			if (strings[i][j] == '$')
			{
				one_$++;
				$_position = i * length + j;
			}
		}

		/*
     * нужна отдельная ф-я для dfs
     */
	//DFS
	if ((one_superman == 1) && (one_$ == 1))
	{
		stack_push (stack_1, Superman_position);
    /*
     * можно писать короче
     * 
     * while (!stack_isempty (stack_1))
     */
		while (stack_isempty (stack_1) == 0)
		{
			path[path_index] = stack_pop (stack_1);
			if (path[path_index] == $_position)
				break;
			if (visited[path[path_index]] == 0)
			{
        /*
         * я не до конца разобрался, что за path у вас.
         * но выглядит довольно нестандартно. вероятно можно написать более лаконичный код, в частности, для последующего вывода.
         * на семинаре расскажите, что за path такой
         */
				push_neighbours (stack_1, path[path_index]);
				visited[path[path_index]] = 1;
			}

			path_index++;
		}
	}
	else
	{
		printf("Invalid number of Supermen or dollars found!\n");
		DESTROY()
		return -1;
	}

	/*
   * нужна отдельная ф-я для вывода результата
   */
	if (path[path_index] == $_position)
	{
		while (path_index > 0)
		{
			if ((((abs(path[path_index] - path[path_index - 1]) == 1) && (path[path_index] / length == path[path_index - 1] / length) == 1)) || 
				((abs(path[path_index] - path[path_index - 1]) == length) && (path[path_index] / length != path[path_index - 1] / length)))
			{}
			else
			{
				for (int j = path_index - 1; j >= 0; --j)
				{
					if (((abs(path[path_index] - path[j]) == 1) && (path[path_index] / length == path[j] / length)) || 
						((abs(path[path_index] - path[j]) == length) && (path[path_index] / length != path[j] / length)))
					{
						correct_thread = j;
						correct_thread++;
						for (int k = path_index; path[k] != $_position; ++k)
						{
							path[correct_thread] = path[k];
							correct_thread++;
						}
						path[correct_thread] = $_position;
					}
				}
			}
			path_index--;
		}

		printf ("One of the possible paths will be being shown after you tap anything.\n");
		getchar ();
		sleep (DELAY);

		for (i = 1; (path[i] != $_position) || (i == 1); ++i)
		{
			system ("clear");

			for (int j = 0; j < length * strings_count; ++j)
			{
				if (j % length == 0)
					printf("\n");
				if (path[i] == j)
					strings[j / length][j % length] = '.';

				printf("%c", strings[j / length][j % length]);
			}
			printf("\n");

			usleep(SPEED);
		}
	}
	else
		printf("There is no path to $!\n");

	DESTROY()

	return 0;
}

void push_neighbours (stack * stack_1, int position)
{
  // это гораздо удобнее циклом записать, т.к. если потом будет 8 соседей, а не 4, то кода будет вдвое больше.
  // а при цикле размер кода не изменится. вроде бы даже в письме с описанием к задаче вставлял "правильные" кусочки кода
	int i = position / length;
	int j = position % length;
	int i_right = (position + 1) / length;
	int j_right = (position + 1) % length;
	int i_left = (position - 1) / length;
	int j_left = (position - 1) % length;
	int i_up = (position - length) / length;
	int j_up = (position - length) % length;
	int i_down = (position + length) / length;
	int j_down = (position + length) % length;

	if (i != 0)
	{
		MY_IF(i_up, j_up)
	}

	if (j != 0)
	{
		MY_IF(i_left, j_left)
	}

	if (i != strings_count - 1)
	{
		MY_IF(i_down, j_down)
	}

	if (j != length - 1)
	{
		MY_IF(i_right, j_right)
	}
}

int my_strlen (char * buffer)
{
	int length = strlen (buffer);

  /*
   * погуглите, что такое тернарный оператов
   */
	if (buffer[length - 1] == '\n')
		return length - 1;
	else return length;
}

int abs (int x)
{
  /*
   * есть ф-я модуля от числа в библиотеке math.h
   */
	if (x < 0)
		return -x;
}
