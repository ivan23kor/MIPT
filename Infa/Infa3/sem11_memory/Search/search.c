#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define N 1000

void search (char * filename, int depth, char * dirname);

int main(int argc, char const *argv[])
{
	int depth = 0;

	char dirname[N];
	char filename[N];
//====================================
	if (argc != 4)
	{
		printf("Input correct arguments!\n<filename> <depth> <dir>\n");
		return -1;
	}
	strcpy (filename, argv[1]);
	depth = atoi (argv[2]);
	if ((depth == 0) && (argv[2][0] != '0'))
	{
		printf("Input correct search depth!\n");
		return -1;
	}
	strcpy (dirname, argv[3]);

	search (filename, depth, dirname);

	return 0;
}

void search (char * filename, int depth, char * dirname)
{
	char dir[N];
	char tmp[N];
  /* Мне кажется, что в случае . и .. отдельные константы заводить не обязательно, т.к. смысл этих контант итак хорошо известен,
   * а названия one_dot и two_dots никакой дополнительной информации не несут.
   */
	char one_dot[] = ".";
	char two_dots[] = "..";

	struct dirent * info = NULL;// = (struct dirent *)malloc (sizeof (struct dirent));
	struct stat buffer;

	DIR * dir_pointer = opendir (dirname);

	if (depth == 0)
		return;

	while ((info = readdir (dir_pointer)) != NULL)
	{
		strcpy (tmp, dirname);
		strcat (tmp, "/");
		strcat (tmp, info->d_name);
		stat (tmp, &buffer);

		if (((buffer.st_mode & S_IFMT) == S_IFREG) && (strcmp (filename, info->d_name) == 0))
			printf("File %s was found in %s\n", filename, tmp);

		if (((buffer.st_mode & S_IFMT) == S_IFDIR) && (strcmp (one_dot, info->d_name) != 0)
												 && (strcmp (two_dots, info->d_name) != 0))
			search (filename, depth - 1, tmp);
	}
}
