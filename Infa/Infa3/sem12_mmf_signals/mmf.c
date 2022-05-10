#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define N 3

char name[] = "input.txt";

void read_write (int file_size, char * ptr);
void scanf_printf (int file_size, char * ptr);

int main(int argc, const char * argv[])
{
	int file_size = 0;

	char * ptr = NULL;

	FILE * input = NULL;
	input = fopen(name, "ra");

	if (input == NULL)
		return -1;
	while (fgetc(input) != EOF)
		file_size++;
	fclose(input);
	file_size *= sizeof(char);
	ptr = (char *)malloc (file_size);

	if (argv[1][0] == '1')
		read_write(file_size, ptr);
	else
		scanf_printf(file_size, ptr);
	printf("OK\n");

	printf("%s\n", ptr);

	return 0;
}

void read_write (int file_size, char * ptr)
{
	int fd = 0;
printf("OK\n");
	char * tmp_ptr = (char *)malloc (sizeof (ptr));
printf("OK\n");
	fd = open(name, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
	{
		printf("File open failed!\n");
		exit(1);
	}
	ptr = (char *)mmap(NULL, file_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
	close(fd);
	if (ptr == MAP_FAILED)
	{
		printf("Mapping failed!\n");
		exit(2);
	}
printf("OK\n");
	tmp_ptr = ptr;
	file_size /= sizeof(char);
	for (int i = 0; i < file_size; ++i)
		ptr[i] += N;
printf("OK\n");
	munmap((void *)tmp_ptr, file_size);
}

void scanf_printf (int file_size, char * ptr)
{

}