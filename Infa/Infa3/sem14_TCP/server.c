#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

#define LINE_DEPTH 5
#define MAX_MSG 1000
#define CONNECT_COUNT 100
#define PORT 51002

void * routine (void * arg);

int sockfd = 0;
int newsockfd[CONNECT_COUNT];
int n = 0; //receive count
int i = 0; //index of connections to clients

char line[1000]; /* Буфер для приема информации */

void main()
{
    int result = 0;
    int index[CONNECT_COUNT];
    int clilen; /* Длина адреса клиента */

    struct sockaddr_in servaddr, cliaddr;

    pthread_t thread_id[CONNECT_COUNT];
    /* Создаем TCP-сокет */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror(NULL);
        exit(1);
    }
    /* Заполняем структуру для адреса сервера: семейство
    протоколов TCP/IP, сетевой интерфейс – любой, номер 
    порта 51000. Поскольку в структуре содержится 
    дополнительное не нужное нам поле, которое должно 
    быть нулевым, побнуляем ее всю перед заполнением */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family= AF_INET;
    servaddr.sin_port= htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /* Настраиваем адрес сокета */
    if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    /* Переводим созданный сокет в пассивное (слушающее) 
    состояние. Глубину очереди для установленных 
    соединений описываем значением 5 */
    if(listen(sockfd, LINE_DEPTH) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    while (1)
    {
        clilen = sizeof (cliaddr);
        if((newsockfd[i] = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) < 0)
        {
            perror(NULL);
            printf("ERROR!\n");
            close(sockfd);
            exit(1);
        }
        else
        {
            index[i] = i;
            result = pthread_create (&thread_id[i], (pthread_attr_t *)NULL, routine, &index[i]);
            if (result)
            {
                printf("Couldn't create thread. result = %d\n", result);
                exit (-1);
            }
            i++;
        }
    }
}

void * routine (void * arg)
{
    /* В цикле принимаем информацию от клиента до
    тех пор, пока не произойдет ошибки (вызов read()
    вернет отрицательное значение) или клиент не
    закроет соединение (вызов read() вернет 
    значение 0). Максимальную длину одной порции 
    данных от клиента ограничим 999 символами. В
    операциях чтения и записи пользуемся дескриптором
    присоединенного сокета, т. е. значением, которое
    вернул вызов accept().*/
    while((n = read(newsockfd[*(int *)arg], line, MAX_MSG)) > 0)
    {
        for (int k = 0; k < i; ++k)
        {
            if (k != *(int *)arg)
            {
                if((n = write(newsockfd[k], line, strlen (line) + 1)) < 0)
                {
                    perror(NULL);
                    close(sockfd);
                    close(newsockfd[k]);
                    exit(1);
                }
            }
        }
    }
/* Если при чтении возникла ошибка – завершаем работу */
    if(n < 0)
    {
        perror(NULL);
        close(sockfd);
        close(newsockfd[*(int *)arg]);
        exit(1);
    }
    close(newsockfd[*(int *)arg]);
    if (i > 0)
        i--;
    else
        printf("i = 0!\n");

    return NULL;
}