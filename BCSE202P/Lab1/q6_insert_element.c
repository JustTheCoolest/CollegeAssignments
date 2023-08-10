#include <stdio.h>
#include "../../ReallyUseful/StdioOperations.c"
#include "../../ReallyUseful/ArrayOperations.c"

// Next edition : Dynamic memory allocation
int main(){
    int n;
    printf("Enter number of elements in initial array: ");
    scanf("%d", &n);
    int array[100];
    getInputs(n, array);
    int element, position;
    printf("Enter element to be inserted: ");
    scanf("%d", &element);
    printf("Enter position to be inserted at: ");
    scanf("%d", &position);
    insertElement(n, array, element, position);
    ++n;
    printArray(n, array);
}