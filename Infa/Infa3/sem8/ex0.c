#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255 
#define N 8

int main()
{
  int msqid = 0;

  char pathname[] = "ex0.c"; 

  key_t key = 0; 

  int len = 0; 

  struct mymsgbuf
  {
    long mtype;
    int mtext;
  } mybuf;

  if ((key = ftok(pathname, 0)) < 0)
  {
    printf("Can't generate key\n");
    exit(-1);
  }

  if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
  {
    printf("Can't get msqid\n");
    exit(-1);
  }

  mybuf.mtype = 1;
  mybuf.mtext = N;
  len = sizeof (mybuf.mtext);

  if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0)
  {
    printf("Can't send message to the queue\n");
    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    exit(-1);
  }
  
  mybuf.mtype = LAST_MESSAGE;
  len = 0;

  if (msgsnd(msqid, (struct msgbuf*)&mybuf, len, 0) < 0)
  {
    printf("Can't send message to queue\n");
    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    exit(-1);
  }

  return 0;
}