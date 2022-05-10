#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

const int ProcessCount = 3;

int main()
{
    int i;

    for (i = 0 ; i < ProcessCount ; ++i) {
            pid_t pid = fork();

            if (pid == 0) {
                printf("Execute %d\n" , i);
                exit(0);
            } 
    }
    return 0;
}
