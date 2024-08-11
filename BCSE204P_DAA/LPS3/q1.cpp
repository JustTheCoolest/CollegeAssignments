// Merge sort in C++

#include <iostream>
using namespace std;

// Merge two subarrays L and M into arr
void product(int p[2], int p1[2], int p2[2]){
    p[0] = p1[0] * p2[0] - p1[1] * p2[1];
    p[1] = p1[0] * p2[1] + p1[1] * p2[0];
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int arr[][2], int l, int r, int p[2]) {
  if(l==r){
    p[0] = arr[l][0];
    p[1] = arr[l][1];
  }
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;
    int p1[2], p2[2];
    mergeSort(arr, l, m, p1);
    mergeSort(arr, m+1, r, p2);
    product(p, p1, p2);
  }
}

// Driver program
int main() {
  int arr[][2] = {{1, 2}, {7, 2}, {6, 1}, {9, 5}};
  int size = sizeof(arr) / sizeof(arr[0]);
  int p[2];
  mergeSort(arr, 0, size - 1, p);
  cout << p[0] << " " << p[1] << endl;
}