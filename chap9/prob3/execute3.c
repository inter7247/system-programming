#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* 명령줄 인수로 받은 명령을 실행시킨다. */
int main(int argc, char *argv[]) { 
   int child, pid, status;
   pid = fork( );
   if (pid == 0) { // 자식 프로세스
      execvp(argv[1], &argv[1]);
      fprintf(stderr, "%s:실행 불가\n",argv[1]);
   } else { // 부모 프로세스
      child = wait(&status);
      printf("[%d] child process %d end \n", getpid(), pid);
      printf("\tend code %d \n", status>>8);
   }
}
