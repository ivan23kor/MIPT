#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	const char dir_name[] = "../../";

	struct dirent info[1];
	struct stat buffer[1];

	DIR * dir_pointer = NULL;
//====================================
	dir_pointer = opendir (dir_name);

	while ((info = readdir (dir_pointer)) != NULL)
	{
		stat (info->d_name, buffer);
		if ((buffer->st_mode & S_IFMT) == S_IFREG)
			printf("Regular file: %s, size = %d bytes.\n", info->d_name, (int)buffer->st_size);
		if ((buffer->st_mode & S_IFMT) == S_IFDIR)
			printf("Directory: %s, size = %d bytes.\n", info->d_name, (int)buffer->st_size);
	}

	closedir (dir_pointer);

	return 0;
}