#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
   
   if(strcmp(argv[1],"-e") == 0) { //옵션이 -e 일 때 
      if(argc == 3) { //매개인자 값이 존재할 때
         char *ptr = getenv(argv[2]);
         
         if(ptr) {
            printf("%s = %s \n", argv[2], ptr);
         } else { 
            printf("wrong argument \n"); //매개인자 값이 잘못 입력했을 때
         }
      } else {
         //매개인자 값 미입력시 전체출력
         char **ptr;
         extern char **environ;
      
         for(ptr = environ; *ptr != 0; ptr++) {
            printf("%s \n", *ptr);
         }
      }
   }
   else if (strcmp(argv[1],"-u") == 0) { //옵션이 -u 일 때
      printf("My Realistic User ID : %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
      printf("My Valid User ID : %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);  
   }
   else if (strcmp(argv[1],"-g") == 0) { //옵션이 -g 일 때
      printf("My Realistic Group ID : %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
      printf("My Valid Group ID : %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
   }
   else if (strcmp(argv[1],"-i") == 0) { //옵션이 -i 일 때
      printf("My Process Number : [%d] \n", getpid());
   }
   else if (strcmp(argv[1],"-p") == 0) { //옵션이 -p 일 때
      printf("My Parent's Process Number : [%d] \n", getppid());
   }

   exit(1);
}
