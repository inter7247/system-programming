#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
   char str[32] = "Do you like Linux?";
   char *ptr;
   char *p;

   ptr = (char *) malloc(32);
   memcpy(ptr, str, strlen(str));
   puts(ptr);

   memset(ptr + 12,'l',1);
   puts(ptr);

   p = (char *) memchr(ptr,'l',18);
   puts(p);
   memmove(str + 12, str + 7, 10);
   puts(str);
}
