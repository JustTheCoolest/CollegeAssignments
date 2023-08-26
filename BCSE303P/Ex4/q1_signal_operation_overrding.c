#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

void sigint_handler(){
    printf("Signal received %ld\n", time(NULL));
}

int main(){
    signal(SIGTSTP, sigint_handler);
    for(int i=0; i<2; i++){
        printf("Before: %ld\n", time(NULL));
        sleep(10);
        printf("After: %ld\n", time(NULL));
    }
}