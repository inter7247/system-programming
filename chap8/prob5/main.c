#include <stdio.h>
#include <unistd.h>

/* 프로세스 번호를 출력한다. */
int main() {    
   printf("my process number: [%d] \n", getpid());
   printf("my parent process number: [%d] \n", getppid());
}
