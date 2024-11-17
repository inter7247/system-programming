#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LENGTH 100

int main() {
   char cmd[MAX_LENGTH];
   int child;
 
   while(1) {
      printf("[shell] ");
      
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
      
      // 명령어 순차적 실행
      char *token = strtok(cmd, ";"); // token 단위로 구분 
      while(token != NULL) {
         
         // token 중에 백그라운드 실행 &이 있을 경우
         if(strchr(token, '&') != NULL) {
            pid_t pid = fork(); // 프로세스 생성

            if(pid == 0) { // 자식 프로세스 실행
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
               char *args[] = {"/bin/sh", "-c", token, NULL};
               execvp(args[0], args);
               exit(EXIT_FAILURE);
            }
            if(pid == -1) { // 실패시 -1 리턴
               exit(EXIT_FAILURE);
            } else {
               int status;
               child = waitpid(pid, &status, 0);
            }
         }
         token = strtok(NULL, ";");
      }      
   }   
}
