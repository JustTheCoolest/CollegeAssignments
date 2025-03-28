// Merge sort in C++

#include <iostream>
using namespace std;

int total_calls = 0;
int max_depth = 0;

// Merge two subarrays L and M into arr
void merge(int arr[], int p, int q, int r) {
  
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

int find_m(int arr[], int l , int r){
    // ASSERT L < R
    int min = __INT_MAX__;
    int min_index = -1;
    for(int i=l; i<=r; ++i){
        if(arr[i] > min){
            continue;
        }
        min = arr[i];
        min_index = i;
    }
    if(min_index==r){
        --min_index;
    }
    return min_index;
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int arr[], int l, int r, int depth = 0) {
  total_calls++;
  max_depth = max(max_depth, depth);

  if (l < r) {
    int m = find_m(arr, l, r);

    mergeSort(arr, l, m, depth + 1);
    mergeSort(arr, m + 1, r, depth + 1);

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
  int arr[] = {6, 5, 12, 10, 9, 1, 2843, 238, 352, -12414, 324, 3, 99, 0, 12};
  int size = sizeof(arr) / sizeof(arr[0]);

  mergeSort(arr, 0, size - 1);

  cout << "Sorted array: \n";
  printArray(arr, size);
  cout << "Total recursive calls: " << total_calls << "\n";
  cout << "Maximum recursion depth: " << max_depth << "\n";
  return 0;
}