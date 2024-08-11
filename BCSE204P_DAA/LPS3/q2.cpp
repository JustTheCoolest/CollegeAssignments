// Merge sort in C++

#include <iostream>
using namespace std;

// Merge two subarrays L and M into arr
int product(int p1, int p2){
    return p1 > p2 ? p1 : p2;
}

// Divide the array into two subarrays, sort them and merge them
int mergeSort(int arr[], int l, int r) {
  if(l==r){
    return arr[l];
  }
  // m is the point where the array is divided into two subarrays
  int m = l + (r - l) / 2;
  int p1 = mergeSort(arr, l, m);
  int p2 = mergeSort(arr, m+1, r);
  return product(p1, p2);
}

// Driver program
int main() {
  int arr[] = {932, 234, 45, 153, 9832, 2438};
  int size = sizeof(arr) / sizeof(arr[0]);
  int p = mergeSort(arr, 0, size - 1);
  cout << p << endl;
}