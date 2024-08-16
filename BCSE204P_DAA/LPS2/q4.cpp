// Merge sort in C++

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

// Merge two subarrays L and M into arr
void merge(vector<int>& arr, int p, int q, int r) {
  
  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(vector<int>& arr, int l, int r, int s) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    // int m = l + (r - l) / 2;
    int m = min(l + s, r-1);

    mergeSort(arr, l, m, s);
    mergeSort(arr, m + 1, r, s);

    // Merge the sorted subarrays
    merge(arr, l, m, r);
  }
}

// Print the array
void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++)
    cout << arr[i] << " ";
  cout << endl;
}

// Driver program
int main() {
  int size = 100;
  for(int s=0; s<size; ++s){
    vector<int> arr(size);
    for(int i=0; i<size; i++){
        arr[i] = rand() % __INT_MAX__;
    }
    // printArray(arr.data(), size);
    clock_t start = clock();
    mergeSort(arr, 0, size - 1, s);
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    cout << s << " " << elapsed << endl;

    // cout << "Sorted array: \n";
    // printArray(arr.data(), size);
    // cout << endl;
  }
}