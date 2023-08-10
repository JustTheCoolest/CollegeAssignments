#include "../../ReallyUseful/StdioOperations.c"
#include "../../ReallyUseful/IntegerOperations.c"

int number_of_high_bits(int number){
  int counter = 0;
  while(number>0){
    counter += number%2;
    number >>= 1;
  }
  return counter;
}

void get_counts(int const array_size, int const numbers[], int counts[]){
  for(int i=0; i<array_size; ++i){
    counts[i] = number_of_high_bits(numbers[i]);
  }
}

void Bsort(int array_size, int swapping_array[], int comparing_array[]){
  for(int i = 0; i < array_size-1; ++i){
    for(int j = 0; j < array_size-1-i; ++j){
      if(comparing_array[j] < comparing_array[j+1]){
        swap(&swapping_array[j], &swapping_array[j+1]);
        swap(&comparing_array[j], &comparing_array[j+1]);
      }
    }
  }
}

int main(){
  int n = 9;
  int arr[] = {5, 2, 3, 9, 4, 6, 7, 15, 32};
  int counts[9];
  get_counts(n, arr, counts);
  //printArray(n, counts);
  Bsort(n, arr, counts);
  //printArray(n, counts);
  printArray(n, arr);
}

