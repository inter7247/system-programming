#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
/* 세 개의 자식 프로세스를 생성하여 각 각 다른 명령어를 실행한다. */
int main( ) {
   printf("parental process start\n");
   if (fork( ) == 0) {
      execl("/bin/echo", "echo", "hello", NULL);
      fprintf(stderr,"첫 번째 실패");
      exit(1);
   }
   if (fork( ) == 0) {
      execl("/bin/date", "date", NULL);
      fprintf(stderr,"두 번째 실패");
      exit(2);
   }
   if (fork( ) == 0) {
      execl("/bin/ls","ls", "-l", NULL);
      fprintf(stderr,"세 번째 실패");
      exit(3);
   }
   wait(NULL);
   printf("parental process end\n");
}
