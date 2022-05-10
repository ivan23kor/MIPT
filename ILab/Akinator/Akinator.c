#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define N 100
#define COUNT 4
#define REPEAT\
		fgets (str, N, stdin);\
		while ((str[0] != 'Y') && (str[0] != 'N') || (str[1] != '\n'))\
		{\
			printf ("Input 'Y' for yes, 'N' for no.\n");\
			fgets (str, N, stdin);\
		}
#define REINPUT(string, mode)\
			fgets (string, N, stdin);\
			while (how_many (string, mode) == 1)\
			{\
				mistake++;\
				if (mistake % 2 == 0)\
					printf ("%s", Rules);\
				printf ("Reinput, please.\n");\
				fgets (string, N, stdin);\
			}\
			mistake = 0;

char Rules[] = {"\nEnter answers to the system ending with '.' sign, questions - with '?' sign. (when Geanie is incorrect)\nEnter questions to the system ending with '?' sign. (when Geanie is incorrect)\nDo not use '[' and ']' symbols.\n"};

FILE *text;

struct _node
{
	char *phrase;
	struct _node *left;
	struct _node *right;
};	
typedef struct _node node;

node *file_to_mem (node *tree); 		//copies the tree from the file to the memory
void mem_to_file (node *tree); 			//writes the new tree to the files
node *game (node *tree); 				//the game itself
int how_many (char *str, int mode); 	//checks whether new sentences are correct (contain '.' or '?' at the end)
void tree_destruct(node *tree); 			//freeing memory from the tree
node *node_ctor (node *tree, char *str); 	//adds str (phrase) to the node (tree)

int main ()
{
	setlocale(LC_ALL, "Rus");

	char *str = (char *)malloc (N * sizeof (char));

	node *tree = NULL;

	assert (text = fopen ("/home/ivan23kor/Documents/Saves/Code/ILab/C_C++/Akinator/text.txt", "rb"));

	tree = file_to_mem (tree);

	printf ("\nПривет, как дела?\nHi, I'm Geanie.\nNeed the rules?(Input 'Y' for yes or 'N' for no.)\n");
	REPEAT
	if (str[0] == 'Y')
	{
		printf ("\nRiddle a word. Answer questions with 'Y' for yes or 'N' for no.");
		printf ("%s", Rules);
		printf ("\nNow riddle something and I'll try to guess it/him/her.\n\n");
	}
	else
		printf ("\nOkay, riddle something and I'll try to guess it/him/her.\n\n");

	str[0] = 'Y';
	while (str[0] == 'Y')
	{
		tree = game (tree);

		
		printf ("\nWould you like another game? (Y/N)\n");
		REPEAT
	}

	assert (!fclose (text));
	assert (text = fopen ("text.txt", "wb"));
	mem_to_file (tree);
	assert (!fclose (text));
	tree_destruct (tree);
	free (str);

	return 0;
}

node *file_to_mem (node *tree)
{
	int length = 0;
	char *str = (char *)malloc (N * sizeof (char));

	while (((str[length] = fgetc (text)) != '?') && (str[length] != '.'))//retrieving the next phrase
		length++;
	length++;
	str[length] = 0;

	tree = node_ctor (tree, str); //adding the phrase to the tree

	if (str[length - 1] == '?')
	{
		fgetc (text); //next symbol is '[' so we need to jump over it
		tree->left = file_to_mem (tree->left);
		fgetc (text); //next symbol is ']' so we need to jump over it
		fgetc (text); //next symbol is '[' so we need to jump over it
		tree->right = file_to_mem (tree->right);
		fgetc (text); //next symbol is ']' so we need to jump over it
	}

	return tree;
}

void mem_to_file (node *tree)
{
	int length = strlen (tree->phrase);

	if (tree->phrase[length - 1] == '?')
	{
		fprintf(text, "%s[", tree->phrase);
		mem_to_file (tree->left);
		fprintf(text, "][");
		mem_to_file (tree->right);
		fprintf(text, "]");
	}
	else
		fprintf(text, "%s", tree->phrase);

	return;
}

node *game (node *tree)
{
	int phrase_length = strlen (tree->phrase);
	int answer_length = 0;
	int mistake = 0;

	char *str = (char *)malloc (N * sizeof (char));
	char *answer = (char *)malloc (N * sizeof (char));
	char *question = (char *)malloc (N * sizeof (char));
	char *temp = (char *)malloc (N * sizeof (char));

	if (tree->phrase[phrase_length - 1] == '?')
	{
		printf ("%s (Y/N)\n", tree->phrase);
		REPEAT

		if (str[0] == 'Y')
			tree->left = game (tree->left);
		else
			tree->right = game (tree->right);
	}
	else
	{
		printf ("You had riddled %s\nAm I right? (Y/N)", tree->phrase);
		REPEAT

		if (str[0] == 'N')
		{
			printf ("What/whom had you riddled?\n");
			REINPUT(answer, 0);

			answer_length = strlen (answer);
			answer[answer_length - 2] = 0;

			tree->phrase[phrase_length - 1] = 0; //tree->phrase contains '.' at the end
			
			printf ("What question can help me differ %s from %s?\n", answer, tree->phrase);
			REINPUT(question, 1)
			question[strlen(question) - 1] = 0;

			strcpy (temp, tree->phrase);
			strcpy (tree->phrase, question);
			printf("%s (about %s, Y/N)\n", tree->phrase, answer);
			REPEAT

			temp[phrase_length - 1] = '.';
			temp[phrase_length] = 0;

			answer[answer_length - 2] = '.';
			answer[answer_length - 1] = 0;

			if (str[0] == 'Y')
			{
				tree->left = node_ctor (tree->left, answer);
				tree->right = node_ctor (tree->right, temp);
			}
			else
			{
				tree->left = node_ctor (tree->left, temp);
				tree->right = node_ctor (tree->right, answer);
			}

			printf ("\nThank you, I will know.\n");
		}
		else
			printf ("\nI am the real Geanie!\n");
	}

	return tree;
}

int how_many (char *str, int mode)
{
	int i;
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;

	for (i = 0; str[i] != 0; i++)
	{
		if (str[i] == '?')
			count1++;
		if (str[i] == '.')
			count2++;
		if ((str[i] == '[') || (str[i] == ']'))
			count3++;
	}

	if (count3 != 0)
		return 1;

	if (mode == 0)
	{
		if ((count1 == 0) && (count2 == 1) && (str[i - 2] == '.'))
			return 0;
		else 
			return 1;
	}
	else if ((count1 == 1) && (count2 == 0) && (str[i - 2] == '?'))
			return 0;
		else
			return 1;
}

node *node_ctor (node *tree, char *str)
{
	assert (!tree);
	tree = (node *)malloc (sizeof (node));
	tree->right = NULL;
	tree->left = NULL;

	tree->phrase = (char *)malloc (N * sizeof (char));
	strcpy (tree->phrase, str);

	return tree;
}

void tree_destruct(node *tree)
{
	if (tree->left != NULL)
		tree_destruct (tree->left);
	if (tree->right != NULL)
		tree_destruct (tree->right);

	free (tree->phrase);
	free (tree);
}
