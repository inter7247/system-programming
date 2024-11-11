#include <stdio.h>
#include <unistd.h>
/* 자식 프로세스를 생성한다. */
int main() { 
   int pid;
   printf("[%d] Process start \n", getpid());
   pid = fork();
   printf("[%d] Process : return value %d\n", getpid(), pid); 
}
