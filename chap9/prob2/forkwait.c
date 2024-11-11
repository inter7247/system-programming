#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/* 부모 프로세스가 자식 프로세스를 생성하고 끝나기를 기다린다. */ 
int main() {
   int pid, child, status;
   printf("[%d] partenal process start \n", getpid( ));
   pid = fork();
   if (pid == 0) {
      printf("[%d] child process start \n", getpid( ));
      exit(1);
   }
  
   child = wait(&status); // 자식 프로세스가 끝나기를 기다린다. 
   printf("[%d] child process %d end \n", getpid(), child);
   printf("\t end code %d\n", status>>8);
} 
