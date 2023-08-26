#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sigint_handler(int){
    printf("Signal received\n");
    sleep(1);
}

int main(){
    signal(8, &sigint_handler);
    printf("Before\n");
    int a = 1/0;
    printf("After\n");
}