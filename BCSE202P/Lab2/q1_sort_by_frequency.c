/*
Algorithm:

Dictionary : [[number, frequency], ...]
Iterate through dictionary to find max frequency that is less than previous max
Iterate through dictionary to print all elements having this max frequency
Repeat until exhaustion

Bubble sort:
for i in range(0, n-1):
  for j in range(0, n-1-i):
    if key(array[j]) > key(array[j+1]):
      swap(array[j], array[j+1])

*/
#include <stdio.h>
#include <math.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp; 
}

void bubble_sort(int n, int array[]){
  for(int i=0; i<n-1; ++i){
    for(int j=0; j<n-i-1; ++j){
      if(array[j] > array[j+1]){
        swap(&array[j], &array[j+1]);
      }
    }
  }
}

int fillDictionary(int n, int dictionary[n][2], int array[]){
  int count=0;
  int *prev = &dictionary[count][0];
  *prev = array[0];
  dictionary[count][1] = 1;
  for(int i=1; i<n; ++i){
    if(array[i] == *prev){
      ++dictionary[count][1];
      continue;
    }
    count++;
    prev = &dictionary[count][0];
    *prev = array[i];
    dictionary[count][1] = 1;
  }
  return count+1;
}

void printSortedDict(int dn, int dictionary[dn][2]){
  int prev_max = INFINITY;
  int new_max;
  while(1){
    new_max = -1;
    for(int i=0; i<dn; ++i){
      if(dictionary[i][1] > new_max && dictionary[i][1] < prev_max){
        new_max = dictionary[i][1];
      }
    }
    if(new_max==-1) break;
    for(int i=0; i<dn; ++i){
      int freq = dictionary[i][1];
      if(freq == new_max){
        for(int j=0; j<freq; ++j) printf("%d ", dictionary[i][0]);
      }
    }
    prev_max = new_max;
  }
}

void printArray(int n, int numbers[], int k1, int k2){
    for(int i=k1; i<=k2; ++i){
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

void Fsort(int n, int array[]){
  int dictionary[n][2];
  bubble_sort(n, array);
  //printArray(n, array, 0, n-1);
  int dn = fillDictionary(n, dictionary, array);
//   for(int i=0; i<dn; ++i){
//       printf("%d %d\n", dictionary[i][0], dictionary[i][1]);
//   }
  printSortedDict(dn, dictionary);
}

int main(){
    int arr[] = {2, 5, 2, 8, 5, 6, 8, 8};
    Fsort(8, arr);
}
