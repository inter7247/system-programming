#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MAXLINE 100

/* 이름 있는 파이프를 통해 읽은 내용을 프린트한다. */
int readLine(int fd, char *str);

int main() {
   int fd;
   char str[MAXLINE];
   unlink("myPipe"); // 기존 파이프 제거
   mkfifo("myPipe", 0660); // 새로운 파이프 생성
   fd = open("myPipe", O_RDONLY); // 읽기 전용으로 파이프 열기

   while (readLine(fd, str)) // 한 줄씩 읽기
      printf("%s\n", str); // 읽은 내용 출력
   close(fd);
   return 0;
}

int readLine(int fd, char *str) {
   int n;
   do {
      n = read(fd, str, 1); // 1바이트씩 읽기
      if (n > 0 && *str == '\n') { // 줄바꿈 문자를 만나면 종료
         *str = '\0'; // 종료 문자 추가
         break;
      }
   } while (n > 0 && *str++ != '\0');
   return (n > 0); // 읽기 성공 여부 반환
}

