#include <stdio.h>

void getInputs(int n, int numbers[]){
    for(int i=0; i<n; i++){
        scanf("%d", &numbers[i]);
    }
}

void printArray(int n, int numbers[]){
    for(int i=0; i<n; i++){
        printf("%d ", numbers[i]);
    }
    printf("\n");
}