#include <stdio.h>

const int n=5;
int data[5];

int t1, t2;

int init(){
    t1=0;
    t2=n-1;
}

int outOfLimits(){
    if(t1>t2){
        return 1;
    }
    if(t1==0){
        return -1;
    }
    if(t2==n-1){
        return -2;
    }
    return 0;
}

void push1(int element){
    if(outOfLimits()>0){
        printf("Stack overflow\n");
        return;
    }
    data[t1++] = element;
}

void push2(int element){
    if(outOfLimits()>0){
        printf("Stack overflow\n");
        return;
    }
    data[t2--] = element;
}

int pop1(){
    if(outOfLimits()==-1){
        printf("Stack 1 underflow\n");
        return 0;
    }
    return data[--t1];
}

int pop2(){
    if(outOfLimits()==-2){
        printf("Stack 2 underflow\n");
        return 0;
    }
    return data[++t2];
}

int peek1(){
    if(outOfLimits()==-1){
        printf("No elements in stack 1\n");
        return 0;
    }
    return data[--t1];
}

int peek2(){
    if(outOfLimits()==-2){
        printf("No elements in stack 1\n");
        return 0;
    }
    return data[--t2];
}

void display1(){
    if(outOfLimits()==-1){
        printf("No elements in stack 1\n");
        return;
    }
    for(int i=0; i<t1; ++i){
        printf("%d ", data[i]);
    }
    printf(" <- Top\n");
}

void display2(){
    if(outOfLimits()==-1){
        printf("No elements in stack 1\n");
        return;
    }
    for(int i=n-1; i>t2; --i){
        printf("%d ", data[i]);
    }
    printf(" <- Top\n");
}