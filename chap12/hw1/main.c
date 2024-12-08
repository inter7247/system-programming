#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXLINE 100

int main(int argc, char* argv[]) {
   int r, fd[2], length;
   char message[MAXLINE], line[MAXLINE];
   
   pipe(fd);

   pid_t pid = fork();

   if (pid == 0) {
      close(fd[0]);
      sprintf(message,"%d", getpid());
      length = strlen(message) + 1;
      write(fd[1], message, length);
   } else {
      close(fd[1]);
      r = read(fd[0], line, MAXLINE);
      printf("Send: [%s] Hello from PID %s\n", line, line);
      printf("Recv: [%d] Hello from PID %s\n", getpid(), line);
   }
   exit(0);
}

