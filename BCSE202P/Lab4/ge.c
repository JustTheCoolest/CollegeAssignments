#include "../../ReallyUseful/stack.c"
#include <stdio.h>

int function(int const n, int const array[]){
    int stack[50];
    int top = 0;
    for(int i=0; i<n; ++i){
        while(!(outOfLimits(50, top)<0) && peek(50, stack, &top)<array[i]){
            printf("%d -> %d\n", pop(50, stack, &top), array[i]);
        }
        push(50, stack, &top, array[i]);
        while(!(outOfLimits(50, top)<0)){
            printf("%d -> -1\n", pop(50, stack, &top));
        }
    }
}

int main(){
    int arr[] = {4, 15, 2, 9, 20, 11, 13};
    function(7, arr);
}