#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <string.h>
#define MAXLINE 100

int main(int argc, char* argv[]){
   int r, fd[2];
   char message[MAXLINE], line[MAXLINE];

   printf("parent process start\n");

   pipe(fd);

   pid_t pid1;
   if((pid1 = fork()) == 0) {
      close(fd[0]);
      printf("input string: ");
      fgets(message, MAXLINE, stdin);
      write(fd[1], message, strlen(message) + 1);
      close(fd[1]);
   }
   wait(NULL);
   
   pid_t pid2;
   if((pid2 = fork()) == 0) {
      close(fd[1]);
      read(fd[0], line, MAXLINE);
      for(int i = 0; line[i] != '\0'; i++) {
         if(islower(line[i])) {
            line[i] = toupper(line[i]);
         } else if (isupper(line[i])) {
            line[i] = tolower(line[i]);
         }
      }
      printf("%s", line);
   }
   exit(0);
}
