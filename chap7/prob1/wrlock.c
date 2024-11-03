#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "student.h"
#include <string.h>

/* 잠금을 이용한 학생 데이터베이스 수정 프로그램 */
int main(int argc, char *argv[]) {
    int fd, id;
    struct student record;
    struct flock lock;

    if (argc < 2) {
        fprintf(stderr, "How to use : %s File \n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("\nEnter StudentID you want to modify : ");
    while (scanf("%d", &id) == 1) {
        // 잠금 구조체 초기화
        memset(&lock, 0, sizeof(lock)); 

        // 잠금 설정
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (id - START_ID) * sizeof(record);  // 시작 위치 계산
        lock.l_len = sizeof(record);  // 잠금 크기

        if (fcntl(fd, F_SETLKW, &lock) == -1) { /* 쓰기 잠금 */
            perror("fcntl");
            exit(3);
        }

        // 레코드 위치로 이동 off_t: long형 정수
        off_t offset = (id - START_ID) * sizeof(record);
        if (lseek(fd, offset, SEEK_SET) == -1) {
            perror("lseek error");
            exit(4);
        }

        // 레코드 읽기
        if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0)) {
            printf("Name: %s\t StuID: %d\t Score: %d\n", record.name, record.id, record.score);
            printf("Enter new score: ");
            scanf("%d", &record.score);

            if (lseek(fd, offset, SEEK_SET) == -1) {
                perror("lseek error");
                exit(5);
            }

            write(fd, (char *) &record, sizeof(record));
            lock.l_type = F_UNLCK;
            fcntl(fd, F_SETLK, &lock);
        } 
        else printf("No record %d \n", id);
        printf("\nEnter StudentID you want to modify : ");
    }

    close(fd);
    exit(0);
}

