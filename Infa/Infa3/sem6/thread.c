#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int a = 0;

void* my_thread(void* dummy) {
    pthread_t my_thread_id; 
    sleep(1);

/*
    Переменная my_thread_id является динамической локальной переменной
    функции my_thread(), т.е. помещается на стеке и, следовательно, не
    разделяется нитями исполнения.
*/

    my_thread_id = pthread_self();
    a += 1;
    printf("Thread %u, result = %d\n" , (unsigned int)my_thread_id , a);
    
    return NULL;
}

int main()
{
    pthread_t thread_id = 0;
    pthread_t thread_id2 = 0;
    pthread_t my_thread_id = 0;
    
    int result = 0;
    int result2 = 0;
    /* 
        Пытаемся создать новую нить исполнения, ассоциированную
        с функцией my_thread(). Передаем ей в качестве параметра
        значение NULL. В случае удачи в переменную thread_id занесется
        id нового thread`a.
        В случае ошибки перекращаем работу.
    */
    
    result = pthread_create(&thread_id , 
                            (pthread_attr_t *)NULL , 
                            my_thread ,
                            NULL);

    if (result) {
        printf("Can`t create thread, returned value = %d\n" , result);
        exit(-1);
    }

    printf("Thread was created, thread id = %u\n" , (unsigned int)thread_id);

    result2 = pthread_create(&thread_id2 , 
                            (pthread_attr_t *)NULL , 
                            my_thread ,
                            NULL);

    if (result2) {
        printf("Can`t create thread, returned value = %d\n" , result2);
        exit(-1);
    }

    printf("Thread was created, thread id = %u\n" , (unsigned int)thread_id2);

    my_thread_id = pthread_self();
    a += 1;
    printf("Main thread %u, result = %d\n" , (unsigned int)my_thread_id , a);

    /*
        Ожидаем завершение порожденного thread`a, не интересуясь, какое значение он
        вернет. Если не выполнить вызов этой функции, то возможно ситуация, когда
        мы завершим функцию main() до того, как выполнится порожденный thread, что
        автоматически повлечет за собой его завершение, исказив результаты
    */

    pthread_join(thread_id , (void **) NULL);
    pthread_join(thread_id2 , (void **) NULL);

    return 0;
}