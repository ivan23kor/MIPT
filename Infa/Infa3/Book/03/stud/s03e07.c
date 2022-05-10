#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    const int ProcessCount = 2;
    const int Delay = 2; //secs

    int i;
    int child_process_count = 0;
    int process_ids[ProcessCount];
    
    for (i = 0 ; i < ProcessCount ; ++i) {
        pid_t pid = fork();

        if (pid == 0) {
           // sleep(Delay * (i + 1));
            printf("Execute %d\n" , i);
            exit(0);
        } else if (pid > 0) {
            process_ids[child_process_count] = pid;
            ++child_process_count;
        }
    }
    
    for (i = 0 ; i < child_process_count ; ++i) {
        int status;
        waitpid(process_ids[i] , &status , 0);
        printf("Child process with pid=%d finished. Status:%d\n" , 
                                        process_ids[i] , 
                                        status);
    }
    
    printf("Parent process finished\n");    
    return 0;
}
