#include "../../Really Useful/QuickSort.c"
#include "../../Really Useful/StdioOperations.c"

void printArrayWithRange(int n, int numbers[], int k1, int k2){
    for(int i=k1; i<=k2; ++i){
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

int test_main(){
    int n = 10;
    int numbers[10] = {10, 3, 5, 9, 7, 2, 6, 1, 4, 8};
    int k1 = 4, k2 = 9;
    //printArray(n, numbers, 0, n-1);
    quickSort(numbers, 0, n-1);
    printArrayWithRange(n, numbers, 0, n-1);
    printArrayWithRange(n, numbers, k1, k2);
}

int actual_main(){
    int n;
    scanf("%d", &n);
    int numbers[n];
    getInputs(n, numbers);
    int k1, k2; 
    scanf("%d %d", &k1, &k2);
    quickSort(numbers, 0, n-1);
    printArrayWithRange(n, numbers, 0, n-1);
    printArrayWithRange(n, numbers, k1, k2);
}

int main(){
    test_main();
}