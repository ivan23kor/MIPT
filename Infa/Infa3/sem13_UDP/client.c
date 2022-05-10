#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define TERMINAL_LENGTH 80
#define PORT 51000
#define MAX_LINE_LENGTH 100

int main(int argc, char const *argv[])
{
	int sockfd = 0;
	int child = 0;
	int clilen = 0;

	char sendline[MAX_LINE_LENGTH];
	char recvline[MAX_LINE_LENGTH];

	struct sockaddr_in cliaddr, servaddr;
//=======================================
	if (argc != 3)
    {
        printf("Usage: ./a.out <IP address> <Nickname>\n");
        exit(1);
    }

	if ((sockfd = socket (PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror (NULL);
        exit (1);
    }

	bzero (&cliaddr, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons (0);
	cliaddr.sin_addr.s_addr = htonl (INADDR_ANY);

	if (bind (sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) < 0)
	{
		perror (NULL);
		close (sockfd);
		exit (1);
	}

	bzero (&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons (PORT);

    if (inet_aton (argv[1], &servaddr.sin_addr) == 0)
    {
        printf ("Invalid IP address\n");
        close (sockfd);
        exit (1);
    }

   	child = fork ();
   	if (child)
   	{	
        while (1)
        {
        	clilen = sizeof (cliaddr);
            if (recvfrom (sockfd, recvline, MAX_LINE_LENGTH, 0, (struct sockaddr*)&servaddr, &clilen) < 0)
            {
                perror (NULL);
                close (sockfd);
                exit (1);
            }
            for (int i = 0; i < TERMINAL_LENGTH - strlen (recvline); ++i)
                printf(" ");
            printf ("%s", recvline);
        }
    }
    else
    {
    	if (sendto (sockfd, argv[2], strlen (argv[2]) + 1, 0, (struct sockaddr*)&servaddr, sizeof (cliaddr)) < 0)
        {
            perror (NULL);
            close (sockfd);
            exit (1);
        }
        while (1)
        {
            fgets (sendline, MAX_LINE_LENGTH, stdin);
            if (sendto (sockfd, sendline, MAX_LINE_LENGTH, 0, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
            {
                perror (NULL);
                close (sockfd);
                exit (1);
            }
    	}
    }

    close (sockfd);

	return 0;
}