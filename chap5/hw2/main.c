#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    char savedText[10][100]; //텍스트 파일을 각 문자열을 저장할 2차원 배열
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

   for (int i = row - 1; i  > -1; i--) { //전체 열 부터 감소 하면서 출력
      printf("%s\n", savedText[i]); 
   }
   
    exit(0);
}
