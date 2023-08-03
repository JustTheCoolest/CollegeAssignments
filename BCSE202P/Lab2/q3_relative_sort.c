#include "../../Really Useful/QuickSort.c"
#include "../../Really Useful/StdioOperations.c"

void relative_Sort(int n1, int A1[], int n2, int A2[]){
    int *position_to_fill = A1;
    for(int i=0; i<n2; ++i){
        int number_of_elements_filled = (position_to_fill - A1);
        for(int j=number_of_elements_filled; j<n1; ++j){
            if(A1[j] == A2[i]){
                swap(&A1[j], position_to_fill++);
            }
        }
    }
    quickSort(A1, (position_to_fill-A1), n1-1);
}

int main(){
    int A1[] = {2, 1, 2, 5, 7, 1, 9, 3, 6, 8, 8};
    int A2[] = {2, 1, 8, 3};
    int n1 = sizeof(A1)/sizeof(*A1);
    int n2 = sizeof(A2)/sizeof(*A2);
    relative_Sort(n1, A1, n2, A2);
    printArray(n1, A1);
}