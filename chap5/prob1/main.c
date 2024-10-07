#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
   int fd;

   if ((fd = open("test.txt", O_RDWR)) == -1) {
      printf("File Open Error\n");
   } else { 
      printf("file %s Open Sucess : %d\n", "test.txt", fd);
   }

   close(fd);
   exit(0);
}
