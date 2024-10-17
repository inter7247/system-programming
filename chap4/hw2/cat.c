#include <stdio.h>
#include <string.h>

/* 텍스트 파일 내용을 표준출력에 출력 */
int main(int argc, char *argv[]) {
   FILE *fp;
   int c;
   if (argc < 2) {
      fp = stdin;                  // 명령줄 인수가 없으면 표준입력 사용
   }

   if(strcmp(argv[1], "-n") == 0) {//명령어 argv[1]부분에 -n이 있는지 확인
      for(int i = 2; i < argc; i++) {
         fp = fopen(argv[i],"r");  // 읽기 전용으로 파일 열기

         printf(" %d ", i - 1);    //문장 앞에 번호 출력

         c = getc(fp);             // 파일로부터 문자 읽기
         while (c != EOF) {        // 파일끝이 아니면
            putc(c, stdout);       // 읽은 문자를 표준출력에 출력
            c = getc(fp);
         }
         fclose(fp);
      }
   } else {
      for(int i = 1; i < argc; i++) {
         fp = fopen(argv[i],"r");  // 읽기 전용으로 파일 열기

         c = getc(fp);             // 파일로부터 문자 읽기
         while (c != EOF) {        // 파일끝이 아니면
            putc(c, stdout);       // 읽은 문자를 표준출력에 출력
            c = getc(fp);
         }
         fclose(fp);
      }
   }

   return 0;
}

//기존 명령어에서 추가된 부분
//strcmp를 통한 -n 확인 및 for문을 통한 파일 연속으로 읽기(hw1 참고)
