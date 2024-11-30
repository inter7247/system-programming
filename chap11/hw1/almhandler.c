#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void alarmHandler(int signum);
void new_signal(int signum, void (*handler)(int));

struct sigaction newact;
struct sigaction oldact;

int main() {
   new_signal(SIGALRM, alarmHandler);
   alarm(5);

   short i = 0;

   while (1) {
      sleep(1);
      i++;
      printf("%d second\n", i);
   }

   printf("end\n");
   return 0;
}

void alarmHandler(int signum) {
   printf("Wake up\n");
   exit(0);
}

void new_signal(int signum, void (*handler)(int)) {
   newact.sa_handler = handler;
   sigemptyset(&newact.sa_mask);
   sigaction(signum, &newact, &oldact);
}
