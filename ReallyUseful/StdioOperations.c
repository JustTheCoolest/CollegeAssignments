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

void print2DArray(int array_size, int inner_array_size, int array[array_size][inner_array_size]){
  for(int i=0; i<array_size; ++i){
    for(int j=0; j<inner_array_size; ++j){
      printf("%d ", array[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}