#include <stdio.h>
/* 파일 복사 프로그램 */
int main(int argc, char *argv[])
{
   char c;
   FILE *fp1, *fp2;
   if (argc !=3) {
      fprintf(stderr,  "How to use: %s File1 File2\n", argv[0]);
      return 1;
   }
   fp1 = fopen(argv[1], "r");
   if (fp1 == NULL) {
      fprintf(stderr, "File %s Open Error\n", argv[1]);
      return 2;
   }

   fp2 = fopen(argv[2], "a"); //"a" 추가 쓰기 (파일이 있으면: 기존 내용 뒤에 추가)
   if (fp2 == NULL) {
      fprintf(stderr, "File %s Open Error\n", argv[2]);
      return 3;
   }

   while ((c = fgetc(fp1)) != EOF) { //fp1(file1)을 문장끝일떄 까지 fp2에 복붙
      fputc(c, fp2);
   }

   fclose(fp1);
   fclose(fp2);
   return 0;
}
