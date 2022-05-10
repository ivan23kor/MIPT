#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define MAX_MSG 1000
#define MSG_COUNT 20
#define PORT 51002

void main(int argc, char **argv)
{
    int child = 0;
    int sockfd; /* Дескриптор сокета */
    int n; /* Количество переданных или прочитанных 
        символов */
    int i; /* Счетчик цикла */
    char sendline[MAX_MSG],recvline[MAX_MSG]; /* Массивы 
        для отсылаемой и принятой строки */
    struct sockaddr_in servaddr; /* Структура для 
        адреса сервера */
    /* Сначала проверяем наличие второго аргумента в
    командной строке. При его отсутствии прекращаем 
    работу */
    if(argc != 2){
        printf("IP address was forgotten!\n");
        exit(1);
    }
    /* Обнуляем символьные массивы */
    bzero(sendline, MAX_MSG);
    bzero(recvline, MAX_MSG);
    /* Создаем TCP сокет */
    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        perror(NULL); /* Печатаем сообщение об ошибке */
        exit(1);
    }
    /* Заполняем структуру для адреса сервера: семейство 
    протоколов TCP/IP, сетевой интерфейс – из аргумента 
    командной строки, номер порта 7. Поскольку в структуре
    содержится дополнительное не нужное нам поле, 
    которое должно быть нулевым, перед заполнением обнуляем 
    ее всю */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if(inet_aton(argv[1], &servaddr.sin_addr) == 0){
        printf("Invalid IP address\n");
        close(sockfd);
        exit(1);
    }
    /* Устанавливаем логическое соединение через 
созданный сокет с сокетом сервера, адрес которого мы занесли
в структуру */
    if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    child = fork ();
    if (child)
    {
        for(i = 0; i < MSG_COUNT; i++){
        printf("String => ");
        fflush(stdin);
        fgets(sendline, MAX_MSG, stdin);
        if((n = write(sockfd, sendline, strlen(sendline) + 1)) < 0)
        {
            perror("Can\'t write\n");
            close(sockfd);
            exit(1);
        }
        }
    }
    else
    {
        for(i = 0; i < MSG_COUNT; i++){
            if ((n = read(sockfd,recvline, MAX_MSG - 1)) < 0)
            {
                perror("Can\'t read\n");
                close(sockfd);
                exit(1);
            }

        printf("%s", recvline);
        }
    }
    close(sockfd);
}