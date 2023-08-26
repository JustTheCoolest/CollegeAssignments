#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int d=7001;

void sigint_handler(){
    printf("Signal received %d\n", d);
    sleep(1);
}

int main(){
    signal(11, sigint_handler);
    int a[] = {1,2};
    printf("Before\n");
    int c;
    printf("jds "), c = a[d-=1000, d];
    printf("c=%d\n", c);
    printf("After\n");
}