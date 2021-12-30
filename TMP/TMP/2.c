#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

int pid1, pid2, pid3, pid4;

void SigHndlr () /* ���������� ������� */
  {
  waitpid (pid1, NULL, 0);
  waitpid (pid2, NULL, 0);
  waitpid (pid3, NULL, 0);
  waitpid (pid4, NULL, 0);
  }



struct
  {
  long mtype; /* ��� ��������� */
  char msg_number; /* ��������� */
  } Message;

int main(int argc, char **argv)
  {
  key_t key;
  //int msgid;
  key = ftok("./f",'s');
      printf( "%d", key);
  /*�������� ���������� ����, ���������� ������������
  ������ � ������� */
      int msgid = msgget (key, 0666 | IPC_CREAT | IPC_EXCL );
      printf("\n");
      printf("FGFG: %d", msgid);
  /*������� ������� ��������� , 0666 ���������� ����� ������� */


  if ((pid1 = fork ()) == 0)
    {//������ �������
    Message.mtype = 'a';
    Message.msg_number = 0;

    msgsnd(msgid, (struct msgbuf*)(&Message), 1, 0);

    for (;;)
      { //����� �������� b
      if (msgrcv(msgid, (struct msgbuf*) (&Message), 1, 'b', 0)  > 0)
        {
        printf ("1 process received %d \n", Message.msg_number);

        Message.mtype = 'a';
        Message.msg_number++;
        msgsnd(msgid, (struct msgbuf*)(&Message), 1, 0);

        printf ("1 process %d \n", Message.msg_number);
        sleep (1);
        }
      }
    }

  if ((pid2 = fork ()) == 0)
    {//������ �������
    for (;;)
      { //����� �������� b
      if (msgrcv(msgid, (struct msgbuf*) (&Message), 1, 'b', 0)  > 0)
        {
        printf ("2 process received %d \n", Message.msg_number);

        Message.mtype = 'a';
        Message.msg_number++;
        msgsnd(msgid, (struct msgbuf*)(&Message), 1, 0);

        printf ("2 process %d \n", Message.msg_number);
        sleep (1);
        }
      }

    }

  if ((pid3 = fork ()) == 0)
    {//������ �������
    for (;;)
      { //����� �������� b
      if (msgrcv(msgid, (struct msgbuf*) (&Message), 1, 'a', 0) > 0)
        {
        printf ("3 process received %d \n", Message.msg_number);

        Message.mtype = 'b';
        Message.msg_number++;
        msgsnd(msgid, (struct msgbuf*)(&Message), 1, 0);

        printf ("3 process %d \n", Message.msg_number);
        sleep (1);
        }
      }
    }

  if ((pid4 = fork ()) == 0)
    {//��������� �������
    for (;;)
      { //����� �������� b
      if (msgrcv(msgid, (struct msgbuf*) (&Message), 1, 'a', 0)  > 0 )
        {
        printf ("4 process received %d \n", Message.msg_number);

        Message.mtype = 'b';
        Message.msg_number++;
        msgsnd(msgid, (struct msgbuf*)(&Message), 1, 0);

        printf ("4 process sent %d \n", Message.msg_number);
        sleep (1);
        }
      }
    }

signal (SIGINT, SigHndlr);

//msgctl(msgid, IPC_RMID, NULL);
}

