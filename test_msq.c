#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

key_t key;
int msq_id;

pthread_t tid1,tid2;
int a;
int b;

void *th_func1(void *arg)
{
  while(1)
    {
      struct msgbuf {
	long mtype;       /* message type, must be > 0 */
	char mtext[100];    /* message data */
      }msg;

      static int dat;
      dat +=2;

      msg.mtype = 1;
      memcpy(&msg.mtext[0],&dat,sizeof(dat));

      msgsnd(msq_id, &msg, sizeof(msg), 0);
    
      sleep(1);
   

    }
}
void *th_func2(void *arg)
{
  int a;
  int b;
    
  struct msgbuf {
    long mtype;       /* message type, must be > 0 */
    char mtext[100];    /* message data */
  }msg;
  int dat;
  
  while (1) {
    int ret;
    ret = msgrcv(msq_id, &msg, sizeof(msg), 1, 0);
    if (ret >= 0) {
      printf("msgtype:%ld, dat:%d\n", msg.mtype, *((int *)msg.mtext));
    }
  }
}

void main(int argc, char **argv)
{
  key = ftok("./", 'a');
  key = key;
  msq_id = msgget(key, IPC_CREAT|S_IRUSR|S_IWUSR);
  pthread_create(&tid1, NULL, th_func1, NULL);
  pthread_create(&tid2, NULL, th_func2, NULL);
  //pthread_create();

  while (1) {
    printf("===========\n");
    printf("\033[41;36mPumpKing\033[0m\n");
    sleep(1);
  }

  return;
}


