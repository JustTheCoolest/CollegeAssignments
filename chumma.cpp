#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int a=90;
    int* b=&a;
    int pid = fork();
    if(pid<0){
        exit(1);
    }
    else if(pid==0){
        *b = 10;
        printf("%d",*b);
    }
    else{
        wait(NULL);
        printf("%d",*b);
    }
}