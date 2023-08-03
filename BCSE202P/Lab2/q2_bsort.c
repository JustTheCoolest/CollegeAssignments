/* Algorithm: Regular sorting*/

#include "../../Really Useful/QuickSort.c"
#include "../../Really Useful/StdioOperations.c"

void Bsort(int n, int numbers[]){
    quickSort(numbers, 0, n-1);
}

int main(){
    int arr[] = {10, 3, 5, 9, 7, 2, 6, 1, 4, 8};
    int n = 10;
    Bsort(n, arr);
    printArray(n, arr);
}