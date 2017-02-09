//IPC_msgq_rcv.c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE  128
void die(char *s)
{
  perror(s);
  exit(1);
}



typedef struct msgbuf
{
    long    mtype;
    char    mtext[MAXSIZE];
};


int main()
{
    int msqid;
    key_t key;
          size_t buflen;

    struct msgbuf rcvbuffer,sbuf;
   key = 1234;
   if ((msqid = msgget(key, 0666)) < 0)
      die("msgget()");
     //Rece ive an answer of message type 1.
   do{
    if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 1, 0) < 0)
      die("msgrcv");
    printf("%s\n", rcvbuffer.mtext);
    
     sbuf.mtype = 1;
      printf("Enter a message to send it to server(sender) : ");
      scanf("%[^\n]",sbuf.mtext);
      getchar();
      buflen = strlen(sbuf.mtext) + 1 ;
      if ( msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
      {
          printf("couldnot send msg\n");
          printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buflen);
          die("msgsnd");
      }else{

      }

    }while(strcmp(sbuf.mtext,"stop")!=0);
    exit(0);
} 
