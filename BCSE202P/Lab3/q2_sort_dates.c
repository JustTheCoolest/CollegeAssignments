#include "../../ReallyUseful/StdioOperations.c"
#include "../../ReallyUseful/ArrayOperations.c"

void fillComparisonDates(int array_size, int dates[][3], int comparison_array[]){
  for(int i=0; i<array_size; ++i){
    comparison_array[i] = dates[i][2] * 10000 + dates[i][1] * 100 + dates[i][0];
  }
}

void Date_sort(int array_size, int swapping_array[][3], int comparing_array[]){
  for(int i = 0; i < array_size-1; ++i){
    for(int j = 0; j < array_size-i-1; ++j){
      if(comparing_array[j] > comparing_array[j+1]){
        swapContiguousIntArrays(3, swapping_array[j], swapping_array[j+1]);
        swap(&comparing_array[j], &comparing_array[j+1]);
      }
    }
  }
}

int main(){
  int array_size = 6;
  int arr[][3] = {{20,  1, 2014},
                    {25,  3, 2010},
                    { 3, 12, 1676},
                    {18, 11, 1982},
                    {19,  4, 2015},
                    { 9,  7, 2015}};
  int comparison_array[array_size];
  fillComparisonDates(array_size, arr, comparison_array);
  //printArray(array_size, comparison_array);
  Date_sort(array_size, arr, comparison_array);
  //printArray(array_size, comparison_array);
  print2DArray(array_size, 3, arr);
}
