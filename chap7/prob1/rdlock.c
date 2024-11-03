#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include <string.h>

/* 잠금을 이용한 학생 데이터베이스 질의 프로그램 */
int main(int argc, char *argv[]) {
    int fd, id;
    struct student record;
    struct flock lock;

    if (argc < 2) {
        fprintf(stderr, "How to use : %s File \n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("\nEnter StudentID to search : ");
    while (scanf("%d", &id) == 1) {
        // 잠금 구조체 초기화
        memset(&lock, 0, sizeof(lock));

        // 읽기 잠금 설정
        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (id - START_ID) * sizeof(record);
        lock.l_len = sizeof(record);

        if (fcntl(fd, F_SETLKW, &lock) == -1) { /* 읽기 잠금 */
            perror("fcntl lock error");
            exit(3);
        }

        // 레코드 위치로 이동
        off_t offset = (id - START_ID) * sizeof(record);
        if (lseek(fd, offset, SEEK_SET) == -1) {
            perror("lseek error");
            lock.l_type = F_UNLCK;
            fcntl(fd, F_SETLK, &lock); // 잠금 해제 후 종료
            exit(4);
        }

        // 레코드 읽기 및 출력
        if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0)) {
            printf("Name: %s\t StuID: %d\t Score: %d\n", record.name, record.id, record.score);
        } else {
            printf("No record with ID %d\n", id);
        }

        // 읽기 잠금 해제
        lock.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLK, &lock) == -1) {
            perror("fcntl unlock error");
            exit(5);
        }

        printf("\nEnter StudentID to search : ");
    }

    close(fd);
    exit(0);
}

