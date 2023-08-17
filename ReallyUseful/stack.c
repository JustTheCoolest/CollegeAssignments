#include <stdio.h>

int outOfLimits(int const n, int const top){
    if(top==n){
        printf("Stack overflow\n");
        return 1;
    }
    if(top==0){
        return -1;
    }
    return 0;
}

void push(int const n, int stack[], int * const top, int const element){
    if(outOfLimits(n, *top)>0) return;
    stack[(*top)++] = element;
}

int pop(int const n, int stack[], int * const top){
    if(outOfLimits(n, *top)<0){
        printf("Stack underflow\n");
        return 0;
    }
    return stack[--(*top)];
}

int peek(int const n, int const stack[], int const * const top){
    if(outOfLimits(n, *top)<0){
        printf("Stack underflow\n");
        return 0;
    }
    return stack[*top];
}

void display(int const n, int const stack[], int const *top){
    if(outOfLimits(n, *top) == -1){
        printf("There are no elements in the stack\n");
        return;
    }
    for(int i=0; i<*top; ++i){
        printf("%d ", stack[i]);
    }
    printf("<- Top\n");
}