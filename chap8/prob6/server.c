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

    // FIFO 생성
    if (mkfifo("./chatfifo1", 0666) == -1) {
        perror("mkfifo1");
    }
    if (mkfifo("./chatfifo2", 0666) == -1) {
        perror("mkfifo2");
    }

    // FIFO 열기
    fd1 = open("./chatfifo1", O_WRONLY); // 클라이언트로 쓰기
    fd2 = open("./chatfifo2", O_RDONLY); // 클라이언트로부터 읽기
    if (fd1 == -1 || fd2 == -1) {
        perror("open");
        exit(1);
    }

    printf("* 서버 시작\n");

    if (fork() == 0) { // 자식 프로세스: 읽기
        while (1) {
            int n = read(fd2, msg, MAXLINE);
            if (n > 0) {
                printf("[클라이언트] -> %s\n", msg);
            }
        }
    } else { // 부모 프로세스: 쓰기
        while (1) {
            printf("[서버] : ");
            fgets(msg, MAXLINE, stdin);
            write(fd1, msg, strlen(msg) + 1);
        }
    }

    close(fd1);
    close(fd2);
    return 0;
}
