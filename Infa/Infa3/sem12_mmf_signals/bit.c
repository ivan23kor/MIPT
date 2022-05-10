#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

/*
 * за my_handler_i явно кроются понятные названия
 */
void my_handler_receiver (int nsig);
void my_handler_sender (int nsig);

unsigned char c = 0;
int i = 0;
const char phrase[] = "Hello, World!";
char * bits = NULL;
int child = 0;

int main(int argc, char const *argv[])
{
	bits = (char *)malloc (strlen(phrase) * 8 * sizeof (char));
	for (i = 0; i < strlen (phrase); ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			bits[i * 8 + j] = (phrase[i] >> j) & 1;
		}
	}
	i = 0;

	child = fork ();
	if (child)
	{
		(void)signal (SIGUSR1, my_handler_sender);
		sleep (1);
	}
	else
	{
		(void)signal (SIGUSR1, my_handler_receiver);
		(void)signal (SIGUSR2, my_handler_receiver);
	}

	if (child)
		my_handler_sender (SIGUSR1);
	while (i < strlen (phrase) * 8);

	if (child)
		sleep (1); //in order if parent terminates earlier than the child, the latest may not print tha last character

	return 0;
}

/* У вас my_handler1 отличается от my_handler2 одной строчкой. Дублировать код очень плохо. Вы могли воспользоваться 
 любой из этих ф-й, добавив проверку, какой именно сигнал пришёл (посмотреть на nsig) */
void my_handler_receiver (int nsig)
{
	if ((i % 8 == 0) && (i != 0))
	{
		printf("%c", c);
		c = 0;	
	}
	if (nsig == SIGUSR1)
		c += (1 << (i % 8));
	kill (getppid (), SIGUSR1);
	i++;
}

void my_handler_sender (int nsig)
{
	if (child > 0)
		kill (child, bits[i] ? SIGUSR1 : SIGUSR2);
    /*
     * тернарный оператор позволяет писать лаконичный код:
     * kill (child, bits[i]? SIGUSR1 : SIGUSR2);
     */
	else
		printf("Child's pid is below zero!\n");
}
