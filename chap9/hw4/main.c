#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LENGTH 100

int main() {
   char cmd[MAX_LENGTH];
   char *args;
   int child;

   while(1) {
      printf("[shell] Plz input cmd : ");

      //명령어 입력 받기
      if(fgets(cmd, MAX_LENGTH, stdin) == NULL) {
         printf("Wrong Command");
         break;
      }

      // 개행문자 제거
      if(strlen(cmd) > 0 && cmd[strlen(cmd) - 1] == '\n'){
         cmd[strlen(cmd) - 1] = '\0';
      }

      // 나가기 실행
      if(strcmp(cmd, "exit") == 0) {
         break;
      }

      char *token = strtok_r(cmd, ";", &args); // token 단위로 구분
      while(token != NULL) {
         printf("[%d] Parent Process start \n", getpid());
         // token 중에 백그라운드 실행 &이 있을 경우
         if(strchr(token, '&') != NULL) {
            pid_t pid = fork(); // 프로세스 생성
            
            if(pid == 0) { // 자식 프로세스 실행
               printf("[%d] Child Process start \n", getpid());
               char *args[] = {"/bin/sh", "-c", token, NULL};
               execvp(args[0], args);
               exit(EXIT_FAILURE);
            }
            if(pid == -1) { // 실패시 -1 리턴
               exit(EXIT_FAILURE);
            }
         } else {
            pid_t pid = fork();
            if(pid == 0) { // 자식 프로세스 실행
               printf("[%d] Child Process start \n", getpid());
               char *args[] = {"/bin/sh", "-c", token, NULL};
               execvp(args[0], args);
               perror("error");
               exit(EXIT_FAILURE);
            }
            if(pid == -1) { // 실패시 -1 리턴
               exit(EXIT_FAILURE);
            } else {
               int status;
               child = waitpid(pid, &status, 0);
               if (WIFEXITED(status) && WEXITSTATUS(status) == 0) { //자식 프로그램 종료확인 명령어
                  printf("[%d] child process end %d \n", getpid(), child);
                  printf("Success\n");
                  printf("\n");
               } else { //잘못 입력시 종료
                  printf("Parent Process end \n");
                  printf("Exit\n");
                  exit(EXIT_FAILURE);
               }
            }
         }
         token = strtok_r(NULL, ";", &args);
      }
   }
}
