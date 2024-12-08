#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]){
   int fd[2];
   char str[1024];
   char *command1, *command2;
   printf("[shell]");
   fgets(str, sizeof(str), stdin);
   str[strlen(str)-1] = '\0';
   if(strchr(str,'|') != NULL) {
      command1 = strtok(str,"| ");
      command2 = strtok(NULL,"| ");
   }
   pipe(fd);

   pid_t pid;
   if((pid = fork()) == 0) {
      close(fd[0]);
      dup2(fd[1],1);
      close(fd[1]);
      execlp(command1, command1, NULL);
   } else {
      close(fd[1]);
      dup2(fd[0],0);
      close(fd[0]);
      execlp(command2, command2, NULL);
   }
   exit(0);
}
