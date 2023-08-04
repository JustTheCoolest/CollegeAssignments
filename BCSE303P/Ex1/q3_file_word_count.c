#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
  char file_address[200];
  printf("Address of the file to open: ");
  scanf("%s", &file_address);
  FILE *file_pointer = fopen(file_address, "r");
  char linux_command[206];
  sprintf(linux_command, "wc -w %s", file_address);
  printf("Number of words by system call: \n");
  system(linux_command);
  //printf("Number of words by manual calculation: %d", words(file_pointer));
}
