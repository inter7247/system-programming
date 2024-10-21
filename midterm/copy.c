#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/* 파일 복사 프로그램 */
int main(int argc, char *argv[])
{
   int fd1, fd2, n;
   char buf[BUFSIZ];
   if (argc != 4) {
      fprintf(stderr, "How to use: %s option file1 file2\n", argv[0]);
      exit(1);
   }

   if(strcmp(argv[1], "0") == 0) { //옵션이 0일떄
      if ((fd1 = open(argv[2], O_RDONLY)) == -1) { //복사할 파일은 r읽기로
         perror(argv[1]);
         exit(2);
      }

      if ((fd2 =open(argv[3], O_WRONLY | O_CREAT|O_TRUNC, 0600)) == -1) {
         perror(argv[2]);
         exit(3);
      }
      while ((n = read(fd1, buf, BUFSIZ)) > 0)
         write(fd2, buf, n);
      exit(0);
   } else if(strcmp(argv[1], "1") == 0) {
      if ((fd1 = open(argv[2], O_RDONLY)) == -1) { //복사할 파일은 r읽기로
         perror(argv[2]);
         exit(2);
      }

      if ((fd2 =open(argv[3], O_WRONLY | O_CREAT|O_TRUNC, 0600)) == -1) {
         perror(argv[3]);
         exit(3);
      }

      while ((n = read(fd1, buf, BUFSIZ)) > 0)
         write(fd2, buf, n);
      
      c = getc(fd2);
      

      exit(0);
   } 
}
