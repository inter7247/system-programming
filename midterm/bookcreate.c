#include <stdio.h> 
#include "db.h"
/* 학생 정보를 읽어 텍스트 파일에 저장한다. */
int main(int argc, char* argv[]) 
{ 
   struct bookinfo rec;
   FILE *fp;
   if (argc != 2) {
      fprintf(stderr, "How to use: %s FileName\n", argv[0]);
      return 1; 
   }
      fp = fopen(argv[1], "w");
   printf("%-4s %-9s %-9s %-5s %-4s %-7s\n", "ID", "bookname", "author", "year", "numofborrow", "borrow");
   while (scanf("%d %s %s %d %d %s", &rec.id, &rec.bookname[10], &rec.author[10], &rec.year, &rec.numoborrow, &rec.borrow[10]) == 6)
      fprintf(fp, "%d %s %s %d %d %s", rec.id, rec.bookname, rec.author, rec.year, rec.numoborrow, rec.borrow);
   fclose(fp);
   return 0;
} 
