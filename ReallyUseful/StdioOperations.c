#include <stdio.h>

void getInputs(int n, int array[]){
    printf("Enter %d elements: \n", n);
    for(int i=0; i<n; i++){
        scanf("%d", &array[i]);
    }
}

void printArray(int n, int numbers[]){
    for(int i=0; i<n; i++){
        printf("%d ", numbers[i]);
    }
    printf("\n");
}