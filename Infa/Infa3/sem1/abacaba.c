#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GenerateString (int n);
 
int main () {
	int n = 0;

	printf ("Input the number of strings.\n");
	scanf ("%d", &n);

	if (n <= 0) {
		printf ("Invalid input!\n");
		return -1;
	}
	else {
		printf("Here are the strings:\n");
		GenerateString (n);
	}

	return 0;
}

/*
 * У вас хороший код в целом.
 * Обычно, когда пишут отдельную ф-ю, то предполагают, что её можно как-то в неизменном виде использовать в другой задаче, например.
 * Когда вы выделяете память, освобождаете её и печатаете результат внутри этой ф-и, то возможности повторно использовать этот код 
 * фактически нет ...
 * Лучше было бы выделять и освобождать память снаружи. Печать результат тоже вне ф-и.
 * void GenerateString (int n, char* resultString);
 * У вас же ф-я называется "сгенерировать строку".
 * Вот она и должна делать ровно это.
 */

void GenerateString (int n) {
	int i = 0;

	char * string = (char *) malloc ((1 << n) * sizeof (char));
	char * temp = (char *) malloc ((1 << n) * sizeof (char));

	for (i; i < n; i++) {
		strcpy (temp, string);
		string[(1 << i) - 1] = 'a' + i;
		string[1 << i] = 0;
		strcat (string, temp);
		printf("%s\n", string);
	}

	free (temp);
	free (string);
}
