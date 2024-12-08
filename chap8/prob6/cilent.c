#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 256

int main() {
    int fd1, fd2;
    char msg[MAXLINE];

    // FIFO 열기
    fd1 = open("./chatfifo1", O_RDONLY); // 서버로부터 읽기
    fd2 = open("./chatfifo2", O_WRONLY); // 서버로 쓰기
    if (fd1 == -1 || fd2 == -1) {
        perror("open");
        exit(1);
    }

    printf("* 클라이언트 시작\n");

    if (fork() == 0) { // 자식 프로세스: 읽기
        while (1) {
            int n = read(fd1, msg, MAXLINE);
            if (n > 0) {
                printf("[서버] -> %s\n", msg);
            }
        }
    } else { // 부모 프로세스: 쓰기
        while (1) {
            printf("[클라이언트] : ");
            fgets(msg, MAXLINE, stdin);
            write(fd2, msg, strlen(msg) + 1);
        }
    }

    close(fd1);
    close(fd2);
    return 0;
}

