#include "IntegerOperations.c"
// Task: Make proper .h headers with only declarations instead

void insertElement(int n, int array[], int element, int position){
    for(int i=n; i>position; --i){
        array[i] = array[i-1];
    }
    array[position] = element;
}

void swapContiguousIntArrays(int array_size, int a[], int b[]){
  for(int i=0; i<array_size; ++i){
    swap(&a[i], &b[i]);
  }
}