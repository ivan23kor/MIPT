#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 51000
#define NICK_LENGTH 20
#define MAX_CLIENTS 50
#define MAX_LINE_LENGTH 100
#define SPLIT_COUNT 2

typedef struct user_t
{
    struct sockaddr_in cliaddr;
    char nickname[NICK_LENGTH];
} user;

int split (char * string, char * delim, char *** tokens);

int main()
{
    int i = 0;
    int found = 0;
    int base_index = 0;
    int sockfd;
    int client_count = 0;
    int clilen = 0;
    int split_count = 0;

    char delim[] = "@";
    char recvline[MAX_LINE_LENGTH];
    char sendline[MAX_LINE_LENGTH];
    char ** tokens = (char **)malloc (SPLIT_COUNT * sizeof (char *));
    for (int j = 0; j < SPLIT_COUNT; ++j)
        tokens[j] = (char *)malloc (MAX_LINE_LENGTH * sizeof (char));

    user user_base[MAX_CLIENTS];

    struct sockaddr_in servaddr, cliaddr;
    bzero (&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons (PORT);
    servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
//================================================
    if ((sockfd = socket (PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror (NULL);
        exit (1);
    }

    if (bind (sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror (NULL);
        close (sockfd);
        exit (1);
    }

    while (1)
    {
        clilen = sizeof (cliaddr);
        if (recvfrom (sockfd, recvline, MAX_LINE_LENGTH, 0, (struct sockaddr*)&cliaddr, &clilen) < 0)
        {
            perror (NULL);
            close (sockfd);
            exit (1);
        }

        for (i = 0; i < base_index; i++)
            if ((cliaddr.sin_addr.s_addr == user_base[i].cliaddr.sin_addr.s_addr) && 
                (cliaddr.sin_port == user_base[i].cliaddr.sin_port))
            {
                found = i;
                break;
            }

        if (base_index == i)
        {
            bzero ((struct sockaddr*)&(user_base[base_index].cliaddr), sizeof(user_base[base_index].cliaddr));
            user_base[base_index].cliaddr.sin_family = AF_INET;
            user_base[base_index].cliaddr.sin_addr.s_addr = cliaddr.sin_addr.s_addr;
            user_base[base_index].cliaddr.sin_port = cliaddr.sin_port;
            strcpy (user_base[base_index].nickname, recvline);
            found = base_index;
            base_index++;
        }
        else
        {
            split_count = split (recvline, delim, &tokens);
            if (split_count == 2)
            {
                for (i = 0; i < base_index; ++i)
                {
                    if ((strcmp (tokens[0], user_base[i].nickname) == 0) && (i != found))
                    {
                        if (sendto (sockfd, tokens[1], strlen (tokens[1]) + 1, 0, (struct sockaddr*)&user_base[i].cliaddr,
                        sizeof (cliaddr)) < 0)
                        {
                            perror (NULL);
                            close (sockfd);
                            exit (1);
                        }
                        printf("Private message from %s to %s: %s", user_base[found].nickname, tokens[0], tokens[1]);
                        break;
                    }
                }
            }
            else if (split_count == 1)
            {
                for (i = 0; i < base_index; i++)
                    if (i != found)
                        if (sendto (sockfd, recvline, strlen (recvline) + 1, 0, (struct sockaddr*)&user_base[i].cliaddr,
                        sizeof (cliaddr)) < 0)
                        {
                            perror (NULL);
                            close (sockfd);
                            exit (1);
                        }
                printf("Message for everybody from %s: %s", user_base[found].nickname, recvline);
            }
            else
                printf("Usage: <nickname@(for private)><message>\n");
        }
    }

    close (sockfd);

    return 0;
}

int split (char * string, char * delim, char *** tokens)
{
    int i = 0;

    char * temp = NULL;

    temp = strtok (string, delim);
    if (temp)
        strcpy ((*tokens)[i], temp);

    while (temp)
    {
        i++;
        temp = strtok (NULL, delim);
        if (temp)
            strcpy ((*tokens)[i], temp);
    }

    return i;
}