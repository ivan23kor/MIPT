#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255 
#define N 5

int main()
{
  int msqid = 0;
  int maxlen = 0;
  int len = 0;
  long long factorial = 1;

  char pathname[] = "ex0.c"; 

  key_t key = 0;

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

  while (1)
  {
    maxlen = sizeof (mybuf.mtext);

    if ((len = msgrcv(msqid, (struct msgbuf *)&mybuf, maxlen, 0, 0)) < 0)
    {
      printf("Can\'t receive message from queue\n");
      msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
      exit(-1);
    }

    if (mybuf.mtype == LAST_MESSAGE)
    {
      msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
      exit(0);
    }

    factorial = 1;
    for (int i = 1; i <= mybuf.mtext; ++i)
      factorial *= i;
    printf("message type = %ld, info = %lld\n", mybuf.mtype, factorial);
  }
  
  return 0;
}