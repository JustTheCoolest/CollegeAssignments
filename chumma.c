#include <stdio.h>

int main(){
   printf("%lu\n", sizeof(char*));
   printf("%lu\n", sizeof(char));
   char *string = "%%";
   char *curr = string;
   while(*curr != '\0'){
      printf("%c", *curr);
      ++curr;
   }
   printf("\n");
}