#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

const int ProcessCount = 2;
const int Delay = 2; //secs

int main()
{
    int i;

    for (i = 0 ; i < ProcessCount ; ++i) {
            pid_t pid = fork();

            if (pid == 0) {
                sleep(Delay * (i + 1));
                printf("Execute %d\n" , i);
                exit(0);
            } 
    }
    return 0;
}
