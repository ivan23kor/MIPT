/* Программа s08e01a.c для иллюстрации работы с семофорами */

/* Программа получает доступ к одному системному семофору.
   Ждет, пока его значение не станет больше или равным 1
   после запусков программы s08e01b.c, а затем уменьшает его
   на 1 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int semid; /* IPC-дескриптор для массива IPC семафоров */

    const char pathname[] = "s08e01a.c"; /* Имя файла, использующееся для генерации ключа.
    Файл с таким именем должен существовать в текущей директории*/

    key_t key; /* IPC ключ */

    struct sembuf mybuf; /* Структура для задания операции над семафором */

    if ( (key = ftok(pathname , 0)) < 0 ) {
        printf("Can`t generate key\n");
        exit(-1);
    }

    /* Пытаемся получить доступ по ключу к массиву семафоров, если он существует,
       или создать его из одного семафора, если его ещё не существует, с правами
       доступа rw для всех пользователей */

    if ((semid = semget(key , 1 , 0666 | IPC_CREAT)) < 0) {
        printf("Can`t get semid\n");
        exit(-1);
    }

    /* Выполним операцию D(semid , 1) для нашего массива семафоров. Для этого
    сначала заполним структуру mybuf */

    mybuf.sem_op = -1;
    mybuf.sem_flg = 0;
    mybuf.sem_num = 0;

    if (semop(semid , &mybuf , 1) < 0) {
        printf("Can`t wait for condition\n");
        exit(-1);
    }

    printf("Condition is present\n");
    return 0;
}

/*
    Удаление семафора:
    ipcs
    ipcrm sem <ipc id>    
*/

