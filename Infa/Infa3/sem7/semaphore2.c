#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int semid = 0;

    char what[] = "qwerty";
    const char filename[] = "semaphore.txt";

    key_t key;

    struct sembuf mybuf;

    FILE * file = fopen ("file.txt", "arw");

    if ((key = ftok (filename , 0)) < 0) {
        printf("Can`t generate key\n");
        exit(-1);
    }

    if ((semid = semget(key , 1 , 0666 | IPC_CREAT)) < 0) {
        printf("Can`t get semid\n");
        exit(-1);
    }

    while (1)
    {
        mybuf.sem_op = -1;
        mybuf.sem_flg = 0;
        mybuf.sem_num = 0;

        if (semop (semid , &mybuf , 1) < 0)
        {
            printf("Can`t wait for condition\n");
            exit(-1);
        }

        fprintf(file, "%s ", what);

        mybuf.sem_op = 1;
        mybuf.sem_flg = 0;
        mybuf.sem_num = 0;

        if (semop (semid , &mybuf , 1) < 0)
        {
            printf("Can`t wait for condition\n");
            exit(-1);
        }        
    }

    fclose (file);
    
    return 0;
}

/*
    Удаление семафора:
    ipcs
    ipcrm sem <ipc id>    
*/