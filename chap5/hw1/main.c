#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char savedText[10][100]; //텍스트 파일을 각 문자열에 저장할 2차원 배열
    int fd;

    //파일 열기
    if((fd = open(argv[1], O_RDONLY)) == -1) {
        printf("File Open Error\n"); //실패시 출력
        exit(1);
    } else {
        printf("File %s Open Sucess\n", argv[1]); //성공시
    }

    //파일 읽기 및 저장
    char buf;
    int row = 0, col = 0; //변수 행과 열 생성

    while(read(fd, &buf, 1) > 0 && row < 10) { // read()를 통해 성공적으로 읽고 행 값이 10 미만일떄 까지
        if (buf == '\n' || col == 99 ) { //buf값이 줄바꿈 이거나 열 값이 최대(99)일떄 까지
            savedText[row][col] = '\0'; //문자열 끝에 null 문자열 종료 추가
            row++; //다음 행 값으로 이동
            col = 0; //다음 행의 첫 열 값으로 이동
        } else {
            savedText[row][col++] = buf; //buf 값을 2차원 savedText 배열에 저장 후 col값을 1증가
        }
    }

    close(fd);

    printf("Total Line : %d\n", row);
    if(row > 2) {
        printf("You can choose 1 ~ %d Line\n", row);
    } else {
        printf("You can choose 1 Line\n");
    }
    
    char range[10]; 
    printf("Pls 'Enter' the line to select : "); //원하는 줄 출력 입력문
    scanf("%s", range); //범위 입력
    
    printf("=====================================\n"); //가시성을 위한 문장

    //"*": 모든 줄 출력
    if(strcmp(range, "*") == 0) { //문자열 비교문 사용 참 일시 0반환
        for(int i = 0 ; i < row; i++) {
            printf("%s\n", savedText[i]);
        }
    } else if(strchr(range,',') != NULL) { //",": 줄 번호 리스트
        int line;
        char *lineNum = strtok(range, ","); //문자열을 ","기준으로 토큰 단위로 자르기
        while(lineNum != NULL) {
            line = atoi(lineNum);
            if(line > 0 && line <= row) { //입력 줄이 0보다 크고 전체 열 보다 같거나 작을떄
                printf("%s\n", savedText[line - 1]);
            } else {
                printf("worng range\n");
            }
            lineNum = strtok(NULL,","); //자른 문자 다음부터 다시 검색
        } 
    } else if(strchr(range, '-') != NULL) { //"-":줄의 범위
        int start, end;
        char *lineRange = strtok(range, "-"); //문자열을 "-"기준으로 토큰 단위로 자르기
        if(lineRange != NULL) { //문자끝 NULL을 반환하기 전 까지
            start = atoi(lineRange); //첫 범위를 변수 start에 저장
            lineRange = strtok(NULL,"-");
            if(lineRange != NULL) { //문자끝NULL을 반환하기 전까지
                end = atoi(lineRange);
                if(start > 0 && start <= end && end && row) { //범위가 제대로 지정되었는지 확인
                    for(int i = start - 1; i < end; i++) {
                    printf("%s\n", savedText[i]);
                    } 
                } else {
                    printf("wrong range\n");
                }
            } else {
                printf("wrong range\n");
            }
        } else {
            printf("wrong range\n");
        }
    } else { //"n": 한 줄 출력
        int num = atoi(range);
        if(num > 0 && num <= row) {
            printf("%s\n", savedText[num - 1]);
        }
    }
    exit(0);
} 
